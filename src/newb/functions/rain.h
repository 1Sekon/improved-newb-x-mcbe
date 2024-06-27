#ifndef RAIN_H
#define RAIN_H

#include "noise.h"
#include "sky.h"
#include "water.h"

float Reflection1(vec3 pos){
  float m = clamp(length(pos.xz), 0.0, 1.0);
  float r = cos(atan(pos.x*0.9, pos.z*0.6)*10.)*1.2;

  return mix(0.0, r, smoothstep(0.45, 1.0, m));
}

float nlWindblow(vec2 p, float t){
  float val = sin(4.0*p.x + 2.0*p.y + 2.0*t + 3.0*p.y*p.x)*sin(p.y*2.0 + 0.2*t);
  val += sin(p.y - p.x + 0.2*t);
  return 0.25*val*val;
}

vec4 nlRefl(
  inout vec4 color, inout vec4 mistColor, vec2 lit, vec2 uv1, vec3 tiledCpos,
  float camDist, vec3 wPos, vec3 viewDir, vec3 torchColor, vec3 horizonEdgeCol, vec3 horizonCol,
  vec3 zenithCol, vec3 FOG_COLOR, float rainFactor, float renderDist, highp float t, vec3 pos, bool underWater, bool end, bool nether
) {
  vec4 wetRefl = vec4(0.0,0.0,0.0,0.0);
  float night = 1.0*max(1.0 - 3.0*max(FOG_COLOR.b, FOG_COLOR.g), 0.0);

if(!end) {

  #ifndef NL_GROUND_REFL
  if (rainFactor > 0.0) {
  #endif
    float wetness = lit.y*lit.y;

  #ifdef NL_RAIN_MIST_OPACITY
    // humid air blow
    float humidAir = rainFactor*wetness*nlWindblow(pos.xy/(1.0+pos.z), t);
    mistColor.a = min(mistColor.a + humidAir*NL_RAIN_MIST_OPACITY, 1.0);
  #endif

    // clip reflection when far (better performance)
    float endDist = renderDist*0.6;
    if (camDist < endDist) {
      float cosR = max(viewDir.y, 0.0);
      float puddles = max(1.0 - NL_GROUND_RAIN_PUDDLES*fastRand(tiledCpos.xz), 0.0);

      #ifndef NL_GROUND_REFL
      wetness *= puddles;
      float reflective = wetness*rainFactor*NL_GROUND_RAIN_WETNESS;
      #else
      float reflective = NL_GROUND_REFL;
      if (!end && !nether) {
        reflective *= wetness;
      }

      wetness *= puddles;
      reflective = mix(reflective, wetness, rainFactor);
      #endif

      if (wPos.y < 0.0) {
        // wetRefl.rgb = getRainSkyRefl(horizonCol, zenithCol, cosR);
        wetRefl.rgb = getSkyRefl(horizonEdgeCol, horizonCol, zenithCol, viewDir, FOG_COLOR, t, -wPos.y, rainFactor, end, underWater, nether, wPos, lit.y);
        wetRefl.a = calculateFresnel(cosR, 0.03)*reflective;

        #if defined(NL_GROUND_AURORA_REFL) && defined(NL_AURORA) && defined (NL_GROUND_REFL)
      if(camDist < 57.0) {
        wetRefl.rgb += nlcAuroraReflect(wPos, t, rainFactor, FOG_COLOR).rgb*lit.y*(1.0-0.75*color.a)*clamp(2.0-2.0*camDist/57.0, 0.0, 1.0);
      }
        #endif

        // torch light
        wetRefl.rgb += torchColor*lit.x*NL_TORCH_INTENSITY;
        
        // fake reflections
      #ifndef NL_GROUND_REFL
        wetRefl.rgb += mix(0.0, Reflection1(wPos)*0.8*(1.0-night), puddles);
      #endif

        // fade out before clip
        wetRefl.a *= clamp(2.0-2.0*camDist/endDist, 0.0, 1.0);
      }
    }

    // darken wet parts
    color.rgb *= 1.0 - 0.4*wetness*rainFactor;

  #ifndef NL_GROUND_REFL
  }
  #endif

}

  return wetRefl;
}

#endif

#ifdef OPAQUE
$input v_fogColor, v_worldPos, v_underwaterRainTime, v_sPos
#endif

#include <bgfx_shader.sh>
#include <newb/main.sh>

uniform vec4 FogColor;
uniform vec4 FogAndDistanceControl;

void main() {
#ifdef OPAQUE
  vec3 viewDir = normalize(v_worldPos);
  bool underWater = v_underwaterRainTime.x > 0.5;
  bool nether = detectNether(FogColor.rgb, FogAndDistanceControl.xy);
  float rainFactor = v_underwaterRainTime.y;

  float mask = (1.0-1.0*rainFactor)*max(1.0 - 3.0*max(FogColor.b, FogColor.g), 0.0);

  vec3 zenithCol;
  vec3 horizonCol;
  vec3 horizonEdgeCol;
  if (underWater) {
    vec3 fogcol = getUnderwaterCol(v_fogColor);
    zenithCol = fogcol;
    horizonCol = fogcol;
    horizonEdgeCol = fogcol;
  } else {
    zenithCol = getZenithCol(rainFactor, v_fogColor);
    horizonCol = getHorizonCol(rainFactor, v_fogColor);
    horizonEdgeCol = getHorizonEdgeCol(horizonCol, rainFactor, v_fogColor);
  }

  vec3 skyColor = nlRenderSky(horizonEdgeCol, horizonCol, zenithCol, -viewDir, v_underwaterRainTime.z, rainFactor, false, underWater, nether, v_fogColor, 1.0);

  float fade = clamp(2.0-2.0*length(v_worldPos)*0.0022, 0.0, 1.0);
  vec4 auroraSky = nlcAuroraSky1(v_sPos, v_underwaterRainTime.z, rainFactor, v_fogColor);

  #ifdef NL_AURORA
    skyColor.rgb += mix(vec3(0.0, 0.0, 0.0), auroraSky.rgb, auroraSky.a*fade);
  #endif
  
  skyColor.rgb = colorCorrection(skyColor.rgb);
  
  if(!underWater){
    drawMeteors(skyColor.rgb, v_sPos.xz, v_underwaterRainTime.z, mask);
  }

  gl_FragColor = vec4(skyColor, 1.0);
#else
  gl_FragColor = vec4(0.0,0.0,0.0,0.0);
#endif
}

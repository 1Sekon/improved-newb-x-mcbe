#ifndef CUSTOM_H
#define CUSTOM_H

#include "noise.h"

/*=========>
??????
Why you are here?
<=========*/



// distance between two vec2
float distance(vec2 p0, vec2 p1)
{
    return sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
}


// for tinting rounded cloud
vec3 getCloudTint1(float rainFactor, vec3 FOG_COLOR) {
  vec3 col = mix(mix(NLC_DAY_CLOUD2_TINT, NLC_DAWN_CLOUD2_TINT, duskD(FOG_COLOR)), NLC_NIGHT_CLOUD2_TINT, nightD(FOG_COLOR));
  
  float brightness = min(FOG_COLOR.g, 0.26);
  brightness *= brightness*19.6;
  
  return mix(col, NLC_RAIN_CLOUD2_TINT*brightness, rainFactor);
}

#include "clouds.h"

// for remove effects that appear in bottom end sky
vec3 HorizonMask(vec3 bmd, vec3 zenith, vec3 viewDir)
{
  float f = 0.7*smoothstep(-0.5, 1.0, viewDir.y);
  return mix(bmd, zenith, f*f);
}


// stars field for end sky
// by bjarkeck : https://www.shadertoy.com/view/lsc3z4
// modified By 1Sekon
#define STARDISTANCE 87.0
#define STARBRIGHTNESS 0.6
#define STARDENSITY 0.05

float endStars(vec3 ray, float t)
{
    vec3 p = ray * STARDISTANCE;
    float h = hash13(p);
    float flicker = cos(sin(t * 1.2) + hash13(fract(p) * 0.05) * 14.) * 0.7 + 0.5;
    float brigtness = smoothstep(1.0 - STARDENSITY, 1.0, hash13(floor(p)));
    return smoothstep(STARBRIGHTNESS, 0., length(fract(p) - 0.5)) * brigtness * flicker;
}

void drawMeteor(inout vec3 col, in vec2 uv, vec2 startP, vec2 endP, float linWidth, float mask, vec2 sp, vec2 ep){

   uv *= 250.0;
   vec2 lineDir = endP - startP;
   vec2 fragDir = uv - startP;

   float lineCoe = clamp(dot(lineDir,fragDir)/dot(lineDir,lineDir),0.,1.0);

   vec2 projDir = lineCoe*lineDir;

   vec2 fragToLineDir = fragDir - projDir;

   float dis = length(fragToLineDir);
   float disToTail = length(projDir);
   dis = linWidth / dis;

   col += dis*vec3(0.8)*(disToTail*disToTail*disToTail)*mask*smoothstep(0.0, 1.0, (1.0-distance(startP, endP)));

}

void drawMeteors(inout vec3 col, vec2 uv, float time, float mask){

    vec2 dir = normalize(vec2(-1.0, -0.5));
    vec2 mv  = -dir*cos(mod(time*1.2,NLC_CONST_PI))*90.0;
    vec2 sp  = vec2(10.0+100.0*hash1(vec2(floor(time*1.2/NLC_CONST_PI))),10.0);
    vec2 ep  = sp+dir*5.0;

    drawMeteor(col, uv, sp+mv, ep+mv, 0.0005, mask, sp, ep);

}


// End smoke effects
vec3 nlcSmoke(vec3 sky, vec3 viewDir, vec3 wPos, vec3 zenithCol, vec3 horizonCol, float t)
{
  vec2 parallax = viewDir.xz/viewDir.y;
  vec2 projectedPos = wPos.xz - parallax*100.0;
  float fade = clamp(2.0 - 0.004*length(projectedPos), 0.0, 1.0);

  vec4 smoke = renderCloudsSimple(projectedPos.xyy, t, 0.0, zenithCol*0.6, horizonCol, vec3(0.05, 0.01, 0.04), vec3(1.0, 1.0, 1.0));
  
  return mix(sky, 1.6*smoke.rgb, smoke.a*fade);
}

// End Spiral
// By Bitmesh : https://www.shadertoy.com/view/3sSXDc
vec3 nlcEndSpiral(vec3 pos, float t, vec3 horizonCol)
{
  vec2 nPos = pos.xz;
  nPos = vec2((atan2(nPos.y,nPos.x)) + t*0.6, sqrt(nPos.x*nPos.x + nPos.y*nPos.y));

  float shape = pow(1.0-nPos.y, 10.0)*10.0;
  shape = sin((nPos.x + pow(nPos.y, 0.2)*10.0) * 6.0) + shape - nPos.y*2.;
  vec3 col = horizonCol*max(0.0,shape)*0.7;
  
  return HorizonMask(vec3(0.0), col, pos);
}

#include "lighting.h"
vec4 nlcEndRefl1(vec2 lit, vec2 uv1, float camDist, vec3 wPos, vec3 viewDir, vec3 torchColor, vec3 horizonEdgeCol, vec3 horizonCol, vec3 zenithCol, vec3 FOG_COLOR, float rainFactor, float renderDist, highp float t, bool underWater, bool end, bool nether)
{
  vec4 Refl = vec4(0.0,0.0,0.0,0.0);
if(end){
    // clip reflection when far (better performance)
    float endDist = renderDist;
    if (camDist < endDist) {
      float cosR = max(viewDir.y, 0.0);

      if (wPos.y < 0.0) {
        Refl.rgb = getSkyRefl(horizonEdgeCol, horizonCol, zenithCol, viewDir, FOG_COLOR, t, -wPos.y, rainFactor, end, underWater, nether, wPos, lit.y);
        Refl.a = calculateFresnel(cosR, 0.03)*NLC_END_REFLECTION;

        // fade out before clip
        Refl.a *= clamp(2.0-2.0*camDist/endDist, 0.0, 1.0);
    }
  }
}
  return Refl;
}

#endif
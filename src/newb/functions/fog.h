#ifndef FOG_H
#define FOG_H

#include "tonemap.h"

float nlcMistDensity(vec3 FOG_COLOR, bool end, float uv1)
{
  if(end){
    return NLC_MIST_DENS_END;
  }else{
    return mix(mix(mix(NLC_MIST_DENS_NOON, NLC_MIST_DENS_DAWN, duskD(FOG_COLOR)), NLC_MIST_DENS_NIGHT, nightD(FOG_COLOR)), 0.1, (1.0-uv1));
  }
}

float nlRenderFogFade(float relativeDist, vec3 FOG_COLOR, vec2 FOG_CONTROL, vec2 uv1, bool end) {
#if NL_FOG_TYPE == 0
  // no fog
  return 0.0;
#else
  #if NL_FOG_TYPE == 1
    // linear transition
    float fade = clamp((relativeDist-FOG_CONTROL.x)/(FOG_CONTROL.y-FOG_CONTROL.x), 0.0, 1.0);
  #else
    // smoother transition
    float fade = smoothstep(FOG_CONTROL.x, FOG_CONTROL.y, relativeDist);
  #endif

  // misty effect
  float density = nlcMistDensity(FOG_COLOR, end, uv1.y)*(19.0 - 18.0*FOG_COLOR.g);
  fade += (1.0-fade)*(0.3-0.3*exp(-relativeDist*relativeDist*density));

  return fade;
#endif
}

float nlRenderGodRayIntensity(vec3 cPos, vec3 worldPos, float t, vec2 uv1, float relativeDist, vec3 FOG_COLOR, float fogColor)
{
vec3 offset = cPos - 16.0*fract(worldPos*0.0625);
offset = abs(2.0*fract(offset*0.0625)-1.0);
offset = offset*offset*(3.0-2.0*offset);

vec3 nrmof = normalize(worldPos);

float u = nrmof.z/length(nrmof.zy);
float diff = dot(offset,vec3(0.1,0.2,1.0)) + 0.07*t;
float mask = nrmof.x*nrmof.x;

float vol = sin(7.0*u + 1.5*diff)*cos(3.0*u + diff);
vol += cos(5.0*u + 0.4*diff)*sin(4.0*u + 0.7*diff);
vol *= vol*mask*uv1.y;
vol *= min(7.0*relativeDist*(1.0-mask),1.0);
vol *= clamp(3.0*(FOG_COLOR.r-FOG_COLOR.b),0.0,1.0);
vol = clamp(vol,0.0,1.0);

return fogColor + 0.3*vol*(1.0-fogColor);
}

#endif

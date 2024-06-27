#ifndef NOISE_H
#define NOISE_H

#include "constants.h"

// hash function for noise (for highp only)
highp float rand(highp vec2 n) {
  return fract(cos(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

// rand with transition
float randt(vec2 n, vec2 t) {
  return smoothstep(t.x, t.y, rand(n));
}

// 1D noise - used in plants,lantern wave
highp float noise1D(highp float x) {
  float x0 = floor(x);
  float t0 = x-x0;
  t0 *= t0*(3.0-2.0*t0);
  return mix(fract(sin(x0)*84.85), fract(sin(x0+1.0)*84.85), t0);
}

// simpler rand for disp, puddles
float fastRand(vec2 n){
  return fract(37.45*sin(dot(n, vec2(4.36, 8.28))));
}

// water displacement map (also used by caustic)
float disp(vec3 pos, highp float t) {
  float val = 0.5 + 0.5*sin(t*1.7 + (pos.x+pos.y)*NL_CONST_PI_HALF);
  return mix(fastRand(pos.xz), fastRand(pos.xz+vec2_splat(1.0)), val);
}

// hash function for shooting stars
highp float hashS (highp vec2 x)
{
return fract(sin(dot(
	x,vec2(11,57)))*4e3);
}

// for end sky stars and sunrays
float hash13(vec3 p3)
{
	p3  = fract(p3 * vec3(.1031,.11369,.13787));
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

float hash1(vec2 p){
  vec2 v = vec2(NLC_CONST_PI*1453.0,exp(1.)*3054.0);
  return fract(sin(dot(p,v)*0.1)*4323.0);
}

#endif

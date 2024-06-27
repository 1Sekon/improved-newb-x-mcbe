$input v_texcoord0, v_posTime, v_sPos

#define NL_GLOW_LEAK 0.8

#include <bgfx_shader.sh>
#include <newb/main.sh>

uniform vec4 ViewPositionAndTime;

SAMPLER2D(s_MatTexture, 0);

void main() {
  vec4 diffuse = texture2D(s_MatTexture, v_texcoord0);
  vec3 bloom1 = nlGlow(s_MatTexture, v_texcoord0, diffuse, nlGlowShimmer(normalize(v_posTime.xyz), ViewPositionAndTime.w), 256.0, 256.0);
  vec3 nPos = normalize(v_posTime.xyz);

  // end sky gradient
  vec3 color = renderEndSky(getEndHorizonCol(), getEndZenithCol(), normalize(v_posTime.xyz), v_posTime.w);

  // stars
  //diffuse.rgb += bloom1;
  //color += diffuse.rgb;
  
  float s = endStars(nPos, ViewPositionAndTime.w);
	color += HorizonMask(vec3(0.0), vec3(s*0.7, s*hash13(abs(nPos)), s*0.9), nPos);

  color = colorCorrection(color);

  gl_FragColor = vec4(color, 1.0);
}

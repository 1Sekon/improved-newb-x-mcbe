$input v_color0
#include <newb/config.h>
#if defined(TRANSPARENT) && NL_CLOUD_TYPE == 2
  $input v_color1, v_color2, v_fogColor, v_horizon
#endif

#include <bgfx_shader.sh>
#include <newb/main.sh>

uniform vec4 FogColor;

void main() {
  vec4 color = v_color0;
  
#if defined(TRANSPARENT) && NL_CLOUD_TYPE == 2
  vec3 vDir = normalize(v_color0.xyz);
  bool underWater = v_horizon.a > 0.5;
  vec3 rsky = nlRenderSky(v_color2.rgb, v_horizon.rgb, v_color1.rgb, -vDir, v_color2.a, v_color1.a, false, underWater, false, FogColor.rgb, 1.0);

  color = renderClouds(vDir, v_color0.xyz, v_color1.a, v_color2.a, rsky, rsky, FogColor.rgb);

  #ifdef NL_CLOUD2_MULTILAYER
    vec2 parallax = vDir.xz / abs(vDir.y) * 120.0;
    vec3 offsetPos = v_color0.xyz;
    offsetPos.xz += parallax;
    vec4 color2 = renderClouds(vDir, offsetPos, v_color1.a, v_color2.a*0.7, rsky, rsky, FogColor.rgb);
    color = mix(color2, color, 0.2 + 0.8*color.a);
  #endif
  
  color.a *= v_color0.a;
  color.rgb = colorCorrection(color.rgb);
#endif

  gl_FragColor = color;
}

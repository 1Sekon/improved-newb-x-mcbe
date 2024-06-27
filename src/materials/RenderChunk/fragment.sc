$input v_color0, v_color1, v_fog, v_refl, v_EndRefl, v_texcoord0, v_lightmapUV, v_extra, v_cPos, v_wPos, v_viewDir, v_horizonCol, v_zenithCol, v_rainTime

#include <bgfx_shader.sh>
#include <newb/main.sh>

uniform vec4 ViewPositionAndTime;
uniform vec4 FogColor;
uniform vec4 FogAndDistanceControl;
uniform vec4 GlobalRoughness;

SAMPLER2D_AUTOREG(s_MatTexture);
SAMPLER2D_AUTOREG(s_SeasonsTexture);
SAMPLER2D_AUTOREG(s_LightMapTexture);

void main() {
  vec4 diffuse;
  vec4 color;

  vec4 dPd = vec4(dFdx(v_texcoord0), dFdy(v_texcoord0));

  float maxAnisotropy = 16.0;
  float lenDx = length(dPd.xy);
  float lenDy = length(dPd.zw);

  float ratio = max(lenDx, lenDy) / min(lenDx, lenDy);
  ratio = min(ratio, maxAnisotropy);
  if (lenDx > lenDy) {
  dPd.zw *= ratio;
  } else {
  dPd.xy *= ratio;
  }

#if defined(DEPTH_ONLY_OPAQUE) || defined(DEPTH_ONLY)
  diffuse = vec4(1.0,1.0,1.0,1.0);
  color = vec4(1.0,1.0,1.0,1.0);
#else
  diffuse.rgb = texture2DGrad(s_MatTexture, v_texcoord0, dPd.xy, dPd.zw).rgb;
  diffuse.a = texture2DLod(s_MatTexture, v_texcoord0, 0.0).a;

#ifdef ALPHA_TEST
  if (diffuse.a < 0.6) {
    discard;
  }
#endif

#if defined(SEASONS) && (defined(OPAQUE) || defined(ALPHA_TEST))
  diffuse.rgb *= mix(vec3(1.0,1.0,1.0), texture2D(s_SeasonsTexture, v_color1.xy).rgb * 2.0, v_color1.z);
#endif
  color = v_color0;
#endif

  diffuse.rgb *= diffuse.rgb;

  vec3 lightTint = texture2DGrad(s_LightMapTexture, v_lightmapUV, dPd.xy, dPd.zw).rgb;
  lightTint = mix(lightTint.bbb, lightTint*lightTint, 0.35 + 0.65*v_lightmapUV.y*v_lightmapUV.y*v_lightmapUV.y);

  color.rgb *= lightTint;

  vec3 glow = nlGlow(s_MatTexture, v_texcoord0, diffuse, v_extra.a, 2048.0, 1024.0);

#ifdef TRANSPARENT
  if (v_extra.b > 0.9) {
    diffuse.rgb = vec3_splat(1.0 - NL_WATER_TEX_OPACITY*(1.0 - diffuse.b*1.8));
    diffuse.a = color.a;
  }
#else
  diffuse.a = 1.0;
#endif

  diffuse.rgb *= color.rgb;
  diffuse.rgb += glow;

  if (v_extra.b > 0.9) {
    diffuse.rgb += v_refl.rgb*v_refl.a;
  } else if (v_refl.a > 0.0) {
    // reflective effect - only on xz plane
    float dy = abs(dFdy(v_extra.g));
    if (dy < 0.0002) {
      float mask = v_refl.a*(clamp(v_extra.r*10.0,8.2,8.8)-7.8);
      diffuse.rgb *= 1.0 - 0.6*mask;
      diffuse.rgb += v_refl.rgb*mask;
    }
  }

// end reflection effects
  if (v_extra.b > 0.9) {
    diffuse.rgb += v_EndRefl.rgb*v_EndRefl.a;
  } else if (v_EndRefl.a > 0.0) {
    // reflective effect - only on xz plane
    float dy = abs(dFdy(v_extra.g));
    if (dy < 0.0002) {
      float mask = v_EndRefl.a*(clamp(v_extra.r*10.0,8.2,8.8)-7.8);
      diffuse.rgb *= 1.0 - 0.6*mask;
      diffuse.rgb += v_EndRefl.rgb*mask;
    }
  }

  diffuse.rgb = mix(diffuse.rgb, v_fog.rgb, v_fog.a);

  diffuse.rgb = colorCorrection(diffuse.rgb);

#ifdef NLC_FAKE_DEPTH_TEX
  diffuse.rgb = mix(diffuse.rgb, nlcFakeDepthMap(s_MatTexture, diffuse.rgb, v_texcoord0, v_lightmapUV, vec2(0.00008, 0.000145), dPd), (1.0-v_fog.a));
#endif

//diffuse = texture2D(s_MatTexture, v_cPos.xz*16.0);

  gl_FragColor = diffuse;
}

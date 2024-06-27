$input v_texcoord0, v_fogColor, v_worldPos, v_underwaterRainTime, v_sPos

#include <bgfx_shader.sh>
#include <newb/main.sh>

SAMPLER2D(s_MatTexture, 0);

uniform vec4 FogColor;
uniform vec4 FogAndDistanceControl;

void main() {
  vec4 diffuse = texture2D(s_MatTexture, v_texcoord0);

  vec3 viewDir = normalize(v_worldPos);
  bool nether = detectNether(FogColor.rgb, FogAndDistanceControl.xy);
  bool underWater = v_underwaterRainTime.x > 0.5;
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

  float fade = clamp(-10.0*viewDir.y, 0.0, 1.0);
  vec4 color = vec4(colorCorrection(skyColor), fade);

  diffuse = mix(color, diffuse, diffuse.a);

  gl_FragColor = diffuse;
}

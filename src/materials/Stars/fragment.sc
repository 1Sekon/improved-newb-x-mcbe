$input v_color0, time, p

#include <bgfx_shader.sh>

uniform vec4 StarsColor;

void main() {
    vec4 starColor;
    starColor.a = v_color0.a;
    starColor.rgb = v_color0.rgb * StarsColor.rgb * v_color0.a;
    starColor.rgb *= sin(p.x+time + cos(p.y))*cos(3.*p.y+time*1.4);
    gl_FragColor = starColor;
}
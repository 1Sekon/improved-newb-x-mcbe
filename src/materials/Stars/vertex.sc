$input a_color0, a_position
$output v_color0, time, p

#include <bgfx_shader.sh>

uniform vec4 ViewPositionAndTime;

void main() {
    v_color0 = a_color0;
    time = ViewPositionAndTime.w;
    p = a_position;

    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}
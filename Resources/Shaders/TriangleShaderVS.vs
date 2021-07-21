attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_MVP;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position =  u_projection * u_view * u_MVP * posL;
v_uv = a_uv;
}
   
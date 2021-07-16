attribute vec3 a_posL;
attribute vec4 a_color;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec4 v_color;
uniform mat4 transform;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position =  transform * vec4(a_posL,1.0);
v_color = a_color;
v_uv = a_uv;
}
   
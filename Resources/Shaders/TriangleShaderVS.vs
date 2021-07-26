attribute vec3 a_posL;
varying vec3 v_pos; 
uniform vec3 u_texture;
uniform mat4 u_MVP;
void main()
{
v_pos = u_texture;
gl_Position =  u_MVP * vec4(a_posL, 1.0);
}
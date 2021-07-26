attribute vec4 a_CubeVertexPos;
attribute vec2 a_uv;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_MVP;
varying vec4 v_pos;
void main(void)
{
	gl_Position = u_projection * u_view * u_MVP * a_CubeVertexPos;
	v_pos = a_CubeVertexPos;
}
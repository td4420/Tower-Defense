precision mediump float;
varying vec3 v_pos;
uniform samplerCube u_Cubemap;
void main()
{
	gl_FragColor = textureCube(u_Cubemap,v_pos);
}
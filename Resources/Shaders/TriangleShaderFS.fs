precision mediump float;
varying vec2 v_uv;
varying vec4 v_color;
uniform sampler2D u_texture;
float near = 0.1; 
float far  = 100.0;
float LinearizeDepth(float depth)
{
	float z = depth*2.0 - 1.0;
	return (2.0 * near * far)/ (far + near - z *(far - near));
}
void main()
{
	float depth = LinearizeDepth(gl_FragColor.z)/far;
	gl_FragColor = texture2D(u_texture,v_uv);
	//gl_FragColor = vec4(vec3(depth),1.0);
}

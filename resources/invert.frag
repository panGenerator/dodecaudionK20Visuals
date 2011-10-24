uniform sampler2D tex0;
uniform float param1;


void main(){
	vec4 rgba = texture2D( tex0, gl_TexCoord[0].st );
	float r = param1 - rgba.r;
	float g = param1 - rgba.g;
	float b = param1 - rgba.b;
	
	gl_FragColor.rgb = vec3(abs(r),abs(g),abs(b));
	gl_FragColor.a = rgba.a;
}
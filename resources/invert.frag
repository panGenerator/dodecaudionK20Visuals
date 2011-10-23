uniform sampler2D tex0;
//uniform float framesCount;
uniform float value;

void main(){
	vec4 rgba = texture2D( tex0, gl_TexCoord[0].st );
	float r = value - rgba.r;
	float g = value - rgba.g;
	float b = value - rgba.b;
	
	gl_FragColor.rgb = vec3(abs(r),abs(g),abs(b));
	gl_FragColor.a = rgba.a;
}
uniform sampler2D tex0;
uniform float framesCount;

void main(){
	gl_FragColor.rgb = vec3(1,1,1) - texture2D( tex0, gl_TexCoord[0].st ).rgb;
	gl_FragColor.a = texture2D( tex0, gl_TexCoord[0].st ).a;
	
}
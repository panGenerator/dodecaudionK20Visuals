uniform sampler2D tex0;
uniform float framesCount;
uniform float rand;

void main(){
	vec3 rgb = texture2D( tex0, gl_TexCoord[0].st ).rgb;
	rgb.r = sqrt( rgb.r );
	rgb.g = sqrt( rgb.g );
	rgb.b = sqrt( rgb.b );

	gl_FragColor.rgb = rgb;
	gl_FragColor.a = texture2D( tex0, gl_TexCoord[0].st ).a;
	
}
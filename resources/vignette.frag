#version 110

uniform sampler2D tex0;
uniform float param1;

void main(){
	vec2 vTexCoord = gl_TexCoord[0].st;
	
	vec2 center = vec2(0.5,0.5);
	float radius = 1.5 + 2.0*param1;
	float dist = distance(center, vTexCoord) * radius;
	vec3 color = texture2D(tex0, vTexCoord).rgb;
	float alpha = texture2D(tex0, vTexCoord).a;
	
	alpha = (1.0 - dist*dist);
	
	gl_FragColor.rgb = texture2D( tex0, vTexCoord ).rgb;
	gl_FragColor.a = alpha;
}
#version 110

uniform sampler2D tex0;
uniform float seed;
uniform float framesCount;

//@see: http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(float seed, vec2 co){
    return fract(seed * sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


void main(){
	vec2 vTexCoord = gl_TexCoord[0].st;
	
	vec2 center = vec2(0.5,0.5);
	float radius = 1.5;
	radius *= (1.0+rand(seed,vTexCoord));
	float dist = distance(center, vTexCoord) * radius;
	vec3 color = texture2D(tex0, vTexCoord).rgb;
	float alpha = texture2D(tex0, vTexCoord).a;
	
	alpha = (1.0 - dist);
	
	gl_FragColor.rgb = texture2D( tex0, vTexCoord ).rgb;
	gl_FragColor.a = alpha;
}
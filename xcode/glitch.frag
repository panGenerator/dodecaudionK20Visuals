#version 110

uniform sampler2D tex0;
uniform float seed;
uniform float framesCount;
uniform float param1;
uniform float param2;
uniform float param23; 

float areaSize;
float glitchAmount;
float _rnd;

//@see: http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(float seed, vec2 co){
    return fract(seed * sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


void main(){
	_rnd = param23;
	glitchAmount = param1;
	areaSize = 0.01 * param2;
	
	vec2 vTexCoord = gl_TexCoord[0].st;
	vec3 color = texture2D(tex0, vTexCoord).rgb;

	bool glitchUp = rand( _rnd , vTexCoord ) > (1.0-glitchAmount) ? true : false;
	//not every available part of texture has to be changed so do it at pseudorandom
	if( glitchUp ){
		for( float a = 0.0 ; a < areaSize ; a+=0.01 ){
			_rnd = rand( param23 * param2*param1 , vec2( param1*param2 , param2*param2 ) );	
			vec2 offset = 10.0*vec2( rand( _rnd , vec2( param1 , param1*param23 ) ) , rand( _rnd , vec2( param23 , 1.0-param23) ) );

			//if true mess up the colors
			if( _rnd >= 0.5 ){
				color = vec3(1,_rnd,1.0-_rnd) - color;
			}else{
				color = color + texture2D(tex0, vTexCoord+offset).rgb / areaSize;	
			}
		}
		
	
	}
	gl_FragColor.rgb = color;
}
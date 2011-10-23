#version 110

uniform sampler2D tex0;
uniform float seed;

//@see: http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(float seed, vec2 co){
    return fract(seed * sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	gl_FragColor.rgb = texture2D( tex0 , gl_TexCoord[0].st ).rgb;
	gl_FragColor.a = 1.0 - 0.2*rand( seed, gl_TexCoord[0].st );
}
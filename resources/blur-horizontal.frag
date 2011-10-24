/**
 * @see: http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/
 */
uniform sampler2D tex0; // the texture with the scene you want to blur
float blendMultiplier = 1.0;
float blurSize = 0.0005;//1.0/512.0;
uniform float param1;
uniform float param2;
 
void main(void)
{
	vec4 sum = vec4(0.0);
	vec2 vTexCoord = vec2( gl_TexCoord[0].x , gl_TexCoord[0].y );
 
	blurSize += 0.1 * param1;
	blendMultiplier += 0.5 * param2; 
 
   // take nine samples, with the distance blurSize between them
   sum += texture2D(tex0, vec2(vTexCoord.x + 4.0*blurSize, vTexCoord.y)) * (0.05+0.03)*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x + 3.0*blurSize, vTexCoord.y)) * 0.09*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x + 2.0*blurSize, vTexCoord.y)) * 0.12*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x + blurSize, vTexCoord.y)) * (0.15)*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y)) * 0.16*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x - blurSize, vTexCoord.y)) * (0.15)*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x - 2.0*blurSize, vTexCoord.y)) * 0.12*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x - 3.0*blurSize, vTexCoord.y)) * 0.09*blendMultiplier;
   sum += texture2D(tex0, vec2(vTexCoord.x - 4.0*blurSize, vTexCoord.y)) * (0.05+0.03)*blendMultiplier;
 
   gl_FragColor = sum;
}
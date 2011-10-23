/**
 * @see: http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/
 */
uniform sampler2D tex0; // the texture with the scene you want to blur
//varying vec2 vTexCoord;
 
const float blurSize = 0.00001;//1.0/1024.0; // I've chosen this size because this will result in that every step will be one pixel wide if the tex0 texture is of size 512x512
 
void main(void)
{
	vec4 sum = vec4(0.0);
	vec2 vTexCoord = vec2( gl_TexCoord[0].x , gl_TexCoord[0].y );
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   //sum += texture2D(tex0, vec2(vTexCoord.x + 4.0*blurSize, vTexCoord.y)) * 0.05;
   //sum += texture2D(tex0, vec2(vTexCoord.x + 3.0*blurSize, vTexCoord.y)) * 0.09;
   sum += texture2D(tex0, vec2(vTexCoord.x + 2.0*blurSize, vTexCoord.y)) * 0.12;
   sum += texture2D(tex0, vec2(vTexCoord.x + blurSize, vTexCoord.y)) * (0.15+0.14);
   sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y)) * 0.16;
   sum += texture2D(tex0, vec2(vTexCoord.x - blurSize, vTexCoord.y)) * (0.15+0.14);
   sum += texture2D(tex0, vec2(vTexCoord.x - 2.0*blurSize, vTexCoord.y)) * 0.12;
   //sum += texture2D(tex0, vec2(vTexCoord.x - 3.0*blurSize, vTexCoord.y)) * 0.09;
   //sum += texture2D(tex0, vec2(vTexCoord.x - 4.0*blurSize, vTexCoord.y)) * 0.05;
 
   gl_FragColor = sum;
}
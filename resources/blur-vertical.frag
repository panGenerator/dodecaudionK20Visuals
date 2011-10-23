/**
 * @see: http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/
 */
uniform sampler2D tex0; 
const float blurSize = 0.00001;//1.0/512.0;

void main(void)
{
	vec4 sum = vec4(0.0);
	vec2 vTexCoord = vec2( gl_TexCoord[0].x , gl_TexCoord[0].y );


	//sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y + 4.0*blurSize)) * 0.05;
	//sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y + 3.0*blurSize)) * 0.09;
	sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y + 2.0*blurSize)) * 0.12;
	sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y + blurSize)) * (0.15+0.14);
	sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y)) * 0.16;
	sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y - blurSize)) * (0.15+0.14);
	sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y - 2.0*blurSize)) * 0.12;
	//sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y - 3.0*blurSize)) * 0.09;
	//sum += texture2D(tex0, vec2(vTexCoord.x, vTexCoord.y - 4.0*blurSize)) * 0.05;

	gl_FragColor = sum;
}
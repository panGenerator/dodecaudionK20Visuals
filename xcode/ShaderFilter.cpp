/*
 *  GenericFilter.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ShaderFilter.h"

#pragma mark Constructors/destructors

ShaderFilter::ShaderFilter()
{
}

#pragma mark Filter interface implementation

/**
 * Setup the controller
 */
void ShaderFilter::setup(string id, DataSourceRef vertShader, DataSourceRef fragShader, Vec2i size)
{
	_id = id;
	shader = gl::GlslProg( vertShader , fragShader );
	
	//init FBO
	fboFormat.setSamples(4);
	fboFormat.enableMipmapping(false);
	fboFormat.setCoverageSamples(16);
	
	resize(size);
}

/**
 * Inform that the application size changed
 */
void ShaderFilter::resize(Vec2i size)
{
	fbo = gl::Fbo( size.x , size.y ,fboFormat);	
}

/**
 * Recalculate values
 */
void ShaderFilter::update()
{
	_values.set( "rand" , (float)rand()/RAND_MAX );	
}

/**
 * Perform filtering
 */
void ShaderFilter::apply(gl::Texture *texture)
{
	/*
	 * All drawing is done int an FBO since this is the only way i found to execute
	 * many GLSL fragment programs on one (not exactly the same memory-wise) texture
	 * as a sequence of effects. Does seem far from opitmal but i haven't noticed any 
	 * performance drops
	 */
	
	fbo.bindFramebuffer();
	(*texture).enableAndBind();
	shader.bind();
	
	shader.uniform("tex0",0);
	shader.uniform("seed", get("rand"));
	shader.uniform("framesCount", get("framesCount"));
	
	gl::clear( ColorAf(0,0,0) );
	gl::setViewport( getWindowBounds() );
	gl::setMatricesWindow( getWindowSize() );
	gl::color( ColorAf( 1,1,1,1 ) );
	gl::drawSolidRect( getWindowBounds() );
	

	shader.unbind();
	(*texture).unbind(0);	
	fbo.unbindFramebuffer();
	*texture = fbo.getTexture();
}

/**
 * Set value of the controlled param 
 */
void ShaderFilter::set(string key, float value)
{
	_values.set( key , value );
}

/**
 * Get value for key. Always returns a value. 0 if it's not defined
 */
float ShaderFilter::get(string key)
{
	return _values.get( key );
}

/**
 * List all available 
 */
vector<string> ShaderFilter::keys()
{
	return _values.keys();
}

/**
 * 
 */
string ShaderFilter::getId()
{
	return _id;
}

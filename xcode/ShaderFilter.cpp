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
void ShaderFilter::setup(DataSourceRef vertShader, DataSourceRef fragShader)
{
	shader = gl::GlslProg( vertShader , fragShader );
}

/**
 * Recalculate values
 */
void ShaderFilter::update()
{
	_values.set( "rand" , rand() );	
}

void ShaderFilter::bind()
{
	shader.bind();
	shader.uniform("tex0",0);
}


void ShaderFilter::unbind()
{
	shader.unbind();
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
	return std::string("generic");
}

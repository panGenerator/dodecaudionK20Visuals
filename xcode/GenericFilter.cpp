/*
 *  GenericFilter.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GenericFilter.h"

#pragma mark Constructors/destructors

GenericFilter::GenericFilter()
{
}

#pragma mark Filter interface implementation

/**
 * Setup the controller
 */
void GenericFilter::setup()
{
    
}

/**
 * Recalculate values
 */
void GenericFilter::update()
{
	_values.set( "rand" , rand() );
}

void GenericFilter::apply(gl::Texture *texture)
{
	
}

/**
 * Set value of the controlled param 
 */
void GenericFilter::set(string key, float value)
{
	_values.set( key , value );
}

/**
 * Get value for key. Always returns a value. 0 if it's not defined
 */
float GenericFilter::get(string key)
{
	return _values.get( key );
}

/**
 * List all available 
 */
vector<string> GenericFilter::keys()
{
	return _values.keys();
}

/**
 * 
 */
string GenericFilter::getId()
{
	return std::string("generic");
}

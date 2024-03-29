/*
 *  RandomController.c
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GenericController.h"

#pragma mark Constructors/destructors

GenericController::GenericController()
{
}

#pragma mark Controller interface implementation

/**
 * Setup the controller
 */
void GenericController::setup()
{
    
}

/**
 * Recalculate values
 */
void GenericController::update()
{
	_values.set( "rand" , rand() );
}
/**
 * Set value of the controlled param 
 */
void GenericController::set(string key, float value)
{
	_values.set( key , value );
}

/**
 * Get value for key. Always returns a value. 0 if it's not defined
 */
float GenericController::get(string key)
{
	return _values.get( key );
}

/**
 * List all available 
 */
vector<string> GenericController::keys()
{
	return _values.keys();
}

/**
 * 
 */
string GenericController::getId()
{
	return std::string("generic");
}

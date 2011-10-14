/*
 *  RandomController.c
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GenericController.h"

GenericController::GenericController()
{
}

void GenericController::update()
{
	_value = rand();
}
/**
 * Set value of the controlled param
 */
void GenericController::set(std::string key, float value)
{
    _value = value;
}

/**
 * Get it's value
 */
float GenericController::get(std::string key)
{
    return _value;
}

std::string GenericController::getId()
{
	return std::string("genericController");
}

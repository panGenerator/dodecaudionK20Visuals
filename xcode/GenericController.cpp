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
	//_value = rand();
    _values["rand"] = rand();
}
/**
 * Set value of the controlled param 
 */
void GenericController::set(string key, float value)
{
    _values[key] = value;
}

/**
 * Get value for key. Always returns a value. 0 if it's not defined
 */
float GenericController::get(string key)
{
	return _values[key];
}

/**
 * List all available 
 */
vector<string> GenericController::keys()
{
    vector<string> list;
    
    for( map<string,float>::iterator it = _values.begin() ; it != _values.end() ; ++it ){
        string key = it->first;
        list.push_back(key);
    }
    
    return list;
}

/**
 * 
 */
string GenericController::getId()
{
	return std::string("genericController");
}

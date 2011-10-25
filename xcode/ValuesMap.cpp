/*
 *  ValuesMap.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ValuesMap.h"

ValuesMap::ValuesMap()
{
}

void ValuesMap::set(string key, float value)
{
	_values[ key ] = value;
}

/**
 * Set value as transitory - readable only once
 */
void ValuesMap::transitorySet(string key, float value)
{
	markAsTransitory(key,true);
	set( key , value );	
}

/**
 * Mark variable as readable only once. Useful for all kind of triggers
 */
void ValuesMap::markAsTransitory(string key, bool transitory)
{
	_transitoryValuesFlag[ key ] = transitory;
}

/**
 * Release all transitory variables
 */
void ValuesMap::releaseTransitory()
{
    for( map<string,float>::iterator it = _values.begin() ; it != _values.end() ; ++it ){
        string key = it->first;
        get( key ); //into the void
    }	
}

float ValuesMap::get(string key)
{
	float returnValue = _values[ key ]; 
	
	if( _transitoryValuesFlag[ key ] ){
		_values[ key ] = 0;
		markAsTransitory(key,false);
	}
	
	return returnValue;
}

float ValuesMap::get(string key, bool persistTransitory)
{
	float val = _values[key];
	transitorySet(key, val);
	return val;	
}

vector<string> ValuesMap::keys()
{
    vector<string> list;
    
    for( map<string,float>::iterator it = _values.begin() ; it != _values.end() ; ++it ){
        string key = it->first;
        list.push_back(key);
    }
    
    return list;	
}

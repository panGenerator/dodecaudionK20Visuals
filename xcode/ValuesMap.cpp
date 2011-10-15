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

float ValuesMap::get(string key)
{
	return _values[ key ];
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

/*
 *  ValuesMap.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef VALUES_MAP_INCLUDED
#define VALUES_MAP_INCLUDED


#include <string>
#include <map>
#include <vector>

using namespace std;

class ValuesMap 
{
public:
	ValuesMap();
	void set(string key, float value);
	float get(string key);
    vector<string> keys();
	
private: 
	map<string,float> _values;

};

#endif
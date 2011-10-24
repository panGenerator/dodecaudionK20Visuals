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
	void transitorySet(string key, float value);
	void markAsTransitory(string key, bool transitory);
	float get(string key);
	float getTransitory(string key);
    vector<string> keys();
	
private: 
	map<string,float> _values;
	map<string,bool> _transitoryValuesFlag;
};

#endif
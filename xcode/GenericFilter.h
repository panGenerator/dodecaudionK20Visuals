/*
 *  GenericFilter.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GENERIC_FILTER_INCLUDED
#define GENERIC_FILTER_INCLUDED


#include "Filter.h"
#include "ValuesMap.h"

using namespace ci;


class GenericFilter : public Filter
{
public:
	GenericFilter();
	void setup();
	void update();
	void apply(gl::Texture *texture);
	void set(string key, float value);
	float get(string key);
    vector<string> keys();
	string getId();
	
protected:
    ValuesMap _values;
	
};

#endif
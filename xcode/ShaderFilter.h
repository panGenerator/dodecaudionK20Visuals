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
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/CinderResources.h"


//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class ShaderFilter : public Filter
{
public:
	ShaderFilter();
	void setup(DataSourceRef vertShader, DataSourceRef fragShader);
	void update();
	void bind();
	void unbind();
	void set(string key, float value);
	float get(string key);
    vector<string> keys();
	string getId();
	
protected:
    ValuesMap _values;
	gl::GlslProg shader;
};

#endif
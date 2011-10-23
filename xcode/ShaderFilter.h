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
#include "cinder/gl/Fbo.h"
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
	void setup(string id,DataSourceRef vertShader, DataSourceRef fragShader, Vec2i size);
	void resize(Vec2i size);
	void update();
	void apply(gl::Texture *texture);
	void set(string key, float value);
	float get(string key);
    vector<string> keys();
	string getId();
	
protected:
	std::string _id;
	ValuesMap _values;
	gl::GlslProg shader;
	gl::Fbo fbo;
	gl::Fbo::Format fboFormat;
};

#endif
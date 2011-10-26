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

#define FILTER_SHADER_PARAM_1 "param1"
#define FILTER_SHADER_PARAM_2 "param2"
#define FILTER_SHADER_PARAM_3 "param3"
#define FILTER_SHADER_PARAM_4 "param4"
#define FILTER_SHADER_PARAM_5 "param5"
#define FILTER_SHADER_PARAM_6 "param6"
#define FILTER_SHADER_PARAM_7 "param7"
#define FILTER_SHADER_PARAM_8 "param8"
#define FILTER_SHADER_PARAM_9 "param9"
#define FILTER_SHADER_PARAM_23 "param23"
#define FILTER_SHADER_EASE_PARAM_1 "ease1"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class ShaderFilter : public Filter
{
public:
	ShaderFilter();
	void setup(string id,DataSourceRef vertShader, DataSourceRef fragShader, Vec2i size);
	//void resize(Vec2i size);
	void setFBO(gl::Fbo *fbo);
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
	gl::Fbo *_fbo;
};

#endif
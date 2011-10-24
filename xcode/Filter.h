/*
 *  Filter.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FILTER_INCLUDED
#define FILTER_INCLUDED

#include "cinder/DataSource.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Fbo.h"
#include "Controllable.h"

using namespace ci;


class Filter : public Controllable{
	
public: 
	virtual ~Filter(){}
	
	virtual void setup(string id, DataSourceRef vertShader, DataSourceRef fragShader, Vec2i size) = 0;
	//virtual void resize(Vec2i size) = 0;
	virtual void setFBO(gl::Fbo *fbo) = 0;
	virtual void update() = 0;
	virtual void apply(gl::Texture *texture) = 0;	
};

#endif
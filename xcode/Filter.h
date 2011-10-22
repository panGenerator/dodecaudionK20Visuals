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
#include "Controllable.h"

using namespace ci;


class Filter : public Controllable{
	
public: 
	virtual ~Filter(){}
	
	virtual void setup(DataSourceRef vertShader, DataSourceRef fragShader) = 0;
	virtual void update() = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	
};

#endif
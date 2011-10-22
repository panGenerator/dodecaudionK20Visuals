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

#include "Controllable.h"
#include "cinder/gl/Texture.h"

using namespace ci;

class Filter : public Controllable{
	
public: 
	virtual ~Filter(){}
	
	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void apply(gl::Texture *texture) = 0;
};

#endif
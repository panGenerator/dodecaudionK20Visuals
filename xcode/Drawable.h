/*
 *  Drawable.h
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWABLE_INCLUDED
#define DRAWABLE_INCLUDED

#include "Controllable.h"

class Drawable : public Controllable
{
	public:
		virtual ~Drawable(){}
	
		virtual void setup() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

};

#endif
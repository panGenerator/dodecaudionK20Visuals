/*
 *  Particle.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "Drawable.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace std;
using namespace ci;
using namespace ci::app;


class Particle : public Drawable {
	
public:
	Particle();
	
	void update();
	void draw();
	
	
	float pSize;
	float pColor;
	float pRotationSpeed;
	Vec3f position;
	Vec3f rotation;
	
	
	
};

/*
 *  ParticlesHolder.h
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


class ParticlesHolder : public Drawable {
	
public:
	ParticlesHolder();
	
	void setup();
	void update();
	void draw();
	
	
	int particlesCount;
	
private: 
	
	void drawParticles();
	
	
	
};



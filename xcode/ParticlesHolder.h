/*
 *  ParticlesHolder.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Drawable.h"
#include "Particle.h"
#include "ValuesMap.h"


#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace std;
using namespace ci;
using namespace ci::app;


class ParticlesHolder : public Drawable {
	
public:
	ParticlesHolder();
	~ParticlesHolder();
	
	void setup();
	void update();
	void draw();
	
	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();	
	
	int particlesCount;
	std::vector<Particle *> particles;
	float maxX;
	float maxY;
	float maxZ;
	
private: 
	ValuesMap _values; 	

	void drawParticles();
	
	
	
};



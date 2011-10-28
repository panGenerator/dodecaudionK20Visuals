/*
 *  Grid.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/28/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWABLE_JKDRAWER_INCLUDED
#define DRAWABLE_JKDRAWER_INCLUDED

#include "Drawable.h"
#include "ValuesMap.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include "cinder/Rand.h"

#include "Tri.h"

#define DRAWABLE_JKDRAWER_SPHERE_RADIUS "sphereRadius"

#define DRAWABLE_JKDRAWER_TORUS_OFFSET "torusOffset"
#define DRAWABLE_JKDRAWER_TORUS_AMPLITUDE "torusAmplitude"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class JKDrawer : public Drawable
{
public:
    JKDrawer();
    ~JKDrawer();
	
	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();
	
	void setup();
	void update();
	void draw();
	
private:	
	void setupTorus();
	void setupParticles();	
	void drawSphere();
	void drawTorus();
	void drawTestCube();
	void drawParticles();
	
	ValuesMap _values; 	
	//gl::Texture mBg;
	std::vector<Tri>mTris;	
	float particlesDensity;
	
	float torusAngleOffset,torusAmplitude;
	float sphereRadius;
};

#endif
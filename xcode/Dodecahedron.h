/*
 *  Dodecahedron.h
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWABLE_DODECAHEDRON_INCLUDED
#define DRAWABLE_DODECAHEDRON_INCLUDED

#include "Drawable.h"
#include "Controller.h"

#include "ValuesMap.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"


//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class Dodecahedron : public Drawable
{
public:
    Dodecahedron();
    ~Dodecahedron();
	
	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();

	void setup();
	void update();
	void draw();	
	
private:
	void __updateVertices();
	void __drawVertices( int vIdx1 , int vIdx2 , int vIdx3 , int vIdx4 , int vIdx5 );

	std::vector<Vec3f> vertices;
	
	ValuesMap _values;    

	//Model / drawing related parameters
	float radius;
	Vec3f modelRotation;
	ColorAf edgesColor;
};

#endif
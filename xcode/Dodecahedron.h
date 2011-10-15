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

#include "GenericController.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#define VERTICES_PER_WALL 5

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class Dodecahedron : public Drawable
{
public:
    Dodecahedron();
    ~Dodecahedron();
	
	void update();
	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();
	void draw();

private:
	void __updateVertices();
	void __drawVertices( int vIdx1 , int vIdx2 , int vIdx3 , int vIdx4 , int vIdx5 );

	std::vector<Vec3f> vertices;
	
	GenericController _values;    

	float modelRotationZ;
};

#endif
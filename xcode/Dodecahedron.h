/*
 *  Dodecahedron.h
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Drawable.h"
#include "Controller.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#define VERTICES_PER_WALL 5

//work in the cinder's namespace
using namespace ci;
using namespace ci::app;


class Dodecahedron : public Drawable
{
public:
    Dodecahedron();
    ~Dodecahedron();
	
	void update();
	void set(std::string key, float value);
	float get(std::string key);	
	void draw();
	std::string getId();

private:
	void __updateVertices();
	void __drawVertices( int vIdx1 , int vIdx2 , int vIdx3 , int vIdx4 , int vIdx5 );

	std::vector<Vec3f> vertices;
	
	float _value;
	float modelRotationZ;
	
    
};

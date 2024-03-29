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


#define WALL_COUNT 12
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
	
	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();

	void setup();
	void update();
	void draw();	
	
private:
	void updateVertices();
	void calcWallCenters();
	void calcWallCoordinateSystems();
	
	void transformToWallCoordinateSystem( int wall );
	void popWallCoordinateSystem();
	
	void drawWall( int wall );
	void drawSonicCones( int wall );	

	void __drawWallCenter( int wall );
	void __drawWallCoordinateSystem( int wall );
	
	
	Vec3f vertices[WALL_COUNT*VERTICES_PER_WALL];
	Vec3f wallCenters[WALL_COUNT];
	//Vec3f wallNormals[WALL_COUNT];
	Vec3f wallCoordinateSystems[WALL_COUNT][3];
	
	ValuesMap _values;    

	//Model / drawing related parameters
	float radius;
	Vec3f modelRotation;
	ColorAf edgesColor;
	
};

#endif
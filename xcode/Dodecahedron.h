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
#include "ValuesMap.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <boost/lexical_cast.hpp>

#define WALL_COUNT 12
#define VERTICES_PER_WALL 5

#define DRAWABLE_DODECAHEDRON_VAR_WALL_ "dodecahedronWall"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_1 "dodecahedronWall1"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_2 "dodecahedronWall2"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_3 "dodecahedronWall3"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_4 "dodecahedronWall4"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_5 "dodecahedronWall5"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_6 "dodecahedronWall6"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_7 "dodecahedronWall7"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_8 "dodecahedronWall8"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_9 "dodecahedronWall9"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_10 "dodecahedronWall10"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_11 "dodecahedronWall11"
#define DRAWABLE_DODECAHEDRON_VAR_WALL_12 "dodecahedronWall12"

#define DEBUG_WALL 1

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
	int __debugSelectedWall;
	std::vector<Vec3f> getWallAnchorVertices( int wall );
	void updateVertices();
	void calcWallCenters();
	void calcWallCoordinateSystems();
	
	void transformToWallCoordinateSystem( int wall );
	void popWallCoordinateSystem();
	
	void drawWall( int wall );
	void drawEye( int wall );
	void drawSonicCones( int wall );	
	
	void __drawWallCenter( int wall );
	void __drawWallCoordinateSystem( int wall );
	
	
	int wallsToDodecahedronFacesMap[WALL_COUNT];
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
/*
 *  Grid.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Grid.h"

#pragma mark Constructor / destructor

Grid::Grid()
{
}

Grid::~Grid()
{
}

#pragma mark Controllable interface implementation

/**
 *
 */
void Grid::set(std::string key, float value)
{
	_values.set( key , value );
}

/**
 *
 */
float Grid::get(std::string key)
{
	return _values.get( key );
}

/**
 * List all keys
 */
vector<string> Grid::keys()
{
	return _values.keys();
}


std::string Grid::getId()
{
	return "dodecahedron";
}



#pragma mark Drawable interface implementation


void Grid::setup()
{
}

/**
 * Update the modl state
 */
void Grid::update()
{
}

/**
 *
 */
void Grid::draw()
{
	glPushMatrix();
	
	glTranslated(-500, -300, 500);
	
	drawGrid();
	
	glRotated(-90, 1, 0, 0);
	drawGrid();
	
	glRotated(-90, 0, 1, 0);
	drawGrid();		
	glPopMatrix();
}


#pragma mark instance methods

void Grid::drawGrid(float size, float step)
{
	glPushMatrix();
	gl::color( Colorf(0.3f, 0.3f, 0.3f) );
	for(float x = 0 ; x <= size ; x+=step ){
		gl::drawLine( Vec3f(x, 0, 0) , Vec3f(x, size, 0) );
	}
	for(float y = 0 ; y <= size ; y+=step ){
		gl::drawLine( Vec3f(0, y, 0) , Vec3f(size, y, 0) );		
	}	
	glPopMatrix();
}
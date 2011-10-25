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
	startWave = false;
	gridSize = 5000.0f;
	cellSize = 20.0f;
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
	return "grid";
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
	cellSize = 20 + 50.0f * get( DRAWABLE_GRID_VAR_CELL_SIZE );
	brightness = get( DRAWABLE_GRID_VAR_BRIGTNESS );
	startWave = get( DRAWABLE_GRID_FLAG_START_WAVE );
	if( startWave ){
		waveTimeIndex = 0;
		waveFadeoutSpeed = 0.001 + get( DRAWABLE_GRID_VAR_WAVE_FADEOUT_SPEED );
		waveAmplitude = 100.0f * get( DRAWABLE_GRID_VAR_WAVE_AMPLITUDE );
		waveFrequency = get( DRAWABLE_GRID_VAR_WAVE_FREQUENCY );	
		console() << "StartWave" << endl;
	}
	
	if( waveTimeIndex < 1.0f ){
		waveTimeIndex += waveFadeoutSpeed;
	}
}

/**
 *
 */
void Grid::draw()
{
	glPushMatrix();
	
	glTranslated(-500, -300, 500);
	
	drawGrid(gridSize,cellSize);
	
	glRotated(-90, 1, 0, 0);
	drawGrid(gridSize,cellSize);
	
	glRotated(-90, 0, 1, 0);
	drawGrid(gridSize,cellSize);		
	glPopMatrix();
}


#pragma mark instance methods

void Grid::drawGrid(float size, float step)
{
	glPushMatrix();
	gl::color( Colorf(brightness,brightness,brightness) );	
	
	for(float x = 0 ; x <= size ; x+=step ){
		gl::drawLine( Vec3f(x, 0, 0) , Vec3f(x, size, 0) );
	}
	for(float y = 0 ; y <= size ; y+=step ){
		gl::drawLine( Vec3f(0, y, 0) , Vec3f(size, y, 0) );		
	}
	glPopMatrix();
}
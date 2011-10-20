/*
 *  FFTVisualiser.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "FFTVisualiser.h"

#pragma mark Constructor / destructor


FFTVisualiser::FFTVisualiser()
{

}

FFTVisualiser::~FFTVisualiser()
{

}


#pragma mark Controllable interface implementation

/**
 *
 */
void FFTVisualiser::set(std::string key, float value)
{
	_values.set( key , value );
}

/**
 *
 */
float FFTVisualiser::get(std::string key)
{
	return _values.get( key );
}

/**
 * List all keys
 */
vector<string> FFTVisualiser::keys()
{
	return _values.keys();
}


std::string FFTVisualiser::getId()
{
	return "fftVisualiser";
}

#pragma mark Drawable interface implementation

void FFTVisualiser::setup()
{

}
void FFTVisualiser::update()
{

}

void FFTVisualiser::draw()
{
	
	gl::color( ColorAf( 1.0 , 1.0 , 1.0 ) );
	
	glPushMatrix();
	
	glTranslated( getWindowWidth()/2.0f, getWindowHeight()/2.0f , 0 );
	
	string bandId;
	int bandsCount = get( "bands" );
	float PI = 3.14;
	float bandValue;
	float radius = 100.0f;
	float idx;
	
	gl::color( ColorAf( 1.0,1.0,1.0 ) );
	glBegin(GL_TRIANGLE_FAN);
	
	for( int band = 0 ; band < bandsCount ; band++ ){
		idx = (band/(float)bandsCount);
		bandId = "band" + boost::lexical_cast<string>(band);
		bandValue = get(bandId);
		
		radius = 20 + 10 * bandValue;
		
		Vec3f v = Vec3f(
			radius * sin( idx * 2*PI ),
			radius * cos( idx * 2*PI ),
			0//radius * sin( idx * 8*PI )
		);
		
		gl::color( ColorAf( 1.0 , idx , 1-idx , 0.5f ) );
		glVertex3fv( v );
	}
	
	glEnd();
	
	glPopMatrix();
	
}
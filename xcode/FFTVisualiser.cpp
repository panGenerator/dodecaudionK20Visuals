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
	float rotation = get( "framesCount" ) / 1.0f;
	float Pi = 3.14;
	float bandWidth = 10 + 20 * get( "blockSize" );
	float bandHeight = 100 + 150 * get( "blockSize" );
	float idx,x,y;
	float val,bandValue;
	for( int band = 0 ; band < bandsCount ; band++ ){
		idx = (band/(float)bandsCount);
		
		
		x = 0;//getWindowWidth()*idx;
		y = 0;
		
		bandId = "band" + boost::lexical_cast<string>(band);
		val = get( bandId );
		bandValue = bandHeight * val;
		
		gl::color( ColorAf( idx , 1.0f-idx , 1.0f , 0.5f ) );
		glRotated( rotation , sin( 4 * idx * Pi ), sin( 0.5 * idx * Pi ), cos( 8 * (1-idx) * Pi ) );
		gl::drawCube( Vec3f( x , y , 0 ) , Vec3f( bandWidth , bandValue , bandWidth ) );
	}
	
	glPopMatrix();
	
}
/*
 *  FFTVisualiser.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWABLE_FFTVIS_INCLUDED
#define DRAWABLE_FFTVIS_INCLUDED


#include "cinder/app/AppBasic.h"
#include <boost/lexical_cast.hpp>
#include "cinder/gl/gl.h"

#include "Drawable.h"
#include "ValuesMap.h"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;


class FFTVisualiser : public Drawable
{
public: 
	FFTVisualiser();
	~FFTVisualiser();

	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();
	
	void setup();
	void update();
	void draw();	
	

private:
	ValuesMap _values;
};

#endif
/*
 *  Grid.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWABLE_GRID_INCLUDED
#define DRAWABLE_GRID_INCLUDED

#include "Drawable.h"
#include "ValuesMap.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class Grid : public Drawable
{
public:
    Grid();
    ~Grid();
	
	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();
	
	void setup();
	void update();
	void draw();
	
private:
	void drawGrid(float size = 2000.0f, float step = 23.0f);
	
	ValuesMap _values; 	
};

#endif
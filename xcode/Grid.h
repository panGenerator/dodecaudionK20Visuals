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


#define DRAWABLE_GRID_VAR_CELL_SIZE "cellSize"
#define DRAWABLE_GRID_VAR_BRIGTNESS "brightness"
#define DRAWABLE_GRID_VAR_WAVE_FADEOUT_SPEED "wavefFadeout"
#define DRAWABLE_GRID_FLAG_START_WAVE "starWaveFlag"
#define DRAWABLE_GRID_VAR_WAVE_AMPLITUDE "waveAmplitude"
#define DRAWABLE_GRID_VAR_WAVE_FREQUENCY "waveFrequency"

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
	void drawGrid(float size = 5000.0f, float step = 100.0f);
	
	ValuesMap _values; 	
	
	float brightness;
	float gridSize,cellSize;
	float waveTimeIndex,waveAmplitude,waveFadeoutSpeed,waveFrequency;
	bool startWave;
};

#endif
/*
 *  Camera.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWABLE_CAMERA_INCLUDED
#define DRAWABLE_CAMERA_INCLUDED

#include "Drawable.h"
#include "ValuesMap.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class CameraDrawer : public Drawable
{
public:
    CameraDrawer();
    ~CameraDrawer();
	
	void set(string key, float value);
	float get(string key);	
	vector<string> keys();
	string getId();
	
	void setup();
	void update();
	void draw();
	
private:
	CameraPersp	cam;
	Vec3f camPosition,targetCamPosition;

	int currentPredefinedCamPositionIndex;
	float camPredefinedPositionLerpIndex, camPredefinedPositionLerpSpeed;
	vector<Vec3f> predefinedCamPositions;
	vector<Vec3f> predefinedCamTargets;
	
	int currentPredefinedCamFOVIndex;
	float camPredefinedFOVLerpIndex, camPredefinedFOVLerpSpeed;
	float camFOV,targetCamFOV;
	vector<float> predefinedFOV;
	
	
	ValuesMap _values; 	
};

#endif
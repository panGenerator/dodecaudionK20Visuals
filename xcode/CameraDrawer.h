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

//flags - need action when set to 1 and are set to 0 immediately after
#define DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_NEXT "camPredefinedPositionNextFlag"
#define DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_PREV "camPredefinedPositionPrevFlag"
#define DRAWABLE_CAMERA_VAR_CAM_RUN_PREDEFINED_LOOP "camIsAutonomous"
#define DRAWABLE_CAMERA_VAR_CAM_PREDEFINED_POSITION "camPredefinedPosition"

#define DRAWABLE_CAMERA_VAR_CAM_MOVEMENT_SPEED "camPositionLerpSpeed"
#define DRAWABLE_CAMERA_VAR_CAM_SHAKE_FACTOR "camShake"

#define DRAWABLE_CAMERA_VAR_FOV "fov" 
#define DRAWABLE_CAMERA_VAR_FOV_CHANGE_SPEED "fovChangeSpeed"

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
	float camFOVLerpIndex, camFOVLerpSpeed;
	float camFOV,targetCamFOV;
	vector<float> targetFOV;
	
	
	ValuesMap _values; 	
	
	
	void setCameraTargetToPredefinedPosition( int positionIdx );
	void setCameraTargetTo(Vec3f position);
	void setCameraFOVTarget( float newFOV );
};

#endif
/*
 *  Camera.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "CameraDrawer.h"

/*
 *  CameraDrawer.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "CameraDrawer.h"

#pragma mark Constructor / destructor

CameraDrawer::CameraDrawer()
{
}

CameraDrawer::~CameraDrawer()
{
}

#pragma mark Controllable interface implementation

/**
 *
 */
void CameraDrawer::set(std::string key, float value)
{
	_values.set( key , value );
}

/**
 *
 */
float CameraDrawer::get(std::string key)
{
	return _values.get( key );
}

/**
 * List all keys
 */
vector<string> CameraDrawer::keys()
{
	return _values.keys();
}


std::string CameraDrawer::getId()
{
	return "camera";
}



#pragma mark Drawable interface implementation


void CameraDrawer::setup()
{
	set( "cameraFarClip" , 2500 );
		
	//set up predefined camera positions
	predefinedCamPositions.push_back( Vec3f( 0,0,-750) );
	predefinedCamPositions.push_back( Vec3f( -200,0,750) );
	predefinedCamPositions.push_back( Vec3f( -200,500,-950) );

	//init defaults
	currentPredefinedCamPositionIndex = 0;
	camPosition = targetCamPosition = predefinedCamPositions[currentPredefinedCamPositionIndex];
	camPredefinedPositionLerpIndex = 0.0f;

	//predefined targets
	//TODO:
	
	//predefined FOVs
	predefinedFOV.push_back( 60 );
	predefinedFOV.push_back( 90 );
	currentPredefinedCamFOVIndex = 0;
	camFOV = targetCamFOV = predefinedFOV[currentPredefinedCamFOVIndex];
	camPredefinedFOVLerpIndex = 0.0f;
}

/**
 * Update the modl state
 */
void CameraDrawer::update()
{
	cam.setAspectRatio( get( "aspectRatio" ) );
	cam.setFarClip( get( "cameraFarClip" ) );
	
	camPredefinedPositionLerpSpeed = 0.05 + get( "camPositionLerpSpeed" );
	camPredefinedFOVLerpSpeed = 0.05 + get( "camFOVLerpSpeed" );
	
	//set to autonomous mode
	if( get( "camAutonomous" ) == 1 ){
		targetCamPosition = Vec3f( 500 * sin( get( "framesCount" ) / 100.0f ) , 120 , -750 );
		camPredefinedPositionLerpIndex = 0.5f;
	}else{	
		//update camera position
		if( currentPredefinedCamPositionIndex != get( "camPredefinedPosition" ) ){
			currentPredefinedCamPositionIndex = (int) get( "camPredefinedPosition" );
			targetCamPosition = predefinedCamPositions[ currentPredefinedCamPositionIndex % predefinedCamPositions.size() ];
			camPredefinedPositionLerpIndex = 0.0;
		}
	}
	
	//see if there's a request to change the camera position...
	camPosition = camPosition.lerp( camPredefinedPositionLerpIndex , targetCamPosition );
	
	if( camPredefinedPositionLerpIndex < 1.0f ){
		camPredefinedPositionLerpIndex += camPredefinedPositionLerpSpeed;
	}	
	
	
	
	//update camera target
	//TODO
	
	
	//update camera FOV
	if( currentPredefinedCamFOVIndex != get( "camPredefinedFOV" ) ){
		currentPredefinedCamFOVIndex = (int) get( "camPredefinedFOV" );
		targetCamFOV = predefinedFOV[ currentPredefinedCamFOVIndex ];
		camPredefinedFOVLerpIndex = 0.0f;
	}
	
	camFOV = lerp( camFOV , targetCamFOV , camPredefinedFOVLerpIndex );
	
	if( camPredefinedFOVLerpIndex < 1.0f ){
		camPredefinedFOVLerpIndex += camPredefinedFOVLerpSpeed;
	}
}

/**
 * Set the view 
 */
void CameraDrawer::draw()
{
	cam.lookAt( camPosition , Vec3f::zero() , -Vec3f::yAxis() );
	cam.setFov( camFOV );
	gl::setMatrices( cam );
}


#pragma mark instance methods

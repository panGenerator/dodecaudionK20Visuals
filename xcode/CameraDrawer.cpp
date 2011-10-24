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
	//predefinedFOV.push_back( 60 );
	//predefinedFOV.push_back( 90 );
	currentPredefinedCamFOVIndex = 0;
	//camFOV = targetCamFOV = predefinedFOV[currentPredefinedCamFOVIndex];
	camFOVLerpIndex = 0.0f;
}

/**
 * Update the modl state
 */
void CameraDrawer::update()
{
	
	//go to next predefined position flag set. 
	if( get( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_NEXT ) == 1 ){
		console() << "NextPos" << endl;
		setCameraTargetToPredefinedPosition( currentPredefinedCamPositionIndex + 1 );
		//currentPredefinedCamPositionIndex += 1;
		//currentPredefinedCamPositionIndex %= predefinedCamPositions.size();
		//camPredefinedFOVLerpIndex = 0.0f;
		set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_NEXT , 0 );
		set( "camAutonomous" , 0 );
	}
	
	//go to prev predefined position flag set
	if( get( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_PREV ) == 1 ){
		console() << "PrevPos" << endl;
		//currentPredefinedCamPositionIndex -= 1;
		setCameraTargetToPredefinedPosition( currentPredefinedCamPositionIndex - 1 );
		set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_PREV , 0 );
		set( "camAutonomous" , 0 );
	}
	
	
	//update FOV 
	setCameraFOVTarget( 60 + 30 * get( DRAWABLE_CAMERA_VAR_FOV ) );
	
	camPredefinedPositionLerpSpeed = 0.0001 + get( DRAWABLE_CAMERA_VAR_CAM_MOVEMENT_SPEED );
	camFOVLerpSpeed = 0.05 + get( DRAWABLE_CAMERA_VAR_FOV_CHANGE_SPEED );
	
	
	cam.setAspectRatio( get( "aspectRatio" ) );
	cam.setFarClip( get( "cameraFarClip" ) );
	
	//TODO
	//set to autonomous mode

	//update the camera position
	camPosition = camPosition.lerp( camPredefinedPositionLerpIndex , targetCamPosition );
	if( camPredefinedPositionLerpIndex < 1.0f ){
		camPredefinedPositionLerpIndex += camPredefinedPositionLerpSpeed;
	}	
	
	
	
	//update camera target
	//TODO
	
	
	//update camera FOV
	camFOV = lerp( camFOV , targetCamFOV , camFOVLerpIndex );
	if( camFOVLerpIndex < 1.0f ){
		camFOVLerpIndex += camFOVLerpSpeed;
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
/**
 * Set camera target to predefined position (determined by position in array)
 */
void CameraDrawer::setCameraTargetToPredefinedPosition( int positionIdx )
{
	currentPredefinedCamPositionIndex = positionIdx % predefinedCamPositions.size();
	setCameraTargetTo( predefinedCamPositions[currentPredefinedCamPositionIndex] );
}

/**
 * Set new target position for camera
 */
void CameraDrawer::setCameraTargetTo(Vec3f position)
{
	targetCamPosition = position;
	camPredefinedPositionLerpIndex = 0.0f;		
}

/**
 * Set target camera FOV
 */
void CameraDrawer::setCameraFOVTarget( float newFOV )
{
	//change only on significant difference
	if( abs( targetCamFOV - newFOV ) > 5.0f ){
		if( newFOV < 20 ){ newFOV = 60.0f; }
		targetCamFOV = newFOV;
		camFOVLerpIndex = 0.0f;
	}
}
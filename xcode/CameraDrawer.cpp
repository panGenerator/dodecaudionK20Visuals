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
	predefinedCamPositions.push_back( Vec3f( 0,20,-750) );
	predefinedCamPositions.push_back( Vec3f( 302.935,263.682,-298.499 ) );
	predefinedCamPositions.push_back( Vec3f( -271.013,343.642,-242.616 ) );
	predefinedCamPositions.push_back( Vec3f( 500,500,-500) );

	//init defaults
	currentPredefinedCamPositionIndex = 0;
	camPosition = targetCamPosition = predefinedCamPositions[currentPredefinedCamPositionIndex];
	camPredefinedPositionLerpIndex = 0.0f;

	//predefined targets
	//TODO:
	
	currentPredefinedCamFOVIndex = 0;

	camShakeLerpIndex = 0.0f;
	
	isAutonomous = false;
}

/**
 * Update the modl state
 */
void CameraDrawer::update()
{
	
	//go to next predefined position flag set. 
	if( get( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_NEXT ) == 1 ){
		//console() << "NextPos" << endl;
		setCameraTargetToPredefinedPosition( currentPredefinedCamPositionIndex + 1 );
		isAutonomous = false;
		set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_NEXT , 0 );
	}
	
	//go to prev predefined position flag set
	if( get( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_PREV ) == 1 ){
		setCameraTargetToPredefinedPosition( currentPredefinedCamPositionIndex - 1 );
		isAutonomous = false;
		set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_PREV , 0 );
	}
	//start autonomous playback
	if( get( DRAWABLE_CAMERA_FLAG_CAM_PREDEFINED_LOOP_START ) == 1 ){
		isAutonomous = true;
	}
	if( get( DRAWABLE_CAMERA_FLAG_CAM_PREDEFINED_LOOP_STOP ) == 1 ){
		isAutonomous = false;
	}
	
	//update FOV 
	camFOV = ( 60 + 30 * ( -1.0f + 2.0f * get( DRAWABLE_CAMERA_VAR_FOV ) ) );
	
	camShakeFactor = get( DRAWABLE_CAMERA_VAR_CAM_SHAKE_FACTOR );
	
	camPredefinedPositionLerpSpeed = 0.0001 + 0.01 * get( DRAWABLE_CAMERA_VAR_CAM_MOVEMENT_SPEED );

	cam.setAspectRatio( get( "aspectRatio" ) );
	cam.setFarClip( get( "cameraFarClip" ) );

	
	//update the camera position
	if( camPredefinedPositionLerpIndex < 1.0f ){
		camPredefinedPositionLerpIndex += camPredefinedPositionLerpSpeed;
	}	
	//if in autonomous mode, when transition is finished go to next position
	if( camPredefinedPositionLerpIndex >= 1.0f && isAutonomous ){
		setCameraTargetToPredefinedPosition( currentPredefinedCamPositionIndex + 1 );
	}
	
	//shake
	camShakeLerpIndex += 2.0f * camPredefinedPositionLerpSpeed;
	camShakeOffset = camShakeOffset.lerp( camShakeLerpIndex , targetCamShakeOffset );
	if( camShakeLerpIndex >= 1.0f ){
		setCameraShakeOffsetTarget( camShakeFactor );
		camShakeLerpIndex = 0.0f;
	}
	
	camPosition = camPosition.lerp( camPredefinedPositionLerpIndex , targetCamPosition ) + camShakeOffset;
	
	//for manual camera 
	Quatf quat,camRotationX,camRotationY;
	float rotationAngleX,rotationAngleY,distance;
	
	rotationAngleX = 3.14 * get( DRAWABLE_CAMERA_VAR_CAM_POSITION_X );
	rotationAngleY = 3.14 * get( DRAWABLE_CAMERA_VAR_CAM_POSITION_Y );
	distance = -500 -750 * get( DRAWABLE_CAMERA_VAR_CAM_DISTANCE );

	
	camRotationX = Quatf( Vec3f::xAxis() , rotationAngleX );	
	camRotationY = Quatf( Vec3f::yAxis() , rotationAngleY );
	quat = camRotationX * camRotationY;
		
	//console() << "Cam rotation: " << "x: " << rotationAngleX << ", y:" << rotationAngleY << ", dst: " << distance << endl;
	
	//camPosition = predefinedCamPositions[0];
	//camPosition.z = distance;
	//camPosition = camPosition * quat;
	//console() << "Cam position" << camPosition << endl;
	
	//update camera target
	//TODO
	
	
	//update camera FOV
	//camFOV = lerp( camFOV , targetCamFOV , camFOVLerpIndex );
	//if( camFOVLerpIndex < 1.0f ){
	//	camFOVLerpIndex += camFOVLerpSpeed;
	//}
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
/*
void CameraDrawer::setCameraFOVTarget( float newFOV )
{
	//change only on significant difference
	if( abs( targetCamFOV - newFOV ) > 0.5f ){
		if( newFOV < 20 ){ newFOV = 60.0f; }
		cam = newFOV;
	}
}
*/

void CameraDrawer::setCameraShakeOffsetTarget( float shakeFactor ){
	shakeFactor *= 10.0f;
	shakeFactor *= shakeFactor;
	
	targetCamShakeOffset = Vec3f(shakeFactor * (-1.0 + 2.0f*rand()/(float)RAND_MAX ) ,
				 shakeFactor * (-1.0 + 2.0f*rand()/(float)RAND_MAX ) , 
				 shakeFactor * (-1.0 + 2.0f*rand()/(float)RAND_MAX ) );	
}
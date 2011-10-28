/*
 *  Tri.cpp
 *  TestProject1
 *
 *  Created by Jakub Koźniewski on 12/6/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "Tri.h";
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h";

using namespace ci;


Tri::Tri( ci::Vec3f _pos, ci::Vec3f _rot, ci::ColorA _color, float _size  ){
	
	mPos = _pos;
	mRotation = _rot;
	mColor = _color;
	mSize = _size;
	
}


void Tri::update(){

	//
	
}

void Tri::draw(){
	
	glPushMatrix();
	
	glTranslatef(mPos.x, mPos.y, mPos.z);
	
	
	glRotatef( mRotation.x, 1.0, 0.0, 0.0 );			// rotate along X axis
	glRotatef( mRotation.y, 0.0, 1.0, 0.0 );			// Y axis
	glRotatef( mRotation.z, 0.0, 0.0, 1.0 );			// Z axis
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glColor4f( mColor.r, mColor.g, mColor.b, mColor.a );
	glColor4f( 0.0, 0.85, 1.0, 0.4 );//* (round(mRotation.z)%360)/360.0f);
	
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glVertex3f( 0.0f, mSize, 0.0f);					// Top
		glVertex3f(-mSize,-mSize, 0.0f);				// Bottom Left
		glVertex3f( mSize,-mSize, 0.0f);				// Bottom Right
	glEnd();
	
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
	
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
	glVertex3f( 0.0f, mSize, 0.0f);					// Top
	glVertex3f(-mSize,-mSize, 0.0f);				// Bottom Left
	glVertex3f( mSize,-mSize, 0.0f);				// Bottom Right
	glEnd();
	
	glColor4f( 1, 1, 1, 1 );							// reset color ( sort of hack ? )
	
	
	glPopMatrix();

}
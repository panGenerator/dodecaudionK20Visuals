/*
 *  Particle.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Particle.h"

Particle::Particle(){
	
	
	
}


void Particle::update(){
	
	rotation += Vec3f( pRotationSpeed, pRotationSpeed, pRotationSpeed );
	
}


void Particle::draw(){
	
	
	glPushMatrix();
	
	glTranslated( position.x, position.y, position.z );
	glRotated( rotation.x, 1.0, 0.0, 0.0 );
	glRotated( rotation.y, 0.0, 1.0, 0.0 );
	glRotated( rotation.z, 0.0, 0.0, 1.0 );
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);
	gl::vertex( Vec3f( 0, pSize, 0 ) );
	gl::vertex( Vec3f( -pSize, -pSize, 0 ) );
	gl::vertex( Vec3f( pSize, -pSize, 0 ) );
	glEnd();
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	glPopMatrix();
	
	
}


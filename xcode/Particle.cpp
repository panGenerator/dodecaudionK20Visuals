/*
 *  Particle.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Particle.h"

Particle::Particle( Vec3f pos ){
	
	position = pos;
	pRotationSpeed = 1;
	pSize = 10;
	
}

void Particle::setup(){

}

void Particle::update(){
	rotation += Vec3f( pRotationSpeed, pRotationSpeed, pRotationSpeed );
	
}


void Particle::draw(){
	
	
	glPushMatrix();
	glColor4f(1.0f,0.0f,0.0f,1.0f);

	gl::drawCube( Vec3f( 0,0,0 ) , Vec3f( 100 , 200 , 300 ) );
	/*
	glTranslated( 0,0,0 );//position.x, position.y, position.z );
	glRotated( rotation.x, 1.0, 0.0, 0.0 );
	glRotated( rotation.y, 0.0, 1.0, 0.0 );
	glRotated( rotation.z, 0.0, 0.0, 1.0 );
	*/
	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//glColor3f(1.0f,0.0f,0.0f);
//	glBegin(GL_TRIANGLES);
//	gl::vertex( Vec3f( 0, pSize, 0 ) );
//	gl::vertex( Vec3f( -pSize, -pSize, 0 ) );
//	gl::vertex( Vec3f( pSize, -pSize, 0 ) );
//	glEnd();
//	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	
	glPopMatrix();
	
	
}


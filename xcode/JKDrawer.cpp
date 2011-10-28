/*
 *  JKDrawer.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "JKDrawer.h"

#pragma mark Constructor / destructor

JKDrawer::JKDrawer()
{
}

JKDrawer::~JKDrawer()
{
}

#pragma mark Controllable interface implementation

/**
 *
 */
void JKDrawer::set(std::string key, float value)
{
	_values.set( key , value );
}

/**
 *
 */
float JKDrawer::get(std::string key)
{
	return _values.get( key );
}

/**
 * List all keys
 */
vector<string> JKDrawer::keys()
{
	return _values.keys();
}


std::string JKDrawer::getId()
{
	return "JKDrawer";
}



#pragma mark Drawable interface implementation


void JKDrawer::setup()
{
	// create bg
	//mBg = gl::Texture( loadImage( loadResource( "bg2.png") ) );	
	
	particlesDensity = 1.5;
	
	setupParticles();
	setupTorus();
	
}

/**
 * Update the modl state
 */
void JKDrawer::update()
{
	//torus
	torusAmplitude = 100.0f * get( DRAWABLE_JKDRAWER_TORUS_AMPLITUDE );
	torusFrequency = 10.0 * get( DRAWABLE_JKDRAWER_TORUS_FREQ );

	console() << "Torus: amplitude: " << torusAmplitude << ", freq: " << torusFrequency << endl;
}

/**
 *
 */
void JKDrawer::draw()
{
	
	// clear out the window with black
	//gl::clear( ColorA( 0, 0, 0, 0 ) ); 
	
	//glPushMatrix();
	
	//glTranslated(-getWindowWidth()/2.0f, -getWindowHeight()/2.0f, 0);
	
	// draw bg
	//mBg.enableAndBind();
	//gl::draw( mBg, getWindowBounds() );
	//glDisable( GL_TEXTURE_2D );	
	
	//glPopMatrix();
	
	// draw 3D
	glPushMatrix();
	
	//glTranslated( getWindowWidth()/2.0, getWindowHeight()/2, 0 );
	
	drawTorus();
	drawSphere();
	drawParticles();
	
	glPopMatrix();
	
}


#pragma mark instance methods

void JKDrawer::setupTorus(){
	torusAmplitude = 5.0f;
	torusFrequency = 1.0f;
}


void JKDrawer::setupParticles(){
	
	// create tris
	
	ci::ColorA color;
	
	for( int i=0; i < 1000; i++ ){
		
		ci::Vec3f pos = Vec3f( 
							  Rand::randFloat( -app::getWindowWidth() / particlesDensity, app::getWindowWidth() / particlesDensity ),	
							  Rand::randFloat( -app::getWindowHeight() / particlesDensity, app::getWindowHeight() / particlesDensity ),
							  Rand::randFloat( -1000 / particlesDensity, 1000 / particlesDensity )
							  );
		
		ci::Vec3f rot = Vec3f( 
							  Rand::randFloat( 360 ),	
							  Rand::randFloat( 360 ),
							  Rand::randFloat( 360 )	
							  );
		
		
		
		// always white ?
		if( Rand::randFloat( 0, 1 ) > 0.5 ){
			
			color = ColorA( 69, 38, 185, Rand::randFloat( 0.1, 0.9 ) );
			
		}else {
			
			color = ColorA( 255, 255, 255, Rand::randFloat( 0.1, 0.9 ) );
			
			
		}
		
		
		mTris.push_back( Tri( pos, rot, color, Rand::randFloat( 0.25, 10 ) ) );
		
	}
	
	
}


#pragma mark Drawing functions



void JKDrawer::drawSphere(){
	
	int lats = 20;
	int longs = 20;
	double r = 10;
	int i, j;
	
	float noiseFactor = 10;
	float oscilatedR = r + sin( getElapsedSeconds() / 2.0 ) * 50;
	
	
	glPushMatrix();
	
	glRotated( 90, 1.0, 0.0, 0.0);
	
	
	for(i = 0; i <= lats; i++) {
		
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
		
		float noise = Rand::randFloat( -noiseFactor, noiseFactor );
		float noiseR = oscilatedR + noise;
		
		double z0  = sin(lat0) * noiseR;
		double zr0 =  cos(lat0) * noiseR;
		
		double lat1 = M_PI * (-0.5 + (double) i / lats);
		double z1 = sin(lat1) * noiseR;
		double zr1 = cos(lat1) * noiseR;
		
		glColor4f( 0.99, 0.0, 0.7, 0.5 );
		
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glBegin(GL_QUAD_STRIP);
		
		for(j = 0; j <= longs; j++) {
			
			double lng = 2 * M_PI * (double) (j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);
			
			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		
		glEnd();
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		
	}
	
	glPopMatrix();
	
}



void JKDrawer::drawTorus(){
	
	glPushMatrix();
	glRotated( 90, 1.0, 0.0, 0.0);
	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glColor4f( 0.0, 0.95, 0.9, 0.5 );
	
	
	float radius1 = 800;
	float radius2 = 700;
	int segments = 500;
	float step = (3.14*2) / (float)segments;
	float angle = 0;
	
	glBegin(GL_QUAD_STRIP);
	
	for (int i = 0; i<segments; i++) {
		float idx = i/(float)segments;
		float sinA = sin( angle );
		float cosA = cos( angle );
		float x = sinA * radius1;
		float y = cosA * radius1;
		float z = torusAmplitude * sin( torusFrequency * idx * 3.14 );
		float z2 = torusAmplitude * sin( torusFrequency * (idx + (-0.1 + 0.2 * rand() / (float)RAND_MAX ) ) ); 
		
		
		gl::vertex( Vec3f( x, y, z ) );
		
		x = sinA * radius2;
		y = cosA * radius2;
		
		gl::vertex( Vec3f( x, y, z2 ) );
		
		angle += step;
	}
	
	glEnd();
	
	
	glColor4f( 0.0, 0.0, 0.0, 0.0 );
	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	glPopMatrix();
	
	
}


void JKDrawer::drawTestCube(){
	
	glColor4f( 0.0, 0.85, 1.0, 1.0 );
	gl::drawCube( Vec3f( 0.0, 0.0, 0.0 ), Vec3f( 100.0, 100.0, 100.0 ) );	
	
}



void JKDrawer::drawParticles(){
	
	
	//gl::pushMatrices();
	
	// setup cam
	//CameraPersp cam( getWindowWidth(), getWindowHeight(), 60 + 20.0f );
	//cam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
	//cam.setCenterOfInterestPoint( Vec3f( getMousePos().x, getMousePos().y, 0 ) );
	//gl::setMatrices( cam );
	
	glPushMatrix();
	
	glTranslated( app::getWindowWidth()/2, app::getWindowHeight()/2, 0);
	glRotated( getElapsedFrames()/10.0, 0.0, 1.0, 0.0 );
	
	// draw tris
	for( std::vector<Tri>::iterator t = mTris.begin(); t != mTris.end(); ++t ){
		t->mRotation += 1;
		t->draw();
	}
	
	glPopMatrix();
	
	//gl::popMatrices();
	
}







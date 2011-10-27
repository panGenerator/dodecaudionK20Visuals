/*
 *  ParticlesHolder.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ParticlesHolder.h"



ParticlesHolder::ParticlesHolder(){
	particlesCount = 23;
}

ParticlesHolder::~ParticlesHolder(){
}


void ParticlesHolder::setup(){
	
	maxX = 1000;
	maxY = 1000;
	maxZ = 1000;
	
	float x = rand()/(float)RAND_MAX;//Rand::randFloat( maxX );
	float y = rand()/(float)RAND_MAX;//Rand::randFloat( maxY );
	float z = rand()/(float)RAND_MAX;//Rand::randFloat( maxZ );
	
	for (int i = 0; i < particlesCount; i++) {
		Particle p = Particle( Vec3f( x, y, z ) ); 
		particles.push_back( &p );
		
	}
	
}


void ParticlesHolder::update(){

	for( std::vector<Particle *>::iterator p = particles.begin(); p != particles.end(); ++p ){
        (*p)->update();
    }

}


void ParticlesHolder::draw(){

	drawParticles();

}

void ParticlesHolder::drawParticles(){

	for( std::vector<Particle *>::iterator p = particles.begin(); p != particles.end(); ++p ){
        (*p)->draw();
    }

}


#pragma mark Controllable interface implementation

/**
 *
 */
void ParticlesHolder::set(std::string key, float value)
{
//	_values.set( key , value );
}

/**
 *
 */
float ParticlesHolder::get(std::string key)
{
	return 0.0;
//	return _values.get( key );
}

/**
 * List all keys
 */
vector<string> ParticlesHolder::keys()
{
	vector<string> v;
	return v;
	//return _values.keys();
}


std::string ParticlesHolder::getId()
{
	return "particlesHolder";
}

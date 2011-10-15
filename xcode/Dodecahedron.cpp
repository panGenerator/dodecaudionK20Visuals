/*
 *  Dodecahedron.cpp
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Dodecahedron.h"

#pragma mark Constructor / destructor

/**
 * Constructor
 */
Dodecahedron::Dodecahedron()
{
	set( "edgeColorR" , 1.0f );  
	edgesColor = ColorAf(get("edgesColorR"),0,0);
	__updateVertices();
}

/**
 * Destructor
 */
Dodecahedron::~Dodecahedron()
{

}


#pragma mark Controllable interface implementation

/**
 *
 */
void Dodecahedron::set(std::string key, float value)
{
	_values.set( key , value );
}

/**
 *
 */
float Dodecahedron::get(std::string key)
{
	return _values.get( key );
}

/**
 * List all keys
 */
vector<string> Dodecahedron::keys()
{
	return _values.keys();
}


std::string Dodecahedron::getId()
{
	return "dodecahedron";
}



#pragma mark Drawable interface implementation


void Dodecahedron::setup()
{
}

/**
 * Update the modl state
 */
void Dodecahedron::update()
{
	radius = 200 * get( "radius" );
	modelRotation = 64 * Vec3f( get( "rotationX" ) , get( "rotationY" ) , get( "rotationZ" ) );
	edgesColor = ColorAf( get( "edgeColorR" ) , get( "edgeColorG" ) , get( "edgeColorB" ) );
	
	__updateVertices();
}

/**
 *
 */
void Dodecahedron::draw()
{
	gl::color( edgesColor );
	
	glPushMatrix();
	glTranslated(getWindowWidth()/2.0f, getWindowHeight()/2.0f, 0);
	
	glRotated( modelRotation.y , 1.0, 0.0, 0.0 );
	glRotated( modelRotation.z , 0.0, 1.0, 0.0 );
	glRotated( modelRotation.x , 0.0, 0.0, 1.0 );
	
	/*
	 * @see: http://www.cs.umbc.edu/~squire/reference/polyhedra.shtml#dodecahedron
	 */
	__drawVertices(0,1,2,3,4);

	__drawVertices(0,1,6,10,5);
	__drawVertices(1,2,7,11,6);
	__drawVertices(2,3,8,12,7);
	__drawVertices(3,4,9,13,8);
	__drawVertices(4,0,5,14,9);
	
	__drawVertices(15,16,11,6,10);
	__drawVertices(16,17,12,7,11);
	__drawVertices(17,18,13,8,12);
	__drawVertices(18,19,14,9,13);
	__drawVertices(19,15,10,5,14);
	
	__drawVertices(15,16,17,18,19);
	
	glPopMatrix();
}

#pragma mark instance methods

/**
 * Initialize the model vertices
 * @see: http://www.cs.umbc.edu/~squire/reference/polyhedra.shtml#dodecahedron
 */
void Dodecahedron::__updateVertices()
{
	
	//vars
	int verticesCount = 20;
	double Pi = 3.141592653589793238462643383279502884197;
	
	double phiaa = 52.62263590; /* the two phi angles needed for generation */
	double phibb = 10.81231754;
	
	float r = 100 + radius; /* any radius in which the polyhedron is inscribed */
	float phia = Pi*phiaa/180.0; /* 4 sets of five points each */
	float phib = Pi*phibb/180.0;
	float phic = Pi*(-phibb)/180.0;
	float phid = Pi*(-phiaa)/180.0;
	float the72 = Pi*72.0/180;
	float theb = the72/2.0; /* pairs of layers offset 36 degrees */
	float the = 0.0;	
	
	//init vertices vector
	vertices.reserve( verticesCount );
	
	//calculation of vertices positions
	Vec3f v;
	float x,y,z;
	for(int i = 0 ; i < 5 ; i++ ){
		x = r*cos(the)*cos(phia);
		y = r*sin(the)*cos(phia);
		z = r*sin(phia);
		
		v = Vec3f( x,y,z );
		vertices[ i ] = v;
		the = the+the72;
	}
	the = 0.0;
	for(int i = 5 ; i < 10 ; i++ ){
		x = r*cos(the)*cos(phib);
		y = r*sin(the)*cos(phib);
		z = r*sin(phib);
		
		v = Vec3f( x,y,z );
		vertices[ i ] = v;
		the = the+the72;
	}
	the = theb;
	for(int i = 10 ; i < 15 ; i++ ){
		x = r*cos(the)*cos(phic);
		y = r*sin(the)*cos(phic);
		z = r*sin(phic);
		
		v = Vec3f( x,y,z );
		vertices[ i ] = v;
		the = the+the72;
	}
	the = theb;
	for(int i = 15 ; i < 20 ; i++ ){
		x = r*cos(the)*cos(phid);
		y = r*sin(the)*cos(phid);
		z = r*sin(phid);
		
		v = Vec3f( x,y,z );
		vertices[ i ] = v;
		the = the+the72;
	}
}

/**
 * Helper method for drawing vertices referenced by position in vertices array
 * This is an ugly method. Bad method, bad!
 */
void Dodecahedron::__drawVertices( int vIdx1 , int vIdx2 , int vIdx3 , int vIdx4 , int vIdx5 )
{
	Vec3f v;
	
	glBegin(GL_LINE_STRIP);	
	
	v = vertices[ vIdx1 ];
	glVertex3fv(v);

	v = vertices[ vIdx2 ];
	glVertex3fv(v);

	v = vertices[ vIdx3 ];
	glVertex3fv(v);

	v = vertices[ vIdx4 ];
	glVertex3fv(v);

	v = vertices[ vIdx5 ];
	glVertex3fv(v);
	
	glEnd();
	
}

/*
 *  Dodecahedron.cpp
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Dodecahedron.h"

int wallVerticeIds[WALL_COUNT][VERTICES_PER_WALL] = {
	{0,1,2,3,4},
	{0,1,6,10,5},
	{1,2,7,11,6},
	
	{2,3,8,12,7},
	{3,4,9,13,8},
	{4,0,5,14,9},
	
	{15,16,11,6,10},
	{16,17,12,7,11},
	{17,18,13,8,12},
	
	{18,19,14,9,13},
	{19,15,10,5,14},
	{15,16,17,18,19},
};

#pragma mark Constructor / destructor

/**
 * Constructor
 */
Dodecahedron::Dodecahedron()
{
	set( "edgeColorR" , 1.0f );  
	edgesColor = ColorAf(get("edgesColorR"),0,0);
	updateVertices();	
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
	radius = 10 * get( "radius" );
	modelRotation = 64 * Vec3f( get( "rotationX" ) , get( "rotationY" ) , get( "rotationZ" ) );
	edgesColor = ColorAf( get( "edgeColorR" ) , get( "edgeColorG" ) , get( "edgeColorB" ) );
	
	updateVertices();
	calcWallCenters();
	calcWallCoordinateSystems();
}

/**
 *
 */
void Dodecahedron::draw()
{
	gl::color( edgesColor );
	
	glPushMatrix();
	
	Quatf quat,quat2;
	Vec3f rotationAxis = Vec3f::zAxis();
	Vec3f rotationAxis2 = Vec3f::xAxis();
	float rotation = -2.20898;// + -0.5 + get( "param1" );
	float rotation2 = 2.02108;// + -0.5 + get( "param2" );
	
	quat = Quatf( rotationAxis , rotation );
	quat2 = Quatf( rotationAxis2 , rotation2 );

	quat = quat * quat2;
	
	gl::rotate( quat ); 

	console() << rotation << ",  "  << rotation2 << endl;
	
	/*
	 * @see: http://www.cs.umbc.edu/~squire/reference/polyhedra.shtml#dodecahedron
	 */
	for( int wall = 0 ; wall < WALL_COUNT ; wall++ ){
		drawWall( wall );
		__drawWallCenter( wall );
		__drawWallCoordinateSystem( wall );
		drawSonicCones( wall );
		drawEye( wall );
	}
	
	glPopMatrix();
}

#pragma mark instance methods

/**
 * Initialize the model vertices
 * @see: http://www.cs.umbc.edu/~squire/reference/polyhedra.shtml#dodecahedron
 */
void Dodecahedron::updateVertices()
{
	
	//vars
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

#pragma mark calculations

/**
 * Calculate middle point for all of the walls
 */
void Dodecahedron::calcWallCenters()
{
	Vec3f vCalc,v1,v2,v3;
	for( int wall = 0 ; wall < WALL_COUNT ; wall++ ){
		// Calculation of the center is based on finding the middle of height of a isosceles (...a triangle with two identical walls basically)
		//switch( wall ){
//			case 1:
				v1 = vertices[wallVerticeIds[wall][3]];
				v2 = vertices[wallVerticeIds[wall][0]];
				v3 = vertices[wallVerticeIds[wall][1]];				
		//		break;
//			default:
//				v1 = vertices[wallVerticeIds[wall][0]];
//				v2 = vertices[wallVerticeIds[wall][2]];
//				v3 = vertices[wallVerticeIds[wall][3]];				
//				break;
//		}
		
		//find half of the base
		vCalc = (v2+v3)/2.0f;
		//find the middle of height
		vCalc = (vCalc+v1)/2.0f;		
		
		wallCenters[wall] = vCalc;
	}
}


/**
 *
 */
void Dodecahedron::calcWallCoordinateSystems()
{
	Vec3f v1,v2,v3,vBase,vCenter,vCalc;
	Vec3f vX,vY,vZ;
	for( int wall = 0 ; wall < WALL_COUNT ; wall++ ){
		vCenter = wallCenters[wall];		
		
//		switch( wall ){
//			case 1:
				v1 = vertices[wallVerticeIds[wall][3]];
				v2 = vertices[wallVerticeIds[wall][0]];
				v3 = vertices[wallVerticeIds[wall][1]];				
//				break;
//			default:
//				v1 = vertices[wallVerticeIds[wall][0]];
//				v2 = vertices[wallVerticeIds[wall][2]];
//				v3 = vertices[wallVerticeIds[wall][3]];				
//				break;
//		}
		
		vX = (v3-v2);
		vX.normalize();
		
		//middle point of the triangle base
		vBase = (v2+v3)/2.0f;
		vY = (v1-vBase);
		vY.normalize();
		
		vZ = vY.cross(vX);
		vZ.normalize();
		
		//if the z is pointing inside then rotate the system arond Y axis
		vCalc = vCenter+vZ;
		if( vCalc.distance(Vec3f::zero()) < vCenter.distance(Vec3f::zero()) ){
			vZ *= -1;
			vX *= -1;
		}
		
		wallCoordinateSystems[wall][0] = vX.normalized();
		wallCoordinateSystems[wall][1] = vY.normalized();
		wallCoordinateSystems[wall][2] = vZ.normalized();
		
	}
}

#pragma mark drawing helpers

/**
 * Transform the coordinate system to match the surface of the wall
 */ 
void Dodecahedron::transformToWallCoordinateSystem( int wall )
{
	Vec3f vCenter = wallCenters[wall];
	Vec3f coordinateSystem[3] = wallCoordinateSystems[wall];
	
	//transform the model matrix to place (0,0,0) in the middle of the wall. this is awesome, took me a while to figure out
	//...probably done the wrong way :)	
	gl::pushModelView();
	Matrix44f transformation = gl::getModelView();
	transformation = transformation.createTranslation(vCenter);
	transformation.rotate(Vec3f::zAxis(), coordinateSystem[2], coordinateSystem[1]);	
	gl::multModelView(transformation);
}

/**
 * Return to the previous coordinate system
 */
void Dodecahedron::popWallCoordinateSystem()
{
	gl::popModelView();
}

#pragma mark drawing

/**
 * Helper method for drawing vertices referenced by position in vertices array
 */
void Dodecahedron::drawWall( int wall )
{
	Vec3f v;
	
	//draw the walls
	/*
	gl::color( ColorAf(0.5f,0.5f,0.5f,0.25f) );
	glBegin(GL_POLYGON);		
	for( int i = 0 ; i < VERTICES_PER_WALL ; i++ ){
		v = vertices[ wallVerticeIds[wall][i] ];
		glVertex3fv( v );
	}
	glEnd();	
	*/
	
	//draw the edges
	glEnable(GL_LINE_SMOOTH);	
	glLineWidth(1.0f);
	
	gl::color( ColorAf(1.0,1.0,1.0,1.0f) );	
	glBegin(GL_LINE_LOOP);		
	for( int i = 0 ; i < VERTICES_PER_WALL ; i++ ){
		v = vertices[ wallVerticeIds[wall][i] ];
		glVertex3fv( v );
	}
	
	glEnd();	

	if( wall == DEBUG_WALL ){
		for( int i = 0 ; i < VERTICES_PER_WALL ; i++ ){
			v = vertices[ wallVerticeIds[wall][i] ];
			gl::color( ColorAf( i/(float)VERTICES_PER_WALL , i/(float)VERTICES_PER_WALL , i/(float)VERTICES_PER_WALL ) );
			gl::drawCube( v , Vec3f( 10 , i*10 , 10 ) );
		}
	}
	
	
	glLineWidth(1.0f);
}

/**
 *
 */
void Dodecahedron::drawSonicCones( int wall )
{	
	transformToWallCoordinateSystem(wall);
	
	glLineWidth(1.3);
	glEnable(GL_LINE_SMOOTH);
	
	string wallId = DRAWABLE_DODECAHEDRON_VAR_WALL_ + boost::lexical_cast<string>( wall );
	float radius,minRadius = 1.0f, maxRadius=minRadius + 64 * get(wallId);
	int step = 13,circlePoints = 16;
	int length = 1000.0 * get(wallId);
	float idx= 0.0f,idxCircle=0.0f;
	Vec3f v;
	for( int ring = 0 ; ring < length ; ring+=step ){
		idx = ring/(float)length;
		
		//increasing radius
		radius = minRadius + pow(idx,2) * (maxRadius-minRadius);
		
		//fade out
		gl::color( ColorAf(0.6,0.7,1.0f,0.5f-0.3f*idx) );
		
		//draw a circle
		glBegin(GL_LINE_LOOP);
		for( int i = 0 ; i < circlePoints ; i++ ){
			idxCircle = (float)i/circlePoints;
			v = Vec3f( radius * sin( 2 * 3.14 * idxCircle ) , radius * cos( 2 * 3.14 * idxCircle ) , idx * length );
			glVertex3fv( v );
		}
		glEnd();
	}
	
	popWallCoordinateSystem();
}

/**
 *
 */
void Dodecahedron::drawEye( int wall )
{ 
//	if( wall != DEBUG_WALL ){ return; }
	
	string wallId = "wall" + boost::lexical_cast<string>( wall );
	int verticesPerEyelid = 16;
	float idx,x,y;
	float width=60.0f,height,heightMin = 1.0,heightMax = 10 * (1+get( wallId ));
	
	transformToWallCoordinateSystem(wall);
	

	
	glBegin(GL_LINE_LOOP);
	gl::color( ColorAf(1,1,1) );
	for( int i = 0 ; i <= verticesPerEyelid ; i++ ){
		idx = i/(float)verticesPerEyelid;
		x = -width/2.0 + width * idx; 
		y = heightMin + heightMax * sin( idx * 3.14 ); 
		
		glVertex3f( x, y, 1);
	}
	
	
	for( int i = 0 ; i <= verticesPerEyelid	; i++ ){
		idx = 1.0f - i/(float)verticesPerEyelid;
		x = -width/2.0 + width * idx; 
		y = heightMin + heightMax * sin( idx * 3.14 ); 
		
		glVertex3f( x, -y, 1);		
	}
	
	glEnd();
	popWallCoordinateSystem();
}

/**
 * Reality check - if the center is in the middle of the wall
 */
void Dodecahedron::__drawWallCenter( int wall )
{
	
	Vec3f v = wallCenters[wall];
	glPushMatrix();
	
	v = wallCenters[wall];
	gl::color( ColorAf(1.0,1.0,1.0) );
	gl::drawCube( v , Vec3f( 3 , 3 , 3 ) );
	
	glPopMatrix();	
}

/**
 * Reality check - drawign the wall's local coordinate system
 */
void Dodecahedron::__drawWallCoordinateSystem( int wall )
{
	Vec3f vCenter = wallCenters[wall];
	//Vec3f coordinateSystem[3] = wallCoordinateSystems[wall];
	float radius = 10.0;
	
	
	//TEST
	//reality check - draw the axes from the base coordinate system 
	/*
	 glLineWidth(4.0f);
	 
	 gl::color( ColorAf(1.0,0.0,0.0,0.4f) );
	 gl::drawVector( vCenter , vCenter+radius*coordinateSystem[0] );
	 gl::color( ColorAf(0.0,1.0,0.0,0.4f) );
	 gl::drawVector( vCenter , vCenter+radius*coordinateSystem[1] );
	 gl::color( ColorAf(0.0,0.0,1.0,0.4f) );
	 gl::drawVector( vCenter , vCenter+radius*coordinateSystem[2] );
	 glLineWidth(1.0f);
	 */
	
	transformToWallCoordinateSystem(wall);
	
	//
	//Start drawing here...
	//	
	//TEST
	//reality check - draw the axes in the walls in the wall's coordinate system
	gl::color( ColorAf(1.0,0.0,0.0,0.6f) );
	gl::drawVector( Vec3f(0,0,0) , 2*radius*Vec3f::xAxis() );
	gl::color( ColorAf(0.0,1.0,0.0,0.6f) );
	gl::drawVector( Vec3f(0,0,0) , 2*radius*Vec3f::yAxis() );
	gl::color( ColorAf(0.0,0.0,1.0,0.6f) );
	gl::drawVector( Vec3f(0,0,0) , 2*radius*Vec3f::zAxis() );
	//yeah, it's always more fun with a flat cube at (10,20,0)
	gl::color( ColorAf(1,1,1,0.3f) );
	gl::drawCube( Vec3f( 10, 20 , 0 ) , Vec3f( 2, 2, 1) );
	
	
	//....
	
	//
	//end drawing here
	//
	
	popWallCoordinateSystem();
	
}


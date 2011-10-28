/*
 *  Tri.h
 *  TestProject1
 *
 *  Created by Jakub Koźniewski on 12/6/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once
#include "cinder/Color.h"
#include "cinder/Vector.h"
#include <vector>


class Tri {
	
 public:
	
	Tri( ci::Vec3f _pos, ci::Vec3f _rot, ci::ColorA _color, float _size );
	
	void draw();
	void update();
	
	ci::Vec3f mPos;
	ci::Vec3f mRotation;
	ci::ColorA mColor;
	float mSize;


};
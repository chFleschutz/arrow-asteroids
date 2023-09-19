#pragma once

#include "ViewPortGL.h"

class Shape {
public:
	Shape(int red, int green, int blue);
	virtual void prepare(ViewPortGL& vp, int centerX, int centerY, float size)  = 0;
	virtual void prepare(ViewPortGL& vp, float centerX, float centerY, float size) = 0;


	void setRotation(float w);

protected:
	int red, green, blue;
	float rotation;
};


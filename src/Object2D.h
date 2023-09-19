#pragma once
#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
#include "MathVec.h"
#include "Triangle.h"
#include "MatrixFactory.h"
#include "BoundingBox.h"

class Object2D
{
public:
	Object2D();
	Object2D(float sca, float rot, MathVec2<float> pos);
	~Object2D();

	void setScale(float s);
	void setRotation(float r);
	void setPosition(MathVec2<float> p);
	void setPosition(MathVec2<float>& p);
	void setPosition(float x1, float x2);
	void setPosRotScale(MathVec2<float>& p, float r, float s);
	void setPosRotScale(float x1, float x2, float r, float s);

	void moveOnX(float x);
	void moveOnY(float y);

	float getScale();
	float getRotation();
	MathVec2<float>& getPosition();

	void addTriangle(Triangle t);
	void prepare(ViewPortGL& vp);
	
	bool boundingBoxContains(MathVec2<float> point);
	bool collidesWith(Object2D& other);
	void prepareBoundingBox(ViewPortGL& vp);

protected:
	float scale, rotation;
	MathVec2<float> position;
	list<Triangle> triangles;
	BoundingBox bounds;
};


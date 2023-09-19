#pragma once
#include "Object2D.h"

class BulletObject : public Object2D
{
public:
	BulletObject();
	BulletObject(float s, float r, MathVec2<float> p);
	BulletObject(float s, float r, MathVec2<float> p, MathVec2<float> d);

	MathVec2<float> getDirection();

private:
	MathVec2<float> direction;
};

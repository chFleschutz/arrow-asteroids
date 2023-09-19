#pragma once
#include "Object2D.h"
class AsteroidObject : public Object2D
{
public:
	AsteroidObject();
	AsteroidObject(float scale, float rotation, MathVec2<float> position);
	AsteroidObject(float scale, float rotation, MathVec2<float> position, MathVec2<float> speed);

	void buildAsteroidObject2D();

	void setSpeed(MathVec2<float> speed);
	MathVec2<float> getSpeed();

private:
	MathVec2<float> velocity;
};


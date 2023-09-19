#include "BulletObject.h"

BulletObject::BulletObject() :
	direction { 0.0f, 0.0f }
{
	Triangle t1(0.0f, 0.005f, 0.01f, 0.0f, 0.0f, -0.005f, 255, 0, 0);
	Object2D::addTriangle(t1);

	MathVec2<float> pos(0.0f, 0.0f);
	Object2D::setPosRotScale(pos, 0.0f, 0.0f);
}

BulletObject::BulletObject(float s, float r, MathVec2<float> p) : 
	direction { 0.0f, 0.0f }
{
	Triangle t1(0.0f, 0.005f, 0.01f, 0.0f, 0.0f, -0.005f, 255, 0, 0);
	Object2D::addTriangle(t1);

	Object2D::setPosRotScale(p, r, s);
}

BulletObject::BulletObject(float s, float r, MathVec2<float> p, MathVec2<float> d) :
	direction(d)
{
	Triangle t1(0.0f, 0.005f, 0.01f, 0.0f, 0.0f, -0.005f, 255, 0, 0);
	Object2D::addTriangle(t1);

	Object2D::setPosRotScale(p, r, s);
}

MathVec2<float> BulletObject::getDirection()
{
	return this->direction;
	
}

#include "AsteroidObject.h"

AsteroidObject::AsteroidObject() : velocity(MathVec2<float>(0.0f))
{
	buildAsteroidObject2D();
	Object2D::setPosRotScale(0.0f, 0.0f, 0.0f, 1.0f);
}

AsteroidObject::AsteroidObject(float scale, float rotation, MathVec2<float> position) : velocity(MathVec2<float>(0.0f))
{
	buildAsteroidObject2D();
	Object2D::setPosRotScale(position, rotation, scale);
}

AsteroidObject::AsteroidObject(float scale, float rotation, MathVec2<float> position, MathVec2<float> speed) : velocity(speed)
{
	buildAsteroidObject2D();
	Object2D::setPosRotScale(position, rotation, scale);
}

void AsteroidObject::buildAsteroidObject2D()
{
	Triangle t1(0.0f, 0.0f, 0.0082, 0.100, 0.0840, 0.0768, 153, 161, 160);
	Triangle t2(0.0f, 0.0f, 0.0840, 0.0768, 0.1200, 0.0212, 153, 161, 160);
	Triangle t3(0.0f, 0.0f, 0.1200, 0.0212, 0.0996, -0.0547, 153, 161, 160);
	Triangle t4(0.0f, 0.0f, 0.0996, -0.0547, 0.0218, -0.0744, 153, 161, 160);
	Triangle t5(0.0f, 0.0f, 0.0218, -0.0744, -0.0634, -0.0515, 153, 161, 160);
	Triangle t6(0.0f, 0.0f, -0.0634, -0.0515, -0.0863, 0.0157, 153, 161, 160);
	Triangle t7(0.0f, 0.0f, -0.0863, 0.0157, -0.0597, 0.0695, 153, 161, 160);
	Triangle t8(0.0f, 0.0f, -0.0597, 0.0695, 0.0082, 0.100, 153, 161, 160);

	Object2D::addTriangle(t1);
	Object2D::addTriangle(t2);
	Object2D::addTriangle(t3);
	Object2D::addTriangle(t4);
	Object2D::addTriangle(t5);
	Object2D::addTriangle(t6);
	Object2D::addTriangle(t7);
	Object2D::addTriangle(t8);
}

void AsteroidObject::setSpeed(MathVec2<float> speed)
{
	velocity = speed;
}

MathVec2<float> AsteroidObject::getSpeed()
{
	return velocity;
}

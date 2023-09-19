#include "Object2D.h"

Object2D::Object2D() :
	scale(0.0f),
	rotation(0.0f),
	position(MathVec2<float>(0.0f, 0.0f)),
	triangles(),
	bounds() {}

Object2D::Object2D(float sca, float rot, MathVec2<float> pos) :
	scale(sca),
	rotation(rot),
	position(pos) {}

Object2D::~Object2D()
{
}

void Object2D::setScale(float s)
{
	this->scale = s;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::setRotation(float r)
{
	this->rotation = r;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::setPosition(MathVec2<float> p)
{
	this->position = p;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::setPosition(MathVec2<float>& p)
{
	this->position = p;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::setPosition(float x1, float x2)
{
	this->position = MathVec2<float>(x1, x2);
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::setPosRotScale(MathVec2<float>& p, float r, float s)
{
	this->position = p;
	this->rotation = r;
	this->scale = s;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::setPosRotScale(float x1, float x2, float r, float s)
{
	this->position = MathVec2<float>(x1, x2);
	this->rotation = r;
	this->scale = s;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::moveOnX(float x)
{
	this->position[0] += x;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

void Object2D::moveOnY(float y)
{
	this->position[1] += y;
	bounds.updateTempCornerUsing(this->rotation, this->scale, this->position);
}

float Object2D::getScale()
{
	return this->scale;
}

float Object2D::getRotation()
{
	return this->rotation;
}

MathVec2<float>& Object2D::getPosition()
{
	return this->position;
}

void Object2D::addTriangle(Triangle t)
{
	// Dreieck der Liste hinzufügen
	triangles.push_back(t);

	// BoundingBox aktualisieren
	for (int i = 0; i < 3; i++)
	{
		if (t[i][0] < bounds.topLeftVec[0]) bounds.topLeftVec[0] = t[i][0];
		if (t[i][0] > bounds.botRightVec[0]) bounds.botRightVec[0] = t[i][0];

		if (t[i][1] < bounds.botRightVec[1]) bounds.botRightVec[1] = t[i][1];
		if (t[i][1] > bounds.topLeftVec[1]) bounds.topLeftVec[1] = t[i][1];
	}
}

void Object2D::prepare(ViewPortGL& vp)
{
	// Für jedes Dreieck in triangles:
	for (auto iter = this->triangles.begin(); iter != this->triangles.end(); iter++) 
	{
		// Vektoren des Dreiecks übernehmen
		MathVec2<float> v1 = (*iter)[0];
		MathVec2<float> v2 = (*iter)[1];
		MathVec2<float> v3 = (*iter)[2];

		// Vektoren Skallieren
		v1 = MathVec2<float>(v1[0] * this->scale, v1[1] * this->scale);
		v2 = MathVec2<float>(v2[0] * this->scale, v2[1] * this->scale);
		v3 = MathVec2<float>(v3[0] * this->scale, v3[1] * this->scale);

		// Vektoren Rotieren
		v1 = getRotationMatrix(this->rotation) * v1;
		v2 = getRotationMatrix(this->rotation) * v2;
		v3 = getRotationMatrix(this->rotation) * v3;

		// Vektoren verschieben
		v1 = v1 + this->position;
		v2 = v2 + this->position;
		v3 = v3 + this->position;

		// Dreieck zeichnen
		vp.prepareTriangle(v1[0], v1[1], v2[0], v2[1], v3[0], v3[1], iter->getColor());
	}
}

bool Object2D::boundingBoxContains(MathVec2<float> point)
{
	// BoundingBox in zwei Dreiecke aufteilen und für jedes prüfen ob der punkt in ihm liegt
	Triangle t1(this->bounds.tempCorner1[0], this->bounds.tempCorner1[1],
		this->bounds.tempCorner2[0], this->bounds.tempCorner2[1],
		this->bounds.tempCorner3[0], this->bounds.tempCorner3[1]);
	Triangle t2(this->bounds.tempCorner1[0], this->bounds.tempCorner1[1],
		this->bounds.tempCorner3[0], this->bounds.tempCorner3[1],
		this->bounds.tempCorner4[0], this->bounds.tempCorner4[1]);

	if (t1.contains(point)) return true;
	if (t2.contains(point)) return true;
	
	return false;
}

bool Object2D::collidesWith(Object2D& other)
{
	if (other.boundingBoxContains(this->bounds.tempCorner1)) return true;
	if (other.boundingBoxContains(this->bounds.tempCorner2)) return true;
	if (other.boundingBoxContains(this->bounds.tempCorner3)) return true;
	if (other.boundingBoxContains(this->bounds.tempCorner4)) return true;
	
	return false;
}

void Object2D::prepareBoundingBox(ViewPortGL& vp)
{
	// zeichnet linien wo die bounding box ist
	vp.prepareLine(this->bounds.tempCorner1[0], this->bounds.tempCorner1[1], this->bounds.tempCorner2[0], this->bounds.tempCorner2[1], 255, 0, 0);
	vp.prepareLine(this->bounds.tempCorner2[0], this->bounds.tempCorner2[1], this->bounds.tempCorner3[0], this->bounds.tempCorner3[1], 255, 0, 0);
	vp.prepareLine(this->bounds.tempCorner3[0], this->bounds.tempCorner3[1], this->bounds.tempCorner4[0], this->bounds.tempCorner4[1], 255, 0, 0);
	vp.prepareLine(this->bounds.tempCorner4[0], this->bounds.tempCorner4[1], this->bounds.tempCorner1[0], this->bounds.tempCorner1[1], 255, 0, 0);
}

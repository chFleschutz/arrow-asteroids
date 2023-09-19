#include "BoundingBox.h"

BoundingBox::BoundingBox() :
	topLeftVec(MathVec2<float>(0.0f, 0.0f)),
	botRightVec(MathVec2<float>(0.0f, 0.0f)),
	tempCorner1(MathVec2<float>(0.0f, 0.0f)),
	tempCorner2(MathVec2<float>(0.0f, 0.0f)),
	tempCorner3(MathVec2<float>(0.0f, 0.0f)),
	tempCorner4(MathVec2<float>(0.0f, 0.0f)) {}

BoundingBox::BoundingBox(MathVec2<float> a, MathVec2<float> b) :
	topLeftVec(a),
	botRightVec(b),
	tempCorner1(a),
	tempCorner2(MathVec2<float>(b[0], a[1])),
	tempCorner3(b),
	tempCorner4(MathVec2<float>(a[0], b[1])) {}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::updateTempCornerUsing(float rotation, float scale, MathVec2<float> position)
{
	// Skalieren
	this->tempCorner1 = MathVec2<float>(this->topLeftVec[0] * scale, this->topLeftVec[1] * scale);
	this->tempCorner2 = MathVec2<float>(this->botRightVec[0] * scale, this->topLeftVec[1] * scale);
	this->tempCorner3 = MathVec2<float>(this->botRightVec[0] * scale, this->botRightVec[1] * scale);
	this->tempCorner4 = MathVec2<float>(this->topLeftVec[0] * scale, this->botRightVec[1] * scale);

	// Rotieren
	this->tempCorner1 = getRotationMatrix(rotation) * this->tempCorner1;
	this->tempCorner2 = getRotationMatrix(rotation) * this->tempCorner2;
	this->tempCorner3 = getRotationMatrix(rotation) * this->tempCorner3;
	this->tempCorner4 = getRotationMatrix(rotation) * this->tempCorner4;

	// Verschieben
	this->tempCorner1 = this->tempCorner1 + position;
	this->tempCorner2 = this->tempCorner2 + position;
	this->tempCorner3 = this->tempCorner3 + position;
	this->tempCorner4 = this->tempCorner4 + position;

}

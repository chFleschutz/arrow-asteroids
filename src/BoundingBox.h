#pragma once
#include "MathVec.h"
#include "MatrixFactory.h"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(MathVec2<float> a, MathVec2<float> b);
	~BoundingBox();

	void updateTempCornerUsing(float rotation, float scale, MathVec2<float> position);

	MathVec2<float> topLeftVec, botRightVec;
	MathVec2<float> tempCorner1, tempCorner2, tempCorner3, tempCorner4;
};


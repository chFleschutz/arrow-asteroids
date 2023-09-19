#pragma once

#include "Shape.h"
#include "MathVec.h"

class Square : public Shape {
public:
	Square(int red, int green, int blue);
	void prepare(ViewPortGL& vp, int centerX, int centerY, float size) override;
	void prepare(ViewPortGL& vp, float centerX, float centerY, float size) override;

private:
	MathVec2<float> upperLeft;
	MathVec2<float> upperRight;
	MathVec2<float> lowerLeft;
	MathVec2<float> lowerRight;
};


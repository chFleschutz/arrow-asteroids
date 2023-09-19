#pragma once
#include "MathVec.h"
#include "Color.h"
#include "ViewPortGL.h"

class Triangle {

public:
	Triangle();
	Triangle(MathVec2<float> p1, MathVec2<float> p2, MathVec2<float> p3);
	Triangle(MathVec2<float> p1, MathVec2<float> p2, MathVec2<float> p3, int r, int g, int b);
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3	);
	Triangle(MathVec2<float> p1, MathVec2<float> p2, MathVec2<float> p3, Color c);
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c);
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3, int r, int g, int b);

	bool contains(MathVec2<float> p);

	void setColor(int r, int g, int b);
	void setColor(Color c);
	Color& getColor();
	MathVec2<float>& operator[](int i);

private:
	MathVec2<float> p1, p2, p3;
	Color col;
};


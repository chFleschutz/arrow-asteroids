#pragma once

#include "Shape.h"

class Disk : public Shape {
public:
	Disk(int red, int green, int blue);
	void prepare(ViewPortGL& vp, int centerX, int centerY, float size) override;
	void prepare(ViewPortGL& vp, float centerX, float centerY, float size) override;

};


#include "Disk.h"
#include <cmath>

Disk::Disk(int red, int green, int blue) : Shape(red, green, blue) {}

void Disk::prepare(ViewPortGL& vp, int centerX, int centerY, float size) {
	float radius = size / 2;
	float radiusSquared = radius * radius;
	for (int y = 0; y < radius; y++) {
		float x = sqrt(radiusSquared - (y * y));
		vp.prepareLine(centerX - static_cast<int>(round(x)), centerY - y,
			centerX + static_cast<int>(round(x)), centerY - y, red, green, blue);
		vp.prepareLine(centerX - static_cast<int>(round(x)), centerY + y,
			centerX + static_cast<int>(round(x)), centerY + y, red, green, blue);
	}
}


void Disk::prepare(ViewPortGL& vp, float centerX, float centerY, float size) {
	float radius = size / 2;
	float radiusSquared = radius * radius;

	float yPixelHeightFact = static_cast<float>(vp.getYSize())/2;
	radius = radius * yPixelHeightFact;
	for (int y = 0; y < radius; y++) {
		float yu = y / yPixelHeightFact;
		float x = sqrt(radiusSquared - (yu * yu));
		vp.prepareLine(centerX - x, centerY + yu, centerX + x, centerY + yu, red, green, blue);
		vp.prepareLine(centerX - x, centerY - yu, centerX + x, centerY - yu, red, green, blue);
	}
}



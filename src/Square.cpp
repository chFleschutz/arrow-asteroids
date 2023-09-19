#include "Square.h"
#include "MatrixFactory.h"
#include "MathMatrix.h"




Square::Square(int red, int green, int blue) 
	: Shape(red, green, blue), upperLeft(-1, -1), upperRight(1, -1), lowerLeft(-1, 1), lowerRight(1, 1) {}

void Square::prepare(ViewPortGL& vp, int centerX, int centerY, float size) {
	MathMatrix<float, 2, 2> m = getRotationMatrix(rotation);
	MathVec2<float> translation = MathVec2<float>(static_cast<float>(centerX), static_cast<float>(centerY));
	MathVec2<float> ul = m * (upperLeft * (size/2)) + translation;
	MathVec2<float> ur = m * (upperRight * (size / 2)) + translation;
	MathVec2<float> ll = m * (lowerLeft * (size / 2)) + translation;
	MathVec2<float> lr = m * (lowerRight * (size / 2)) + translation;

	vp.prepareTriangle(static_cast<int>(ul.get(0)), static_cast<int>(ul.get(1)), 
		static_cast<int>(ur.get(0)), static_cast<int>(ur.get(1)), 
		static_cast<int>(lr.get(0)), static_cast<int>(lr.get(1)), 
		red, green, blue);
	vp.prepareTriangle(static_cast<int>(ul.get(0)), static_cast<int>(ul.get(1)), 
		static_cast<int>(lr.get(0)), static_cast<int>(lr.get(1)), 
		static_cast<int>(ll.get(0)), static_cast<int>(ll.get(1)), 
		red, green, blue);
}


void Square::prepare(ViewPortGL& vp, float centerX, float centerY, float size) {
	MathMatrix<float, 2, 2> m = getRotationMatrix(rotation);
	MathVec2<float> translation = MathVec2<float>(centerX, centerY);
	MathVec2<float> ul = m * (upperLeft * (size / 2)) + translation;
	MathVec2<float> ur = m * (upperRight * (size / 2)) + translation;
	MathVec2<float> ll = m * (lowerLeft * (size / 2)) + translation;
	MathVec2<float> lr = m * (lowerRight * (size / 2)) + translation;

	vp.prepareTriangle(ul.get(0), ul.get(1), ur.get(0), ur.get(1), lr.get(0), lr.get(1), red, green, blue);
	vp.prepareTriangle(ul.get(0), ul.get(1), lr.get(0), lr.get(1), ll.get(0), ll.get(1), red, green, blue);
}

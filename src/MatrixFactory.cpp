#include "MatrixFactory.h"

MathMatrix<float, 2, 2> getRotationMatrix(float angle) {
	MathMatrix<float, 2, 2> m = MathMatrix<float, 2, 2>(0.0f);
	m.set(0, 0, static_cast<float>(cos(angle)));
	m.set(0, 1, static_cast<float>(-sin(angle)));
	m.set(1, 0, static_cast<float>(sin(angle)));
	m.set(1, 1, static_cast<float>(cos(angle)));
	return m;
}

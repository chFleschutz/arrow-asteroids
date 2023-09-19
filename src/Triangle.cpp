#include "Triangle.h"
#include <string>
#include <stdexcept>


using namespace std;

Triangle::Triangle() :
	p1 {MathVec2<float>{ 0.0f, 0.0f }}, 
	p2 {MathVec2<float>{ 0.0f, 0.0f }},
	p3 {MathVec2<float>{ 0.0f, 0.0f }},
	col {Color(255, 0, 0)} {}

Triangle::Triangle(MathVec2<float> p1, MathVec2<float> p2, MathVec2<float> p3) 
	: p1{ p1 }, p2{ p2 }, p3{ p3 }, col{ Color(255, 0, 0) } {}

Triangle::Triangle(MathVec2<float> p1, MathVec2<float> p2, MathVec2<float> p3, int r, int g, int b) 
	: p1{ p1 }, p2{ p2 }, p3{ p3 }, col{ Color(r, g, b) } {}

Triangle::Triangle(MathVec2<float> p1, MathVec2<float> p2, MathVec2<float> p3, Color c)
	: p1{ p1 }, p2{ p2 }, p3{ p3 }, col {c} {}

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) 
	: p1 {MathVec2<float>(x1, y1)}, p2{ MathVec2<float>(x2, y2) }, p3{ MathVec2<float>(x3, y3) } {}

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c)
	: p1{ MathVec2<float>(x1, y1) }, p2{ MathVec2<float>(x2, y2) }, p3{ MathVec2<float>(x3, y3) }, col{c} {}

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3, int r, int g, int b)
	: p1{ MathVec2<float>(x1, y1) }, p2{ MathVec2<float>(x2, y2) }, p3{ MathVec2<float>(x3, y3) }, col{ r, g, b } {}


inline float sgn(float x) {
	if (x < 0.0f) return -1;
	if (x > 0.0f) return 1;
	return 0.0f;
}


bool Triangle::contains(MathVec2<float> q) {
	MathVec2<float> fromP1ToP2 = p2 - p1;
	MathVec2<float> fromP1ToP3 = p3 - p1;
	MathVec2<float> fromP1ToQ = q - p1;

	MathVec3<float> cp12q = MathVec3<float>(fromP1ToP2, 0.0f).
		crossProduct(MathVec3<float>(fromP1ToQ, 0.0f));
	MathVec3<float> cp12p13 = MathVec3<float>(fromP1ToP2, 0.0f).
		crossProduct(MathVec3<float>(fromP1ToP3, 0.0f));
	if (sgn(cp12q[2]) != sgn(cp12p13[2])) return false;

	MathVec3<float> cp13q = MathVec3<float>(fromP1ToP3, 0.0f).
		crossProduct(MathVec3<float>(fromP1ToQ, 0.0f));
	MathVec3<float> cp13p12 = cp12p13 * -1.0f;
	if (sgn(cp13q[2]) != sgn(cp13p12[2])) return false;

	MathVec2<float> fromP2ToP3 = p3 - p2;
	MathVec2<float> fromP2ToP1 = p1 - p2;
	MathVec2<float> fromP2ToQ = q - p2;
	MathVec3<float> cp23q = MathVec3<float>(fromP2ToP3, 0.0f).
		crossProduct(MathVec3<float>(fromP2ToQ, 0.0f));
	MathVec3<float> cp23p21 = MathVec3<float>(fromP2ToP3, 0.0f).
		crossProduct(MathVec3<float>(fromP2ToP1, 0.0f));
	return sgn(cp23q[2]) == sgn(cp23p21[2]);
}



void Triangle::setColor(int r, int g, int b) {
	col = Color(r, g, b);
}

void Triangle::setColor(Color c) {
	col = c;
}


Color& Triangle::getColor() {
	return col;
}

MathVec2<float>& Triangle::operator[](int i) {
	if (i == 0) return p1;
	if (i == 1) return p2;
	if (i == 2) return p3;
	throw logic_error("Unknown vertex index: " + to_string(i));
}


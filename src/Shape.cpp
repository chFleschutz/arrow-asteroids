#include "Shape.h"



Shape::Shape(int red, int green, int blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->rotation = 0.0f;
}

void Shape::setRotation(float w) {
	rotation = w;
}

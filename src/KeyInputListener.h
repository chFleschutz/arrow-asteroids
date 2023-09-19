#pragma once
#include "WindowInterface.h"


class KeyInputListener {
public:
	virtual void operator()(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};


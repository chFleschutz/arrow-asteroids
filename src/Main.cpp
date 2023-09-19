#include <time.h>
#include "ViewPortGL.h"
#include "AsteroidsGameSession.h"

using namespace std;

AsteroidsGameSession* session;

void keyInputListener(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((action == GLFW_PRESS) && (key == GLFW_KEY_LEFT)) {
        session->leftKeyDown = true;
    }
    if ((action == GLFW_RELEASE) && (key == GLFW_KEY_LEFT)) {
        session->leftKeyDown = false;
    }
    if ((action == GLFW_PRESS) && (key == GLFW_KEY_RIGHT)) {
        session->rightKeyDown = true;
    }
    if ((action == GLFW_RELEASE) && (key == GLFW_KEY_RIGHT)) {
        session->rightKeyDown = false;
    }
    if ((action == GLFW_PRESS) && (key == GLFW_KEY_UP)) {
        session->upKeyDown = true;
    }
    if ((action == GLFW_RELEASE) && (key == GLFW_KEY_UP)) {
        session->upKeyDown = false;
    }
    if ((action == GLFW_PRESS) && (key == GLFW_KEY_DOWN)) {
        session->downKeyDown = true;
    }
    if ((action == GLFW_RELEASE) && (key == GLFW_KEY_DOWN)) {
        session->downKeyDown = false;
    }

    if ((action == GLFW_PRESS) && (key == GLFW_KEY_LEFT_CONTROL)) {
        session->shoot();
    }

    if ((action == GLFW_PRESS) && (key == GLFW_KEY_ENTER)) {
        session->enterCallback();
    }

}

int main() 
{
    srand(time(nullptr));
	ViewPortGL* vp = new ViewPortGL("Arrow Astroids", 1920, 1080);
    vp->addKeyListener(keyInputListener);

    session = new AsteroidsGameSession(vp);
    session->startSession();

	return 0;
}
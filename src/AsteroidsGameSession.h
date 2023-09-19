#pragma once
#include <cmath>
#include <iostream>
#include <list>
#include "MatrixFactory.h"
#include "Object2D.h"
#include "AsteroidObject.h"
#include "BulletObject.h"
#include "CharSet.h"

enum Status {
	STATUS_MENUE,
	STATUS_GAMELOOP,
	STATUS_GAMEOVER
};

class AsteroidsGameSession
{
public:
	AsteroidsGameSession(ViewPortGL* vp);
	~AsteroidsGameSession();

	void startSession();
	void shoot();
	void enterCallback();

	bool leftKeyDown, rightKeyDown, upKeyDown, downKeyDown;

private:
	void handleMenue();
	void handleGameloop();
	void handleGameover();

	void handleShipMovement();
	void handleAsteroids();
	void handleCollision();
	void handleGraphicOutput();
	void updateObjectPosition();

	MathVec2<float> getVecOutOfBounds();
	void resetGame();
	void displayStringWithShadow(string s, int yPos, int charSize, Color textColor, Color shadowColor);

	// Game Constants
	const float acceleration;
	const float turnSpeed;
	const float bulletSpeed;
	const float aspectRatio;
	const int maxAsteroids;
	const float maxAsteroidScale;
	const float minAsteroidScale;
	const float maxAsteroidVelocity;

	// Text Constants
	float CharSizeRatio;

	// Game-Variablen
	MathVec2<float> currentVelocity;
	float currentRotation;
	int asteroidCount;

	ViewPortGL* vp;

	Object2D spaceShip;
	list<AsteroidObject> asteroids;
	list<BulletObject> bullets;

	int gameStatus;
	int score;
};


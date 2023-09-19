#include "AsteroidsGameSession.h"
#include "CharSet.h"

using namespace std;

AsteroidsGameSession::AsteroidsGameSession(ViewPortGL* viewPort) :
	acceleration(0.00008f),
	turnSpeed(0.035f),
	bulletSpeed(0.015f),
	maxAsteroids(10),
	aspectRatio(viewPort->getMaxX()),
	currentVelocity {0.0f, 0.0f},
	gameStatus(STATUS_MENUE),
	CharSizeRatio(0.5f),
	maxAsteroidScale(2.0f),
	minAsteroidScale(0.7f),
	maxAsteroidVelocity(0.005)
{
	vp = viewPort;
	leftKeyDown = false;
	rightKeyDown = false;
	upKeyDown = false;
	downKeyDown = false;
	currentRotation = 0.0f;
	asteroidCount = 0;
	score = 0;

	// spaceship bauen
	spaceShip.addTriangle(Triangle(0.1f, 0.0f, -0.1f, 0.1f, -0.05, 0.0f, 0, 0, 255));
	spaceShip.addTriangle(Triangle(0.1f, 0.0f, -0.1f, -0.1f, -0.05, 0.0f, 0, 0, 255));
	spaceShip.setPosRotScale(0.0f, 0.0f, 0.0f, 1.0f);

	cout << "=== Session Info ===" << endl;
	cout << "Gamestatus: " << gameStatus << endl;
	cout << "Aspect Ratio: " << aspectRatio << endl;
	cout << "Max Asteroids: " << maxAsteroids << endl;
	cout << "Bullet Speed: " << bulletSpeed << endl;
	cout << "Ship Turn Speed: " << turnSpeed << endl;
	cout << "Ship Acceleration: " << acceleration << endl << endl;
}

AsteroidsGameSession::~AsteroidsGameSession()
{
}

void AsteroidsGameSession::startSession()
{
	while (!vp->windowShouldClose())
	{
		vp->clearViewPort();

		if (gameStatus == STATUS_MENUE) handleMenue();
		if (gameStatus == STATUS_GAMELOOP) handleGameloop();
		if (gameStatus == STATUS_GAMEOVER) handleGameover();

		vp->sendLines();
		vp->sendPixels();
		vp->sendTriangles();
		vp->swapBuffers();
	}
}

void AsteroidsGameSession::shoot()
{
	// Add Bullet
	MathVec2<float> direction(cos(currentRotation) * bulletSpeed, sin(currentRotation) * bulletSpeed);

	BulletObject b(3.0f, currentRotation, spaceShip.getPosition(), direction);
	bullets.push_front(b);

	cout << "Pew" << endl;
}

void AsteroidsGameSession::enterCallback()
{
	//Switch from Menue to Game
	if (gameStatus == STATUS_MENUE)
	{
		gameStatus = STATUS_GAMELOOP;	
		resetGame();
	}
	//Switch from GameOver-Screen to Menue
	else if (gameStatus == STATUS_GAMEOVER) 
		gameStatus = STATUS_MENUE;		
}

void AsteroidsGameSession::handleMenue()
{
	// Show Menue
	spaceShip.prepare(*vp);
	displayStringWithShadow("ARROW ASTEROIDS", 150, 200, Color(255, 255, 255), Color(100, 100, 100));
	displayStringWithShadow("PRESS ENTER TO START", 800, 70, Color(255, 255, 255), Color(100, 100, 100));
}

void AsteroidsGameSession::handleGameloop()
{
	// Handle input
	handleShipMovement();
	// Spawn new Asteroids
	handleAsteroids();
	// Check for Collisions 
	handleCollision();
	// Update all Positions
	updateObjectPosition();
	// Draw Objects
	handleGraphicOutput();
}

void AsteroidsGameSession::handleGameover()
{
	// still show Background
	handleGraphicOutput();

	// Gameover text
	displayStringWithShadow("GAME OVER", 150, 200, Color(255, 255, 255), Color(100, 100, 100));
	displayStringWithShadow("PRESS ENTER TO CONTINUE", 800, 70, Color(255, 255, 255), Color(100, 100, 100));
}

void AsteroidsGameSession::handleShipMovement()
{
	if (upKeyDown) {
		// increase Velocity  
		currentVelocity[0] -= cos(currentRotation) * acceleration;
		currentVelocity[1] -= sin(currentRotation) * acceleration;
	}	
	
	if (downKeyDown) {
		// decrease Velocity 
		currentVelocity[0] += cos(currentRotation) * acceleration;
		currentVelocity[1] += sin(currentRotation) * acceleration;
	}	
	
	if (leftKeyDown) {
		// turn left
		currentRotation += turnSpeed;
	}
	
	if (rightKeyDown) {
		// turn right
		currentRotation -= turnSpeed;
	}

	// Ship Rotation updaten
	spaceShip.setRotation(currentRotation);
}

void AsteroidsGameSession::handleAsteroids()
{
	// Spawns new Asteroids 
	for (int i = asteroidCount; i < maxAsteroids; i++)
	{
		float scale = rand() % static_cast<int>((maxAsteroidScale - minAsteroidScale) * 100) / 100.f + minAsteroidScale;	// Scale 
		float rotation = (rand() % 628) / 100.f;																			// Rotation 0 - ~Tau
		MathVec2<float> position = getVecOutOfBounds();																		// A Position out of Viewport
		MathVec2<float> velocity = MathVec2<float>((rand() % 20 - 10) * maxAsteroidVelocity * 0.1f, (rand() % 20 - 10) * maxAsteroidVelocity * 0.1f);
		
		asteroids.push_front(AsteroidObject(scale, rotation, position, velocity));
		asteroidCount++;

		cout << "Asteroid spawned at: " << to_string(position) << endl;
	}
}

void AsteroidsGameSession::handleCollision()
{
	// Check if Bullet hit Asteroid
	auto iterBul = bullets.begin();
	while (iterBul != bullets.end())
	{
		auto iterAst = asteroids.begin();
		while (iterAst != asteroids.end())
		{
			if (iterBul->collidesWith(*iterAst))
			{
				// Asteroid been hit
				cout << "An Asteroid been hit" << endl;
				// update score
				score++;

				asteroids.erase(iterAst);

				auto iCpyBul = iterBul;
				iterBul++;
				bullets.erase(iCpyBul);

				asteroidCount--;

				break;
			}
			else iterAst++;
		}
		if (iterBul != bullets.end()) iterBul++;
	}

	// Check if spaceship collides with an asteroid
	auto iterAst = asteroids.begin();
	while (iterAst != asteroids.end())
	{
		if (spaceShip.collidesWith(*iterAst))
		{
			// Collision with Asteroid
			cout << "!Collision Alert!" << endl;
			gameStatus = STATUS_GAMEOVER;
		}
		iterAst++;
	}
}

void AsteroidsGameSession::handleGraphicOutput()
{
	// Draw Bullets
	for (BulletObject bul : bullets)
	{
		bul.prepare(*vp);
	}

	// Draw Asteroids
	for (Object2D astro : asteroids)
	{
		astro.prepare(*vp);
	}
	
	// Draw Spaceship
	spaceShip.prepare(*vp);

	// Draw Scoreboard
	displayStringWithShadow("SCORE: " + to_string(score), 1000, 50, Color(255, 255, 255), Color(100, 100, 100));
}

void AsteroidsGameSession::updateObjectPosition()
{
	// Change Asteroid Position
	auto iterAst = asteroids.begin();
	while (iterAst != asteroids.end())
	{
		iterAst->setPosition(iterAst->getPosition() + iterAst->getSpeed() + currentVelocity);
		iterAst++;
	}

	// Check if Asteroids are out of Bounds
	iterAst = asteroids.begin();
	while (iterAst != asteroids.end())
	{
		MathVec2<float> pos = iterAst->getPosition();
		if (iterAst->getPosition()[0] < aspectRatio * -1.0f - 0.3f)
		{
			iterAst->setPosition(MathVec2<float>(pos[0] * -1.0f, pos[1]));
		}
		else if (iterAst->getPosition()[0] > aspectRatio + 0.3f) 
		{
			iterAst->setPosition(MathVec2<float>(pos[0] * -1.0f, pos[1]));
		}
		else if (iterAst->getPosition()[1] < -1.3f)
		{
			iterAst->setPosition(MathVec2<float>(pos[0], pos[1] * -1.0f));
		}
		else if (iterAst->getPosition()[1] > 1.3f)
		{
			iterAst->setPosition(MathVec2<float>(pos[0], pos[1] * -1.0f));
		}
		iterAst++;
	}

	// Update Bullet Location
	auto iterBul = bullets.begin();
	while ( iterBul != bullets.end() )
	{
		iterBul->setPosition(iterBul->getPosition() + iterBul->getDirection());
		
		// Check if out of Bounds
		if (iterBul->getPosition()[0] < aspectRatio * -1.0f || 
			iterBul->getPosition()[0] > aspectRatio ||
			iterBul->getPosition()[1] < -1.0f || 
			iterBul->getPosition()[1] > 1.0f)
		{
			auto  iCopy = iterBul;
			iterBul++;
			this->bullets.erase(iCopy);
		}
		else iterBul++;
	}
}

MathVec2<float> AsteroidsGameSession::getVecOutOfBounds()
{
	// Random Point Out of Screen
	int side = rand() % 4;
	float x, y;

	switch (side)
	{
	default:
		x = 0.0f;
		y = 0.0f;
		break;
	case 0:
		// Upper Border
		x = (rand() % 200 - 100) / 100.f * aspectRatio;
		y = 1.2f;
		break;
	case 1:
		// Left Border
		x = -aspectRatio - 0.2f;
		y = (rand() % 200 - 100) / 100.f;
		break;
	case 2:
		// Right Border
		x = aspectRatio + 0.2f;
		y = (rand() % 200 - 100) / 100.f;
		break;
	case 3:
		// Lower Border
		x = (rand() % 200 - 100) / 100.0f * aspectRatio;
		y = -1.2f;
		break;
	}

	return MathVec2<float>(x, y);
}

void AsteroidsGameSession::resetGame()
{
	// Halt Spaceship
	currentVelocity = MathVec2<float>(0.0f, 0.0f);
	// Delete Asteroids
	asteroids.clear();
	asteroidCount = 0;
	// Delete Remaining Bullets
	bullets.clear();
	// Reset Score
	score = 0;
}

void AsteroidsGameSession::displayStringWithShadow(string s, int yPos, int charSize, Color textColor, Color shadowColor)
{
	int textWidth = s.length() * charSize * CharSizeRatio;
	int x = (vp->getXSize() / 2) - (textWidth / 2);
	int shadowOffset = charSize * 0.025;
	CharSet::instance.drawString(vp, s, x - shadowOffset, yPos + shadowOffset, textWidth, charSize, shadowColor.getRed(), shadowColor.getGreen(), shadowColor.getBlue());
	CharSet::instance.drawString(vp, s, x, yPos, textWidth, charSize, textColor.getRed(), textColor.getGreen(), textColor.getBlue());
}

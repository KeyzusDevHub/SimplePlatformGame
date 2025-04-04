#pragma once

#include "Player.h"

class Platform
{
public:
	// Platform constructor
	Platform(Sprite* pSprite, int startX, int startY, int ID);

	// Allows to check if player has jumped on a platform
	bool HasPlayerJumpedOn(Player* p);

	// Draws platform on board
	void ShowPlatform();

	// Allows platform to move
	void MovePlatform();

	// Returns coordinates (x, y) of the platform object through referenced arguments
	void GetCoordinates(double& outX, double& outY);

	// Simulates camera movement on platform object
	void MoveCamera(int changeY);

	// Allows to check if platform is past the bottom of board
	bool IsOutOfBounds();

	// Returns platform Velocity in X axis
	double GetVelocity();

	// Returns ID of the platform
	int GetID();

	// Returns full (covering all of the Sprite with margins on y-axis) collision rectangle
	Rectangle* GetFullRectangle();

	// Returns full (covering all of the Sprite path with margins on y-axis) collision rectangle
	Rectangle* GetMovingRectangle();

	// Platform destructor
	~Platform();

private:
	double x;
	double y;
	int PlatformSizeX;
	int PlatformSizeY;
	int PlatformID;
	double VelocityX = 0.2;
	Sprite* PlatformSprite;
	Rectangle* PlatformBounceRect;
	Rectangle* PlatformFullRect;
	Rectangle* PlatformMovingRect;
};


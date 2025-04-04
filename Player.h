#pragma once

#include <algorithm>
#include <cmath>

#include "GameFramework.h"
#include "Rectangle.h"
#include "Projectile.h"
#include "Scalings.h"

class Player
{

protected:
	// Makes player move left with constant speed
	void MoveLeft();

	// Makes player move right with constant speed
	void MoveRight();

public:
	// Constructor
	Player(int StartX, int StartY);
	
	// Manage players movement
	void MoveOrStand();

	// Simulates the movenent of camera on Player object
	void MoveCamera(int changeY);

	// Stops the movement
	void Stop(bool dir);

	// Allows player to bounce off platforms
	void Bounce();

	// Allows player to shoot and stop shooting
	void MakeShoot();

	// Returns the (x,y) coordinates of the player to referenced arguments
	void GetCoordinates(double& outX, double& outY);

	// Allows to check if player is falling
	bool IsFalling();

	// Allows to check if player is shooting
	bool IsShooting();

	// Changes the direction of players movement
	void MakeMove(bool dir);

	// Checks collision with given projectile
	bool CheckCollision(Projectile* p);

	// Kills player
	void Kill();

	// Allows to check if player is alive or not
	bool IsAlive();

	// Allows to check if player is past the bottom of board
	bool IsOutOfBounds();

	// Allows to check if player is in the right position to gain immunity
	bool CanBeImmune();

	// Changes the state of players immunity
	void ChangeImmunity();

	// Allows to get Player collision rectangle for jumping (without nose)
	Rectangle* GetPlayerJumpRectangle();

	// Allows to get the Player full rectangle (with nose)
	Rectangle* GetPlayerFullRectangle();

	// Spawns a projectile and returns it
	Projectile* SpawnProjectile(Sprite* ProjectileSprite, int mouseX, int mouseY);

	// Player destructor
	~Player();

private:
	double x;
	double y;
	int PlayerSizeX;
	int PlayerSizeY;
	double VelocityX = 0.4;
	double VelocityY = 1.0;
	bool direction; // left == 1, right == 0
	bool moving; // moving == 1, standing == 0
	bool shooting;
	double BounceVelocity;
	double FallSpeed = 0.002;
	bool Alive = true;
	bool Immunity = true;
	Sprite* PlayerRight;
	Sprite* PlayerLeft;
	Sprite* PlayerShoot;
	Rectangle* JumpRect;
	Rectangle* LeftRect;
	Rectangle* RightRect;
	Rectangle* ShootRect;
};


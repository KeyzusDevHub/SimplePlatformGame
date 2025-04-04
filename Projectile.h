#pragma once

#include "GameFramework.h"
#include "Rectangle.h"
#include "Scalings.h"

class Projectile
{
public:
	// Projectile constructor
	Projectile(Sprite* pSprite, int startX, int startY, double velX, double velY);
	
	// Changes the position of projectile on board
	void MoveProjectile();

	// Simulates camera movement on projectile object
	void MoveCamera(int changeY);

	// Returns projectile collision rectangle 
	Rectangle* GetProjectileRectangle();

	// Marks projectile as ready to be despawned (after hit)
	void Despawn();

	// Allows to check if the projectile should be despawned
	bool ShouldBeDespawned();

	// Allows to check if the projectile if past bottom or top of board
	bool IsOutOfBounds();

	// Projectile destructor
	~Projectile();

private:
	double x, y;
	int ProjectileSizeX;
	int ProjectileSizeY;
	double VelocityX, VelocityY;
	bool ToDespawn = false;
	Sprite* ProjectileSprite;
	Rectangle* ProjectileRect;
};


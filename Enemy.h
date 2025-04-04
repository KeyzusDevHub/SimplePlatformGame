#pragma once

#include "Platform.h"
#include "GameFramework.h"
#include "Projectile.h"

class Enemy
{
public:
	// Enemy constructor
	Enemy(Sprite* eSprite, Platform* pSource, bool moving = false);

	// Draws the enemy sprite on the board
	void ShowEnemy();

	// Checks collision with a player
	bool CheckCollision(Player* p);

	// Checks collision with given projectile
	bool CheckCollision(Projectile* p);

	// Simulates camera movement on enemy object
	void MoveCamera(int changeY);

	// Allows to check if enemy is alive or not
	bool IsAlive();

	// Allows to check if the enemy is past bottom of the board
	bool IsOutOfBounds();

	// Changes enemy life based on given argument
	void ChangeLife(int damage);

	// Returns enemy full (with potential movement path) collision rectangle
	Rectangle* GetEnemyRectangle();

	// Enemy destructor
	~Enemy();
private:
	double x = 0;
	double y = 0;
	double VelocityX;
	int EnemySizeX = 0;
	int EnemySizeY = 0;
	int Life = 3;
	Sprite* EnemySprite;
	Rectangle* EnemyUpperRect;
	Rectangle* EnemyLowerRect;
	Rectangle* EnemyFullRect;
};


#pragma once

#include <string>
#include <random>
#include <deque>

#include "GameFramework.h"
#include "Player.h"
#include "Platform.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Coin.h"
#include "Turret.h"
#include "Scalings.h"

class World
{
protected:
	// Used to spawn platform and (not always) enemy on the top of it
	int SpawnPlatformAndEnemy();

	// Draws scores on top of the board
	void ShowScores();
	
	// Manages the spawn of coins on the board
	void SpawnCoin();

	// Checks all collisions to the rectangle of given object
	bool CheckAllCollisionsTo(Rectangle* rect);

public:
	// World constructor
	World();

	// Draws all of the objects controlled by world
	void DrawWorld();

	// Checks all important collisions between objects on the board
	void CheckCollisions();

	// Manages the spawn of projectiles
	void SpawnProjectile(int mouseX, int mouseY, bool type);

	// Clears all of possessed double-ended queues from unused objects
	void ClearQueues();

	// Spawns all of the needed world environment
	void SpawnAll();

	// Manages the simulation of camera on all controlled objects 
	void MoveAll();

	// Makes the player immune
	void StartPlayerImmunity();

	// Ends player immunity
	void StopPlayerImmunity();

	// Allows to check if the world shoud be restarted
	bool ToRestart();

	// Allows to check if the player can use immunity
	bool CanPlayerBeImmune();

	// Returns player object
	Player* GetPlayer();

	// World destructor
	~World();
private:
	int CameraDistance = 0;
	int highestPlatform = 0;
	int CoinBalance = 0;
	int PlatformScore = 0;
	long int PlatformsSpawned = 0;
	long int Score = 0;
	bool HasPlayerBounced = false;
	Player* player;
	Turret* turret;
	Sprite* PlatformSprite;
	Sprite* ProjectileSprite;
	Sprite* TurretProjectileSprite;
	Sprite* BackgroundSprite;
	Sprite* CoinSprite;
	Sprite* TopSprite;
	Sprite* EnemySprite;
	Sprite* TurretSprite;
	Sprite* Numbers[10];
	std::deque<Platform*> PlatformsStatic;
	std::deque<Platform*> PlatformsMoving;
	std::deque<Projectile*> PlayerProjectiles;
	std::deque<Projectile*> TurretProjectiles;
	std::deque<Enemy*> Enemies;
	std::deque<Coin*> Coins;
};


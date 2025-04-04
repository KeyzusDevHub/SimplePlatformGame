#pragma once

#include <cmath>

#include "Player.h"
#include "Projectile.h"

class Turret
{
public:
	// Turret constructor
	Turret(Sprite* tSprite, int startX, int startY);

	// Draws turret on board
	void ShowTurret();

	// Spawns projectile and returns it
	Projectile* SpawnProjectile(Sprite* ProjectileSprite, Player* p);

	// Turret destructor
	~Turret();
	
private:
	int x;
	int y;
	int TurretSizeX;
	int TurretSizeY;
	Sprite* TurretSprite;
};


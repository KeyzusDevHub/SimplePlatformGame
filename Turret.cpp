#include "Turret.h"

Turret::Turret(Sprite* tSprite, int startX, int startY) {
	TurretSprite = tSprite;
	x = startX;
	y = startY;
	getSpriteSize(TurretSprite, TurretSizeX, TurretSizeY);
}

void Turret::ShowTurret() {
	drawSprite(TurretSprite, x, y);
}

Projectile* Turret::SpawnProjectile(Sprite* ProjectileSprite, Player* p) {
	int spriteX, spriteY;
	getSpriteSize(ProjectileSprite, spriteX, spriteY);
	double VectorX, VectorY;
	double playerX, playerY;
	p->GetCoordinates(playerX, playerY);
	VectorX = playerX - x;
	VectorY = y - playerY;
	double VectorLen = std::sqrt(VectorX * VectorX + VectorY * VectorY);
	VectorX /= VectorLen;
	VectorY /= VectorLen;
	return new Projectile(ProjectileSprite, (int)(x + (TurretSizeX - spriteX) / 2), (int)y + TurretSizeY, VectorX, VectorY);
}

Turret::~Turret() {

}
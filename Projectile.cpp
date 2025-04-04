#include "Projectile.h"


Projectile::Projectile(Sprite* pSprite, int startX, int startY, double VelX, double VelY) {
	getSpriteSize(pSprite, ProjectileSizeX, ProjectileSizeY);
	x = (double) startX;
	y = (double) startY;
	ProjectileSprite = pSprite;
	VelocityX = VelX * Scalings::GetProjectileDefaultScale();
	VelocityY = VelY * Scalings::GetProjectileDefaultScale();
	ProjectileRect = new Rectangle(startX, startY, ProjectileSizeX, ProjectileSizeY);
}

void Projectile::MoveProjectile() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	x += VelocityX;
	y -= VelocityY;
	drawSprite(ProjectileSprite, (int)x, (int)y);
	if ((int)x < -(ProjectileSizeX / 2)) {
		x = (double)(screenX - (ProjectileSizeX / 2));
	}
	else if ((int)x > screenX - (ProjectileSizeX / 2)) {
		x = (double)(-(ProjectileSizeX / 2));
	}
	ProjectileRect->UpdateRectangle((int)x, (int)y);
}

void Projectile::MoveCamera(int changeY) {
	y += changeY;
	ProjectileRect->UpdateRectangle((int)x, (int)y);
}

Rectangle* Projectile::GetProjectileRectangle() {
	return ProjectileRect;
}

void Projectile::Despawn() {
	ToDespawn = true;
}

bool Projectile::ShouldBeDespawned() {
	return ToDespawn;
}

bool Projectile::IsOutOfBounds() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (y > screenY || y < 0) {
		return true;
	}
	return false;
}

Projectile::~Projectile() {

}
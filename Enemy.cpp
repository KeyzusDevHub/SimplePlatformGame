#include "Enemy.h"


Enemy::Enemy(Sprite* eSprite, Platform* pSource, bool moving) {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	EnemySprite = eSprite;
	getSpriteSize(eSprite, EnemySizeX, EnemySizeY);
	pSource->GetCoordinates(x, y);
	y -= EnemySizeY;
	EnemyUpperRect = new Rectangle((int)x, (int)y, EnemySizeX, EnemySizeY / 2);
	EnemyLowerRect = new Rectangle((int)x, (int)y + EnemySizeY / 2, EnemySizeX, EnemySizeY / 2);
	if (moving) {
		EnemyFullRect = new Rectangle(0, (int)y, screenX, EnemySizeY);
		VelocityX = pSource->GetVelocity();
	}
	else {
		EnemyFullRect = new Rectangle((int)x, (int)y, EnemySizeX, EnemySizeY);
		VelocityX = 0;
	}
}

bool Enemy::CheckCollision(Player* p) {
	if (!p->IsFalling()) {
		if (EnemyUpperRect->ColideRectangles(p->GetPlayerFullRectangle()) || EnemyLowerRect->ColideRectangles(p->GetPlayerFullRectangle())
			|| p->GetPlayerFullRectangle()->ColideRectangles(EnemyUpperRect) || p->GetPlayerFullRectangle()->ColideRectangles(EnemyLowerRect)) {
			p->Kill();
			return true;
		}
	}
	else {
		if (EnemyLowerRect->ColideRectangles(p->GetPlayerFullRectangle()) || p->GetPlayerFullRectangle()->ColideRectangles(EnemyLowerRect)) {
			p->Kill();
			return true;
		}
		else if (EnemyUpperRect->ColideRectangles(p->GetPlayerFullRectangle()) || p->GetPlayerFullRectangle()->ColideRectangles(EnemyUpperRect)) {
			ChangeLife(3);
			return true;
		}
	}
	return false;
}

bool Enemy::CheckCollision(Projectile* p) {
	if (EnemyUpperRect->ColideRectangles(p->GetProjectileRectangle()) || EnemyLowerRect->ColideRectangles(p->GetProjectileRectangle())) {
		ChangeLife(1);
		return true;
	}
	return false;
}

void Enemy::ShowEnemy() {
	x += VelocityX;
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (x < 0 || (x + EnemySizeX) > screenX) {
		VelocityX *= -1;
	}
	drawSprite(EnemySprite, (int) x, (int) y);
	EnemyUpperRect->UpdateRectangle((int)x, (int)y);
	EnemyLowerRect->UpdateRectangle((int)x, (int)y + EnemySizeY / 2);
	if (VelocityX > 0) {
		EnemyFullRect->UpdateRectangle(0, (int)y);
	}
	else {
		EnemyFullRect->UpdateRectangle((int)x, (int)y);
	}
}

void Enemy::MoveCamera(int changeY) {
	y += changeY;
}

void Enemy::ChangeLife(int damage) {
	Life -= damage;
}

bool Enemy::IsAlive() {
	return Life > 0;
}

bool Enemy::IsOutOfBounds() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (y > screenY) {
		return true;
	}
	return false;
}

Rectangle* Enemy::GetEnemyRectangle() {
	return EnemyFullRect;
}

Enemy::~Enemy() {
	delete EnemyUpperRect;
	delete EnemyLowerRect;
	delete EnemyFullRect;
}
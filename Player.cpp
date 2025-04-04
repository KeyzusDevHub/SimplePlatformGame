#include "Player.h"

Player::Player(int StartX, int StartY) {
	x = (double)StartX;
	y = (double)StartY;

	PlayerRight = createSprite("./data/PlayerRight.png");
	PlayerLeft = createSprite("./data/PlayerLeft.png");

	getSpriteSize(PlayerRight, PlayerSizeX, PlayerSizeY);

	PlayerSizeX = (int)((double)PlayerSizeY * Scalings::GetDefaultScale() * 0.5);
	PlayerSizeY = (int)((double)PlayerSizeY * Scalings::GetDefaultScale() * 0.5);

	setSpriteSize(PlayerRight, PlayerSizeX, PlayerSizeY);
	setSpriteSize(PlayerLeft, PlayerSizeX, PlayerSizeY);

	x -= (double)(PlayerSizeX / 2);

	VelocityX *= Scalings::GetScaleX();
	BounceVelocity = VelocityY *= Scalings::GetScaleY();
	FallSpeed *= Scalings::GetScaleY();
	direction = 0;
	shooting = false;
	moving = false;

	JumpRect = new Rectangle((int)x + PlayerSizeX / 4, (int)y + (4 * PlayerSizeY / 5), PlayerSizeX / 2, PlayerSizeY / 5);
	LeftRect = new Rectangle((int)x, (int)y + PlayerSizeY / 4, 3 * PlayerSizeX / 4, 3 * PlayerSizeY / 4);
	RightRect = new Rectangle((int)x + PlayerSizeX / 4, (int)y + PlayerSizeY / 4, 3 * PlayerSizeX / 4, 3 * PlayerSizeY / 4);
	ShootRect = new Rectangle((int)x + PlayerSizeX / 4, (int)y, PlayerSizeX / 2, PlayerSizeY);
}

void Player::MoveOrStand() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (direction) {
		MoveLeft();
	}
	else {
		MoveRight();
	}
	VelocityY -= FallSpeed;
	if (((int)y > (screenY - 4 * PlayerSizeY / 5)) && Immunity) {
		Bounce();
	}
	int tmpX = (int) x;
	int tmpY = (int) y;
	JumpRect->UpdateRectangle(tmpX + PlayerSizeX / 4, tmpY + (4 * PlayerSizeY / 5));
	LeftRect->UpdateRectangle(tmpX, tmpY + PlayerSizeY / 4);
	RightRect->UpdateRectangle(tmpX + PlayerSizeX / 4, tmpY + PlayerSizeY / 4);
	ShootRect->UpdateRectangle(tmpX + PlayerSizeX / 4, tmpY);
}

void Player::Bounce() {
	VelocityY = BounceVelocity;
}

void Player::MakeMove(bool dir) {
	moving = true;
	direction = dir;
}

void Player::MoveCamera(int changeY) {
	y += changeY;
	JumpRect->UpdateRectangle((int)x + PlayerSizeX / 4, (int)y + (4 * PlayerSizeY / 5));
	LeftRect->UpdateRectangle((int)x, (int)y + PlayerSizeY / 4);
	RightRect->UpdateRectangle((int)x + PlayerSizeX / 4, (int)y + PlayerSizeY / 4);
	ShootRect->UpdateRectangle((int)x + PlayerSizeX / 4, (int)y);
}

void Player::Stop(bool dir) {
	if (dir == direction) {
		moving = false;
	}
}

void Player::MoveLeft() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	x -= VelocityX * int(moving);
	y -= VelocityY;
	if ((int)x + (PlayerSizeX / 2) < 0) {
		x = (double)(screenX - (PlayerSizeX / 2));
	}
	drawSprite(PlayerLeft, (int)x, (int)y);
}

void Player::MoveRight() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	x += VelocityX * int(moving);
	y -= VelocityY;
	if ((int)x + (PlayerSizeX / 2) > screenX) {
		x = (double)(-(PlayerSizeX / 2));
	}

	drawSprite(PlayerRight, (int)x, (int)y);

}

void Player::GetCoordinates(double& outX, double& outY) {
	outX = x;
	outY = y;
}

Rectangle* Player::GetPlayerJumpRectangle() {
	return JumpRect;
}

Rectangle* Player::GetPlayerFullRectangle() {
	if (shooting) {
		return ShootRect;
	}
	else if (direction) {
		return LeftRect;
	}
	else {
		return RightRect;
	}
}

Projectile* Player::SpawnProjectile(Sprite* ProjectileSprite, int mouseX, int mouseY) {
	int spriteX, spriteY;
	getSpriteSize(ProjectileSprite, spriteX, spriteY);
	double VectorX, VectorY;
	VectorX = (double)mouseX - x;
	VectorY = y - (double)mouseY;
	double VectorLen = std::sqrt(VectorX * VectorX + VectorY * VectorY);
	VectorX /= VectorLen;
	VectorY /= VectorLen;
	return new Projectile(ProjectileSprite, (int)(x + (PlayerSizeX - spriteX) / 2), (int)y, VectorX, VectorY);
}

void Player::Kill() {
	Alive = false;
}

bool Player::IsAlive() {
	return Alive;
}

bool Player::IsOutOfBounds() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (y > screenY) {
		return true;
	}
	return false;
}

bool Player::IsShooting() {
	return shooting;
}

bool Player::CheckCollision(Projectile* p) {
	Rectangle* Rect = GetPlayerFullRectangle();
	if (Rect->ColideRectangles(p->GetProjectileRectangle()) || Rect->ColideRectangles(p->GetProjectileRectangle())) {
		Kill();
		return true;
	}
	return false;
}

void Player::MakeShoot() {
	shooting = !shooting;
}

bool Player::CanBeImmune() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if ((screenY - (int)y) > (4 * PlayerSizeY / 5)) {
		return true;
	}
	return false;
}

bool Player::IsFalling() {
	return VelocityY < 0.0;
}

void Player::ChangeImmunity() {
	Immunity = !Immunity;
}

Player::~Player() {
	destroySprite(PlayerLeft);
	destroySprite(PlayerRight);
	delete JumpRect;
	delete LeftRect;
	delete RightRect;
	delete ShootRect;
}
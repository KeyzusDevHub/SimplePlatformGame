#include "Platform.h"

Platform::Platform(Sprite* pSprite, int startX, int startY, int ID) {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	x = (double) startX;
	y = (double) startY;
	PlatformSprite = pSprite;
	getSpriteSize(pSprite, PlatformSizeX, PlatformSizeY);

	PlatformBounceRect = new Rectangle(startX, startY, PlatformSizeX, PlatformSizeY / 3);
	PlatformFullRect = new Rectangle(startX, startY - PlatformSizeY / 3, PlatformSizeX, PlatformSizeY + PlatformSizeY / 3);
	PlatformMovingRect = new Rectangle(0, startY - PlatformSizeY / 3, screenX, PlatformSizeY + PlatformSizeY / 3);
	setSpriteSize(PlatformSprite, PlatformSizeX, PlatformSizeY);
	VelocityX *= Scalings::GetScaleX();
	PlatformID = ID;
}

void Platform::ShowPlatform() {
	drawSprite(PlatformSprite, (int) x, (int) y);
}

void Platform::MoveCamera(int changeY) {
	y += (double) changeY;
	PlatformBounceRect->UpdateRectangle((int)x, (int)y);
	PlatformFullRect->UpdateRectangle((int)x, (int)y);
	PlatformMovingRect->UpdateRectangle(0, (int)y);
}

void Platform::GetCoordinates(double& outX, double& outY) {
	outX = x;
	outY = y;
}

bool Platform::HasPlayerJumpedOn(Player* p) {
	if (p->IsFalling()) {
		if (PlatformBounceRect->ColideRectangles(p->GetPlayerJumpRectangle())) {
			return true;
		}
	}
	return false;
}

void Platform::MovePlatform() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (x < 0 || (x + PlatformSizeX) > screenX) {
		VelocityX *= -1;
	}
	x += VelocityX;
	ShowPlatform();
	PlatformBounceRect->UpdateRectangle((int)x, (int)y);
	PlatformFullRect->UpdateRectangle((int)x, (int)y);
}

bool Platform::IsOutOfBounds() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (y > screenY) {
		return true;
	}
	return false;
}

int Platform::GetID() {
	return PlatformID;
}

double Platform::GetVelocity() {
	return VelocityX;
}

Rectangle* Platform::GetFullRectangle() {
	return PlatformFullRect;
}

Rectangle* Platform::GetMovingRectangle() {
	return PlatformMovingRect;
}

Platform::~Platform() {
	delete PlatformBounceRect;
	delete PlatformFullRect;
	delete PlatformMovingRect;
}
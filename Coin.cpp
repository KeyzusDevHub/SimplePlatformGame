#include "Coin.h"

Coin::Coin(Sprite* cSprite, int startX, int startY) {
	x = startX;
	y = startY;
	CoinSprite = cSprite;
	getSpriteSize(cSprite, CoinSizeX, CoinSizeY);
	CoinRect = new Rectangle(x, y, CoinSizeX, CoinSizeY);
}

void Coin::ShowCoin() {
	drawSprite(CoinSprite, x, y);
}

bool Coin::CheckIfPlayerCollects(Player* p) {
	if ((CoinRect->ColideRectangles(p->GetPlayerFullRectangle()) || p->GetPlayerFullRectangle()->ColideRectangles(CoinRect)) && !Collected) {
		Collected = true;
		return true;
	}
	return false;
}

bool Coin::IsCollected() {
	return Collected;
}

bool Coin::IsOutOfBounds() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	if (y > screenY) {
		return true;
	}
	return false;
}

void Coin::MoveCamera(int changeY) {
	y += changeY;
	CoinRect->UpdateRectangle(x, y);
}

Rectangle* Coin::GetCoinRectangle() {
	return CoinRect;
}

Coin::~Coin() {

}
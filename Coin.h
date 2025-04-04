#pragma once

#include "Player.h"

class Coin
{
public:

	// Coin constructor
	Coin(Sprite* cSprite, int startX, int startY);

	// Draws coin on board
	void ShowCoin();

	// Checks if player collides with a coin Sprite
	bool CheckIfPlayerCollects(Player* p);

	// Returns if the coin is collected
	bool IsCollected();

	// Returns if the coin is past bottom of board
	bool IsOutOfBounds();

	// Simulates the movement of camera on coin object
	void MoveCamera(int changeY);

	// Returns coin collision rectangle
	Rectangle* GetCoinRectangle();

	// Coin destructor
	~Coin();

private:
	int x;
	int y;
	int CoinSizeX;
	int CoinSizeY;
	bool Collected = false;
	Sprite* CoinSprite;
	Rectangle* CoinRect;

};


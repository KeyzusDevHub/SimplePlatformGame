#pragma once
class Rectangle
{
public:
	// Rectangle constructor
	Rectangle(int startX, int startY, int sizeX, int sizeY);

	// Checks if rectangles collide
	bool ColideRectangles(Rectangle* r);

	// Updates (x, y) coordinates of rectangle
	void UpdateRectangle(int x, int y);

	// Rectangle destructor
	~Rectangle();
private:
	int x;
	int y;
	int RectangleSizeX;
	int RectangleSizeY;
};
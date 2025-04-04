#include "Rectangle.h"

Rectangle::Rectangle(int startX, int startY, int sizeX, int sizeY) {
	x = startX;
	y = startY;
	RectangleSizeX = sizeX;
	RectangleSizeY = sizeY;
}

bool Rectangle::ColideRectangles(Rectangle* r) {
	int rx = r->x;
	int rsx = r->RectangleSizeX;
	int ry = r->y;
	int rsy = r->RectangleSizeY;
	if (x <= rx && (x + RectangleSizeX) >= rx && y <= ry && (y + RectangleSizeY) >= ry) {
		return true;
	}
	else if (x <= (rx + rsx) && (x + RectangleSizeX) >= (rx + rsx) && y <= ry && (y + RectangleSizeY) >= ry) {
		return true;
	}
	else if (x <= rx && (x + RectangleSizeX) >= rx && y <= (ry + rsy) && (y + RectangleSizeY) >= (ry + rsy)) {
		return true;
	}
	else if (x <= (rx + rsx) && (x + RectangleSizeX) >= (rx + rsx) && y <= (ry + rsy) && (y + RectangleSizeY) >= (ry + rsy)) {
		return true;
	}
	return false;
}

void Rectangle::UpdateRectangle(int updatedX, int updatedY) {
	x = updatedX;
	y = updatedY;
}

Rectangle::~Rectangle() {

}
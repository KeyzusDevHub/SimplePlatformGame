#include "Scalings.h"

void Scalings::SetVariables(double sX, double sY, double dS) {
	ScaleX = sX;
	ScaleY = sY;
	DefaultScale = dS;
	ProjectileDefaultScale *= dS;
	ScoreDefaultScale *= dS;
}

double Scalings::GetScaleX() {
	return ScaleX;
}

double Scalings::GetScaleY() {
	return ScaleY;
}

double Scalings::GetDefaultScale() {
	return DefaultScale;
}

double Scalings::GetProjectileDefaultScale() {
	return ProjectileDefaultScale;
}

double Scalings::GetScoreDefaultScale() {
	return ScoreDefaultScale;
}


double Scalings::ScaleX = 1.0;
double Scalings::ScaleY = 1.0;
double Scalings::DefaultScale = 1.0;
double Scalings::ProjectileDefaultScale = 0.5;
double Scalings::ScoreDefaultScale = 0.9;
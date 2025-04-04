#pragma once
class Scalings
{
public:
	// Sets the values of static variables
	static void SetVariables(double sX, double sY, double dS);

	// Returns ScaleX
	static double GetScaleX();

	// Returns ScaleY
	static double GetScaleY();

	// Returns DefaultScale
	static double GetDefaultScale();

	// Returns ProjectileDefaultScale
	static double GetProjectileDefaultScale();

	// Returns ScoreDefaultScale
	static double GetScoreDefaultScale();

private:
	static double ScaleX;
	static double ScaleY;
	static double DefaultScale;
	static double ProjectileDefaultScale;
	static double ScoreDefaultScale;
};


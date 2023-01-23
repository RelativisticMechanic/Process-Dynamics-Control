/* WIP - A speedometer type indicator for single variable properties */

#ifndef ROUNDMETER_H
#define ROUNDMETER_H

#include "Graph2D.h"

class RoundMeter
{
public:
	olc::PixelGameEngine* app;
	double x;
	double xmin, xmax;

	vec2 position;
	vec2 dimensions;

	RoundMeter() { };
	RoundMeter(olc::PixelGameEngine* app, vec2 position, vec2 dimensions, double x, double xmin, double xmax);
	void Update(double x);
	void Draw();
};

#endif

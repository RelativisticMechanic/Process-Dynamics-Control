#ifndef DRAW_ARC_H
#define DRAW_ARC_H 

/*
	WORK IN PROGRESS: ARC DRAWING ALGORITHM
*/

#include "olcPixelGameEngine.h"
#include <math.h>

inline float cotf(float x)
{
	return tanf(3.14159 * 0.5 - x);
}
inline void DrawIfPointInArc(olc::PixelGameEngine* app, olc::vi2d center, int x, int y, int angle_start, int angle_end, olc::Pixel color)
{
	float deg_to_rad = 3.14159 / 180;
	if (angle_start == 0)
	{
		angle_start = 1;
	}
	float start = angle_start * deg_to_rad;
	float end = angle_end * deg_to_rad; 

	float theta_deg = (int)((atan2f(-y, x)) * (180 / 3.14159) + 360) % 360;
	float cot_xy = cotf(theta_deg * deg_to_rad);
	float tan_xy = tanf(theta_deg * deg_to_rad);
	if (cotf(start) > cot_xy && cotf(end) < cot_xy)
	{
		app->Draw(center + olc::vi2d(x, y), color);
	}
}
inline void DrawArc(olc::PixelGameEngine* app, olc::vi2d center, int radius, int angle_start, int angle_end)
{
	int x = 0;
	int y = radius;
	int d = 1 - radius;

	while (y > x)
	{
		if (d < 0)
			d = 2 + 2 * x + 3;
		else
		{
			d = d + 2 * (x - y) + 5;
			y--;
		}
		x++;
		DrawIfPointInArc(app, center, x, y, angle_start, angle_end, olc::WHITE);
		DrawIfPointInArc(app, center, -x, y, angle_start, angle_end, olc::WHITE);
		DrawIfPointInArc(app, center, x, -y, angle_start, angle_end, olc::WHITE);
		DrawIfPointInArc(app, center, -x, -y, angle_start, angle_end, olc::WHITE);
		DrawIfPointInArc(app, center, y, x, angle_start, angle_end, olc::WHITE);
		DrawIfPointInArc(app, center, y, -x, angle_start, angle_end, olc::WHITE);
		DrawIfPointInArc(app, center, -y, x, angle_start, angle_end, olc::WHITE);
		DrawIfPointInArc(app, center, -y, -x, angle_start, angle_end, olc::WHITE);
	}

}

#endif
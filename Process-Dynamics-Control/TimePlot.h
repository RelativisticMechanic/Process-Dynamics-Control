#ifndef TIMEPLOT_H
#define TIMEPLOT_H

#include "Graph2D.h"

/*
	This is the TimePlot class.

	The TimePlot class allows you to visualize how a variable evolves through time.
	
	TimePlot(olc::PixelGameEngine* app, vec2 pos, vec2 dimensions, double xmin, double xmax, int n);
	Here, you pass position and dimensions of your time plot, along with the range of your x value
	(if your x value is greater than xmin and xmax, it will simply not plot!). The "n" represents
	how many time steps you wish to record. If you're fetching data every 1 second, and want to see
	the output of the last 30 seconds, you'll pass 30.

	To push data to the TimePlot, use the function PushData(double t, double x).

	If you've pushed 30 points, then the TimePlot class will pop the first pushed point, 
	and then push your new data. It works like a stack.

	The TimePlot class uses Graph2D to render the plot to the screen.
*/

class TimePlot
{
public:
	std::vector<double> t;
	std::vector<double> x;
	int n = 0;
	double xmin, xmax;

	TimePlot() { };
	TimePlot(olc::PixelGameEngine* app, vec2 pos, vec2 dimensions, std::string caption, double xmin, double xmax, int n);
	void PushData(double t, double x);
	void Plot();
public:
	Graph2D graph;
};

#endif
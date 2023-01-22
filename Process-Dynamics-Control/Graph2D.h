#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "olcPixelGameEngine.h"

/* TODO: Make the graph borders customizable */
#define GRAPH_BORDER_SIZE 5

typedef olc::vi2d vec2;
typedef olc::vd2d vec2f;

/*
	This is the Graph2D class. 

	A Graph2D represents a graph on the screen. As we'll be needing to render
	various ranges and domains of functions we shall come across, it can be quite
	annoying to have to manually set the origin and scale every time you wish to 
	plot a point.

	Here's where this class comes in to help. You create a Graph2D with a position,
	and dimensions. Next you pass the xorigin and yorigin. Suppose you wanted to create
	a graph centered at (1,1) then xorigin=1, and yorigin=1, then you specify the xspan
	and yspan i.e., how large of a space you want to show on this graph. If you wanted
	to plot a sine curve from -2*pi to +2pi, then your xspan would be 2*pi and your yspan
	would be 1 (sine goes from -1 to 1).

	The grid_x and grid_y are the grid line spacing in x and y direction. Grid lines are drawn
	from the origin to -xspan/-yspan and to +xspan/+yspan (in both directions)
*/
class Graph2D
{
public:
	vec2 position; 
	vec2 dimensions;
	std::string caption = "";
	double origin_x, origin_y;

	olc::PixelGameEngine* app;

	Graph2D() { };
	Graph2D(olc::PixelGameEngine* app, vec2 position, vec2 dimensions, double xorigin, double yorigin, double xspan, double yspan, double grid_x, double grid_y);
	// These are setter functions, in case one wishes to change the 
	// origin and the grid spacing during run time
	void SetGridLines(double delta_x, double delta_y);
	void SetOrigin(double xo, double yo, double x_max, double y_max);
	// This function "ScreenPosFromNormalized" returns the screen position
	// from the normalized coordinates i.e., x E (-1,1) and y E (-1,1)
	olc::vi2d ScreenPosFromNormalized(double x, double y);
	// Returns a "Normalized" coordinate. A normalized coordinate is basically
	// where both x and y values range from -1 to 1.
	vec2f NormalizeCoordinate(double x, double y);
	// Clears the graph screen space
	void Clear();
	// Plots a normalized coordinate on the graph
	void PlotNormalized(double x, double y);
	// Plots a point on the ground
	void PlotPoint(double x, double y);
	// Draws a line between two points on the graph
	void DrawLine(vec2f p1, vec2f p2, olc::Pixel = olc::WHITE, uint32_t pattern=0xFFFFFFFF);
	// Plots the points represented by x[i] and y[i] and then connects them with lines 
	void Plot(std::vector<double> x, std::vector<double> y);

private:
	double grid_start_x, grid_start_y;
	double grid_end_x, grid_end_y;
	double delta_x, delta_y;
	int n_gridx, n_gridy;
	void PlotGridLines();
	void PlotAxes();
};

#endif
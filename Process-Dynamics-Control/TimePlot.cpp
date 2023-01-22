#include "TimePlot.h"

TimePlot::TimePlot(olc::PixelGameEngine* app, vec2 pos, vec2 dimensions, std::string caption, double xmin, double xmax, int n)
{
	this->graph = Graph2D(app, pos, dimensions, 0, (xmin+xmax)/2, 1.0, (xmax - xmin)/2, 0, 0);
	this->xmin = xmin;
	this->xmax = xmax;
	this->n = n;
	this->t = std::vector<double>();
	this->x = std::vector<double>();
	this->graph.caption = caption;
}

void TimePlot::PushData(double t, double x)
{
	std::cout << "TimePlot: Received Data: x: " << x << " t: " << t << std::endl; 
	this->t.push_back(t);
	this->x.push_back(x);

	if (this->t.size() >= this->n)
	{
		this->t.erase(this->t.begin());
		this->x.erase(this->x.begin());
	}
}

void TimePlot::Plot()
{
	if (this->t.size() <= 1) return;
	// Set the x origin to the average of first and last time step
	double t_0 = this->t[0];
	double t_end = this->t[this->t.size() - 1];
	// The y origin of the TimePlot is just the average of the xmax and xmin
	this->graph.SetOrigin( (t_0 + t_end) / 2.0, (xmax + xmin) / 2.0, (t_end - t_0) / 2.0, (this->xmax - this->xmin) / 2);
	// Set appropriate gridlines
	this->graph.SetGridLines((t_end - t_0) / this->t.size(), (this->xmax - this->xmin) / 5.0);
	this->graph.Clear();
	// Plot!
	this->graph.Plot(this->t, this->x);
}
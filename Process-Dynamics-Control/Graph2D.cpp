#include "Graph2D.h"

Graph2D::Graph2D(olc::PixelGameEngine* app, vec2 position, vec2 dimensions, double xorigin, double yorigin, double xspan, double yspan, double grid_x, double grid_y)
{
	this->position = position;
	this->dimensions = dimensions;
	this->SetOrigin(xorigin, yorigin, xspan, yspan);
	this->SetGridLines(grid_x, grid_y);
	this->app = app;
}

void Graph2D::SetOrigin(double xo, double yo, double x_max, double y_max)
{
	this->grid_start_x = xo - x_max;
	this->grid_start_y = yo - y_max;
	this->grid_end_x = xo + x_max;
	this->grid_end_y = yo + y_max;
	// Save for future calculations
	this->origin_x = xo;
	this->origin_y = yo;
}

void Graph2D::SetGridLines(double delta_x, double delta_y)
{
	this->delta_x = delta_x;
	this->delta_y = delta_y;
	// How many grid lines to plot in x direction?
	this->n_gridx = ((grid_end_x - grid_start_x)) / this->delta_x;
	// How many grid lines to plot in y direction?
	this->n_gridy = ((grid_end_y - grid_start_y)) / this->delta_y;
}

void Graph2D::Clear()
{
	this->app->FillRect(this->position - olc::vi2d(GRAPH_BORDER_SIZE, GRAPH_BORDER_SIZE), this->dimensions + 2 * olc::vi2d(GRAPH_BORDER_SIZE, GRAPH_BORDER_SIZE), olc::WHITE);
	this->app->FillRect(this->position, this->dimensions, olc::BLACK);
}

// Maps normalized space to screen space
olc::vi2d Graph2D::ScreenPosFromNormalized(double x, double y)
{
	if (fabs(x) > 1.0)
	{
		x = fabs(x) / x;
	}
	if (fabs(y) > 1.0)
	{
		y = fabs(y) / y;
	}
	// Scale x & y
	x *= this->dimensions.x / 2;
	y *= this->dimensions.y / 2;

	x += this->dimensions.x / 2;
	y = (this->dimensions.y / 2) - y;

	olc::vi2d final = this->position + olc::vi2d(x, y);
	return final;
}
// Plots a normalized coordinate
void Graph2D::PlotNormalized(double x, double y)
{
	this->app->Draw(this->ScreenPosFromNormalized(x, y), olc::RED);
}

// Turns from graph space defined by the origin and maximum values
// to normalized space (-1 to 1)
vec2f Graph2D::NormalizeCoordinate(double x, double y)
{
	vec2f origin = vec2f(this->origin_x, this->origin_y);
	
	double grid_height = (this->grid_end_y - this->grid_start_y);
	double grid_length = (this->grid_end_x - this->grid_start_x);

	vec2f normalized = vec2f(x, y) - origin;

	// Normalize between -1 and 1
	normalized.x = normalized.x / (grid_length / 2);
	normalized.y = normalized.y / (grid_height / 2);
	//std::cout << normalized.x << "," << normalized.y << std::endl;
	return normalized;
}

// Plots one point to screen
void Graph2D::PlotPoint(double x, double y)
{
	vec2f n = this->NormalizeCoordinate(x, y);
	this->PlotNormalized(n.x, n.y);
}

void Graph2D::DrawLine(vec2f p1, vec2f p2, olc::Pixel px, uint32_t pattern)
{
	vec2f p1_n = this->NormalizeCoordinate(p1.x, p1.y);
	vec2f p2_n = this->NormalizeCoordinate(p2.x, p2.y);
	vec2 screen_p1 = this->ScreenPosFromNormalized(p1_n.x, p1_n.y);
	vec2 screen_p2 = this->ScreenPosFromNormalized(p2_n.x, p2_n.y);
	this->app->DrawLine(screen_p1, screen_p2, px, pattern);
}

void Graph2D::PlotGridLines()
{
	if (this->delta_x != 0 && this->delta_y != 0)
	{
		// delta_x basically describes the distance between the grid lines
		// We begin plotting from the center of the screen and move delta_x
		// in either directions to plot the y lines.
		for (int i = 0; i <= n_gridx; i++)
		{
			// Start from the origin, and go to the right most grid line to plot
			// And move towards the origin.
			double xp = this->origin_x - ((n_gridx / 2) - i) * delta_x;
			this->DrawLine(vec2f(xp, grid_start_y), vec2f(xp, grid_end_y), olc::DARK_GREY, '....');
		}

		for (int i = 0; i <= n_gridy; i++)
		{
			double yp = this->origin_y - ((n_gridy / 2) - i) * delta_y;
			this->DrawLine(vec2f(grid_start_x, yp), vec2f(grid_end_x, yp), olc::DARK_GREY, '....');
		}
	}

/*
	TODO: Make this customizable. Number of labels on graph is hard coded for now.
*/
	// Draw the labels on Y axis
	int number_of_labels = 5;
	// First we find the starting point to draw
	// This will be top left of the graph
	vec2f text_start = this->position;
	for (int i = 0; i < number_of_labels; i++)
	{
		// Now we add height per label (this.dimensions.y / number_of_labels)
		vec2f final_text_loc = text_start + vec2f(0, i * this->dimensions.y / number_of_labels);
		// Calculate the current value at y position
		double label_value = this->grid_end_y + (i) * (this->grid_start_y - this->grid_end_y) / number_of_labels;
		// Draw the string
		this->app->DrawString(final_text_loc, std::to_string(label_value), olc::GREEN);
	}

}

void Graph2D::PlotAxes()
{
	// Draw x-axis (y=0)
	this->DrawLine(vec2f(grid_start_x, 0), vec2f(grid_end_x, 0), olc::BLUE, '____');
	// Draw y-axis (x=0)
	this->DrawLine(vec2f(0, grid_start_y), vec2f(0, grid_end_y), olc::RED, '____');
}
// Plot vector data to screen
void Graph2D::Plot(std::vector<double> x, std::vector<double> y)
{
	// Clear
	this->Clear();
	// Plot grid lines
	this->PlotGridLines();
	// Plot axis
	this->PlotAxes();
	if (x.size() != y.size())
	{
		return;
	}

	for (int i = 0; i < x.size() - 1; i++)
	{
		this->DrawLine(vec2f(x[i], y[i]), vec2f(x[i + 1], y[i + 1]));
	}

	this->app->DrawString(this->position - vec2(0, GRAPH_BORDER_SIZE + this->app->GetTextSize("A").y) , this->caption, olc::RED);
}
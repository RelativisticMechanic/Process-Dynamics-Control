#include "RungeKutta4.h"

/*
	ALGORITHM:

	Given some y, t, to calculate y at t + dt

	k1 = f(y,t)
	k2 = f(y+k1*dt*0.5, t + dt*0.5)
	k3 = f(y+k2*dt*0.5, t + dt*0.5)
	k4 = f(y+k3*dt, t + dt)

	y_new = y + (dt/6)*(k1 + 2*k2 + 2*k3 + k4)
*/
std::vector<double> RungeKutta4_Iteration(RK4_FUNC f, std::vector<double> y_prev, double t, double delta_t, std::vector<double> arg_list)
{
	int n = y_prev.size();
	std::vector<double> y_next = std::vector<double>(n);

	std::vector<double> k1 = f(y_prev, t, arg_list);
	for (int i = 0; i < n; i++)
	{
		y_next[i] = y_prev[i] + delta_t * (k1[i] * 0.5);
	}

	std::vector<double> k2 = f(y_next, t + (delta_t) * 0.5, arg_list);

	for (int i = 0; i < n; i++)
	{
		y_next[i] = y_prev[i] + delta_t * (k2[i] * 0.5);
	}
	std::vector<double> k3 = f(y_next, t + (delta_t) * 0.5, arg_list);

	for (int i = 0; i < n; i++)
	{
		y_next[i] = y_prev[i] + delta_t * k3[i];
	}

	std::vector<double> k4 = f(y_next, t + (delta_t), arg_list);

	std::vector<double> result = std::vector<double>(y_prev.size());

	for (int i = 0; i < n; i++)
	{
		result[i] = y_prev[i] + delta_t * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]) / 6.0;
	}

	return result;
}
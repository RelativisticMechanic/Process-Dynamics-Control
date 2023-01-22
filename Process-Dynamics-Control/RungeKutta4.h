#ifndef RUNGE_KUTTA_4
#define RUNGE_KUTTA_4

#include <vector>

typedef std::vector<double> (*RK4_FUNC)(std::vector<double>, double t, std::vector<double> arg_list);

/*
	Solves differential equation of the form:
		dy/dt = f(y, t)
		
		Here both dy/dt and y of t are vectors.
		Returns a vector containing the estimated y values for the time 
		t + delta_t.

	Accepts: 
		A function of the form f(y,t) which returns dy/dt at a given time.
		Both y and dy/dt are vectors, allowing multiple variables as well
		as different order derivatives to be supplied.

	RK4_FUNC has the prototype:
		std::vector<double> rk4_callback(std::vector<double> y, double t)

	Example:
		Solving the spring equation: y'' = -ky
		With initial conditions:
			y = 1.0 at t = 0
			y' = 0 at t = 0
		
		We create a vector of 2 values: [y y']
		The function will return the derivative of this vector: [y' y'']

		std::vector<double> y_prev = std::vector<double>(3)
		
		[](std::vector<double> y, double t) -> std::vector<double>
		{
			std::vector<double> out(2);

			// y'' = -y
			out[1] = -y[0];
			// y' = y' 
			out[0] = y[1];

			return out;
			
		}
		
		Then we call the RK4_FUNC at t = 0 and delta_t = 0.01 
		std::vector<double> result = RungeKutta4I_teration(f, y_prev, 0, 0.01);

		We'll get the values for position and velocity at time t = 0 + 0.01 in result.

		You can iterate this quite a lot of times as follows:

		result = RungeKutta4I_teration(f, y_prev, 0, 0.01)
		for(double t = 0.01; t < 1.0; t += 0.01)
		{
			result = RungeKutta4_Iteration(f, result, t, 0.01);
		}

		We'll get the result at t = 1.0s

		Remember, the smaller the delta_t value, the more accurate will be your result. For some problems
		with large constants, smaller delta_t is NECESSARY FOR CONVERGENCE, otherwise your solution
		will explode!

*/
std::vector<double> RungeKutta4_Iteration(RK4_FUNC f, std::vector<double> y_prev, double t, double delta_t, std::vector<double> arg_list);

#endif
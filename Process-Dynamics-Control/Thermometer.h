/*
	Describes a simple thermometer 
*/

#include <iostream>
#include <vector>
#include "RungeKutta4.h"

class Thermometer
{
public:
	// Thermomemter variables 
	double time_constant;
	double temperature;

	Thermometer() { };
	Thermometer(double time_constant, double temperature)
	{
		this->time_constant = time_constant;
		this->temperature = temperature;
	}

	static std::vector<double> Thermometer_Function(std::vector<double> y, double t, std::vector<double> arg_list)
	{
		// Arg_List[0] = New Temperature (from input)
		// Arg_List[1] = Time Constant
		std::vector<double> dydt = std::vector<double>(1);

		// A simple thermometer is described by the differential equation:
		// dy/dt = (X - Y) / T
		dydt[0] = (arg_list[0] - y[0]) / arg_list[1];
		return dydt;
	}
	void Update(double new_temperature, double delta_time)
	{
		std::vector<double> y_prev = std::vector<double>(1);
		std::vector<double> arg_list = std::vector<double>(2);

		arg_list[0] = new_temperature;
		arg_list[1] = this->time_constant;
		y_prev[0] = this->temperature;

		// Solve the differential equation using RK4.
		std::vector<double> y = RungeKutta4_Iteration(Thermometer_Function, y_prev, 0.0f, delta_time, arg_list);
		this->temperature = y[0];
	}

};
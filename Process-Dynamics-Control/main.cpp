#include <iostream>
#include <cmath>

#include "olcPixelGameEngine.h"
#include "drawArc.h"
#include "TimePlot.h"
#include "RungeKutta4.h"
#include "ThermometerApp.cpp"


int main(int argc, char** argv)
{
	ThermometerApp thermometer_demo;

	const std::vector<std::string> SIMULATIONS_LIST = { "Thermometer" };
	const std::vector<olc::PixelGameEngine*> SIMULATIONS = { &thermometer_demo };

	std::cout << "Welcome to Process Dynamics and Control Simulations! Choose your simulation to run:" << std::endl;

	for (int i = 0; i < SIMULATIONS_LIST.size(); i++)
	{
		std::cout <<  i + 1 << "] " << SIMULATIONS_LIST[i] << std::endl;
	}

	std::cout << "Choose which simulation to run: ";
	int a = 0;
	std::cin >> a;

	if (a - 1 >= SIMULATIONS_LIST.size() || a - 1 < 0)
	{
		std::cout << "No such simulation exists. Quitting." << std::endl;
		return 0;
	}
	else
	{
		if (SIMULATIONS[a - 1]->Construct(800, 600, 1, 1))
			SIMULATIONS[a - 1]->Start();
	}
	return 0;
}
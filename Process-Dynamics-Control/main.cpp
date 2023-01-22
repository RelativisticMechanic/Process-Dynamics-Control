#include <iostream>
#include <cmath>

#include "olcPixelGameEngine.h"
#include "TimePlot.h"
#include "RungeKutta4.h"
#include "Thermometer.h"

class myApp : public olc::PixelGameEngine
{
public:
	TimePlot thermometer_out;
	TimePlot fluid_temperature;
	Thermometer myThermometer;

	// Default temperature of 310K
	double default_temperature = 310;
	// Amplitude of the sinusoidal input be 10 K
	double sinusoidal_amplitude = 10;

	// Some variables to track time
	float s = 0;
	int n = 0;
	myApp()
	{
		sAppName = "Process Dynamics and Control";
	}

	bool OnUserCreate() override
	{
		fluid_temperature = TimePlot(this, vec2(100, 50), vec2(400, 200), "Fluid Temperature", 300, 320, 60);
		thermometer_out = TimePlot(this, vec2(100, 300), vec2(400, 200), "Thermometer", 300, 320, 60);
		myThermometer = Thermometer(1.0, 310);
		return true;
	}

	bool OnUserUpdate(float elapsed) override
	{
		Clear(olc::BLACK);
		DrawString(vec2(0, 0), "Press LMB to stop sinusoidal input", olc::WHITE, 2.0);
		if (s > 0.1*n)
		{
			thermometer_out.PushData(s, myThermometer.temperature);
			// If mouse button is held stop sinusoidal input
			if (GetMouse(0).bHeld)
			{
				fluid_temperature.PushData(s, default_temperature);
				myThermometer.Update(default_temperature, 0.1);
			}
			// If mouse button is released continue sinusoidal input
			else
			{
				fluid_temperature.PushData(s, default_temperature + sinusoidal_amplitude * sin(s));
				myThermometer.Update(default_temperature + sinusoidal_amplitude * sin(s), 0.1);
			}
			
			n += 1;
		}

		s += elapsed;
		fluid_temperature.Plot();
		thermometer_out.Plot();
		return true;
	}
};

int main(void)
{
	myApp demo;
	if (demo.Construct(800, 600, 1, 1))
		demo.Start();

	return 0;
}
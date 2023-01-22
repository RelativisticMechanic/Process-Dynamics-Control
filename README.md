<img src="https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/working-thermometer.gif" alt="Thermometer Implementation" width="600"/>

# Process Dynamics Control

This is a C++ application that implements a way to simulate and show process dynamics in C++. It was created in the January of 2023 by me as a way to understand the course [CH3310 (Process Dynamics and Control)](https://website.nitrkl.ac.in/Academics/AcademicDepartments/SyllabiDetails.aspx?d=Q0g6Q2hlbWljYWwgRW5naW5lZXJpbmc=-dmhpvpMkqIU=&di=Ng==-dYSTlPCIpzE=&c=Q2hlbWljYWwgRW5naW5lZXJpbmcgKEIuVGVjaC4gLSA0eXJzKQ==-Qpv4BN16nww=&t=VUc=-/CGGPdtU1IU=&s=NjgwNg%3d%3d-cO7ZMP8ekjo%3d).

Currently, it implements a _Thermometer_ class, which can respond to temperature input and set its temperature accordingly. More will be described in the section below.

## Part I: The Problem

When it comes to thermometers, in most of high school, we generally assume that the thermometer reports the correct reading of the fluid. That is, if the fluid temperature were to increase from 310 K to 320 K, a mercury thermometer would also go from 310 K to 320 K with the fluid. This is how it ideally should be, but it **isn't**!

Why? Because the thermometer itself is made up of mercury, which will take its own sweet time to heat up, and then it will expand in the tube, giving us the required reading. Therefore, our thermometer output will *lag* by the actual fluid temperature.

### Describing it mathematically

Let us consider a steady state system where both the fluid temperature and the temperature shown by the thermometer is $T_0$. At $t = 0$, the temperature of the fluid becomes $T_1$, and we no longer operate at steady state.

We have the heat transfer equation,

$$ \frac{dQ}{dt} = hA(T_1 - T) $$

This describes a fluid at temperature $T_1$ transfering heat to an object at temperature $T$, here: $A$ is the area of contact between the thermometer at the fluid (this would be the area of the outer cylinder) and $h$ is called the _convective heat transfer coefficient_, which is different for different liquids. 

Recall from high school physics that if the rate of heat transfer is $\frac{dQ}{dt}$, and the rate of temperature change be $\frac{dT}{dt}$, then these are correlated with the equation 

$$ \frac{dQ}{dt} = m C_p \frac{dT}{dt} $$

We equate the two equations,

$$ hA(T_1 - T) = m C_p \frac{dT}{dt} $$

$$ (T_1 - T) = \frac{m C_p}{hA} \frac{dT}{dt} $$

We define the constant $\frac{m C_p}{hA} = \tau$. This $\tau$ is referred to as the _time constant_ of the thermometer.

$$ (T_1 - T) = \tau \frac{dT}{dt} $$

We thus have the differential equation:

$$ \frac{dT}{dt} = \frac{T_1 - T}{\tau}$$

$T_1$ needn't be constant here, it could vary as well with time. In the program in fact, the fluid temperature $T_1$ varies sinusodially by default.

### Solving the Differential Equation

In a typical classroom scenario, we are usually taught to solve the DEs using analytical methods like _Laplace Transforms_. However, since computer programs cannot perform analytical operations like symbolic integration or inverse laplace transform, we'll solve the DE using the [Runge Kutta Order 4](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods).

You can see my implementation of RK4 in [```RungeKutta4.cpp```](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/Process-Dynamics-Control/RungeKutta4.cpp).

With the differential equation solved, the RK4 function returns the temperature of the thermometer at the next time instant.

## Part II: The Project Structure

The project is made using Visual Studio 2022.

- [```olcPixelGameEngine.h```](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/Process-Dynamics-Control/olcPixelGameEngine.h): This contains [Javidx9's olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine). It is a header only library for C++ that gives us access to a basic OpenGL / WebGL output screen with basic 2D rasterization functions already implemented. I wanted to use my own library for 2D rasterization [engine2D](https://github.com/RelativisticMechanic/engine2D), but engine2D requires SDL as a dependency. I wanted this project to have as minimum of dependencies as possible.

- [```Graph2D.cpp```](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/Process-Dynamics-Control/Graph2D.cpp): This is the Graph2D class. It allows us to render any set of points on screen space given the origin of our data and the span of the data. It functions as essentially a mini matplotlib.

- [```TimePlot.cpp```](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/Process-Dynamics-Control/TimePlot.cpp): This is the TimePlot class. It is implemented over the Graph2D class and allows us to visualize some variable $x$ as a function in time. It functions as a stack. Newer values can be pushed last and older values are discarded.

- [```RungeKutta4.cpp```](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/Process-Dynamics-Control/RungeKutta4.cpp): The Runge-Kutta 4 Differential Equation Solver.

- [```Thermometer.h```](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/Process-Dynamics-Control/Thermometer.h): An implementation of a simple thermometer described above.

- [```main.cpp```](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/Process-Dynamics-Control/main.cpp): The main file of the application.

Here's a nice visualization of how the program's mainloop functions, as a Chemical Engineering, a process flow diagram is perhaps the most fun thing to make:

![Program Process Flow Diagram](https://github.com/RelativisticMechanic/Process-Dynamics-Control/blob/main/pdc-program-pfd.png)

## Part III: Extending the project further

This project can be extended a lot further. One could easily incorporate other kinds of systems into it, as both the TimePlot class and the RungeKutta4 differential equation solver are highly extendable. As I progress through this course, I shall add more systems other than just the Thermometer implementation.

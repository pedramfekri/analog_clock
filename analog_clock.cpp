#pragma comment(lib, "User32.lib")
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <Windows.h>

#include "2D_graphics.h"
#include "DrawClock.h"

#include "timer.h"

using  namespace std;

int main()
{
	settings clock_set;
	int n = 2, id = 0;
	static double width = 800, height = 600, r, g, b, scale, xp, yp, value;
	r = 1.0;
	g = 0.0;
	b = 0.0;
	char str[1000] = "text";
	double t, t0;
	static double px, py, radius, ang;
	double x[2];
	double y[2];

	double clx[12];
	double cly[12];
	

	double status[3][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0} };
	
	clock_set.cx = width / 2.0;

	clock_set.cy = height / 2.0;


	initialize(clock_set, status);


	initialize_graphics();

	double deg = 0;
	

	t0 = high_resolution_time();

	draw_clock(clx, cly, clock_set.cx, clock_set.cy, 12);

	update();
	
	while (1) {
		clear();

		draw_clock(clx, cly, clock_set.cx, clock_set.cy, 12);
		counter(clock_set, status);
		digital_clock(status[2][3], status[1][3], status[0][3], clock_set);

		update();
		
		Sleep(1000);

	}


}


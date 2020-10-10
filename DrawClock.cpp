#include "DrawClock.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <Windows.h>

#include "2D_graphics.h"

#include "timer.h"

using  namespace std;

void draw_indices(double& cx, double& cy, double& px, double& py, double& r, double& ang) {
	px = cx - (r * cos(ang));
	py = cy - (r * sin(ang));
}

double deg2rad(double deg) {
	double pi = 3.14159265359;

	return deg * (pi / 180.0);
}

void draw_clock(double* x, double* y, double& cx, double& cy, int num) {
	const int numbers[12] = { 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8};
	double bradius = 100;
	double sradius = 80;
	double tradius = bradius + 20;
	double step = 360.0 / 12.0;
	double deg = 0, ang;
	double pbx, pby;
	double psx, psy;
	double tx, ty;
	double dx[2], dy[2];
	double r, g, b;

	r = 1.0;
	g = 1.0;
	b = 0.0;
	ang = deg2rad(deg);
	for (int i = 0; i < num; i++){
		draw_indices(cx, cy, pbx, pby, bradius, ang);
		draw_indices(cx, cy, psx, psy, sradius, ang);
		draw_indices(cx, cy, tx, ty, tradius, ang);
		dx[0] = pbx;
		dx[1] = psx;
		dy[0] = pby;
		dy[1] = psy;
		line(dx, dy, 2, r, g, b);
		//text(numbers[i], tx, ty, 0.3);
		
		deg -= step;
		ang = deg2rad(deg);

	}

}

void counter(settings &set, double status[][4]) {
	//       x   y   deg   counter
	// sec  ..  ..   ..    ..
	// min  ..  ..   ..    ..
	// hr   ..  ..   ..    ..
	double step = 360.0 / 60.0;
	double deg = 0, ang;
	double cpoint = 60;
	double dx[2], dy[2];

	step = deg2rad(step);
	
	cout << status[0][2] << "\n";
	
	status[0][2] -= step;
	draw_indices(set.cx, set.cy, status[0][0], status[0][1], set.radius_sec, status[0][2]);
	status[1][2] -= (step / 60.0);
	draw_indices(set.cx, set.cy, status[1][0], status[1][1], set.radius_min, status[1][2]);
	status[2][2] -= ((step * 5) / (60.0 * 60.0));
	draw_indices(set.cx, set.cy, status[2][0], status[2][1], set.radius_hr, status[2][2]);

	status[0][3] += 1;
	if (status[0][3] >= cpoint) {
		status[0][3] = 0;
		status[1][3] += 1;

		if (status[1][3] >= cpoint) {
			status[1][3] = 0;
			status[2][3] += 1;
			
			if (status[2][3] >= 12)
				status[2][3] = 1;
		}
	}

	dx[0] = status[0][0];
	dx[1] = set.cx;
	dy[0] = status[0][1];
	dy[1] = set.cy;
	line(dx, dy, 2, set.rs, set.gs, set.bs);

	dx[0] = status[1][0];
	dx[1] = set.cx;
	dy[0] = status[1][1];
	dy[1] = set.cy;
	line(dx, dy, 2, set.rm, set.gm, set.bm);

	dx[0] = status[2][0];
	dx[1] = set.cx;
	dy[0] = status[2][1];
	dy[1] = set.cy;
	line(dx, dy, 2, set.rh, set.gh, set.bh);


	
}

void initialize(settings &set, double status[][4]) {
//       x   y   deg   counter
// sec  ..  ..   ..    ..
// min  ..  ..   ..    ..
// hr   ..  ..   ..    ..
	double step = 360.0 / 60.0;
	step = deg2rad(step);
	set.radius_sec = 90;
	set.radius_min = 80;
	set.radius_hr = 70;

	set.rs = 1; 
	set.gs = 0; 
	set.bs = 0;

	set.rm = 1; 
	set.gm = 1; 
	set.bm = 1; 

	set.rh = 0;
	set.gh = 0;
	set.bh = 1;

	set.sec = 0;
	set.min = 0;
	set.hour = 12;

	status[0][3] = set.sec;
	status[1][3] = set.min;
	status[2][3] = set.hour;

	status[0][2] = deg2rad(-90.0 - (6.0 * set.sec));
	status[1][2] = deg2rad(-90.0 - (6.0 * set.min) - ((6.0 * set.sec) / 60));
	status[2][2] = deg2rad(-90.0 - (6.0 * set.hour * 5.0) - ((30.0 * set.min) / 60.0));

	cout << status[0][2] << "\n";
	cout << status[1][2] << "\n";
	cout << status[2][2] << "\n";
	draw_indices(set.cx, set.cy, status[0][0], status[0][1], set.radius_sec, status[0][2]);
	draw_indices(set.cx, set.cy, status[1][0], status[1][1], set.radius_min, status[1][2]);
	draw_indices(set.cx, set.cy, status[2][0], status[2][1], set.radius_hr, status[2][2]);

}


void digital_clock(double h, double m, double s, settings &set) {
	string hs = to_string((int)h);
	char hc[10];
	strcpy_s(hc, hs.c_str());

	string ms = to_string((int)m);
	char mc[10];
	strcpy_s(mc, ms.c_str());

	string ss = to_string((int)s);
	char sc[10];
	strcpy_s(sc, ss.c_str());

	char col[10] = { ":" };

	text(hc, set.cx - 50, set.cy / 5, 0.3);
	text(col, set.cx - 30, set.cy / 5, 0.3);
	text(mc, set.cx - 10, set.cy / 5, 0.3);
	text(col, set.cx + 10, set.cy / 5, 0.3);
	text(sc, set.cx + 30, set.cy / 5, 0.3);
}


#pragma once
struct settings {
	double sec;
	double min;
	double hour;
	double cx;
	double cy;
	double rs, gs, bs, rm, gm, bm, rh, gh, bh;
	double radius_sec;
	double radius_min;
	double radius_hr;

};

void draw_indices(double& cx, double& cy, double& px, double& py, double& r, double& ang);
double deg2rad(double deg);
void draw_clock(double* x, double* y, double& cx, double& cy, int num);
void counter(settings &set, double status[][4]);
void initialize(settings &set, double status[][4]);
void digital_clock(double h, double m, double s, settings& set);
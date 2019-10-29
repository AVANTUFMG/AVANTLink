#ifndef GLOBAL_FUNCTIONS_H_INCLUDED
#define GLOBAL_FUNCTIONS_H_INCLUDED

#include "Class_Point.h"
#include "Class_Malha.h"
#include "Class_Obstacle.h"

using namespace std;

double D_to_RAD(double D_x);
double DELTA(double start, double destiny);
double distance_two_points(double lat1, double lat2, double delta_lon, double delta_lat);
double distance_between_two_points(double D_lat, double D_lon, double height, double D_lat_destiny, double D_lon_destiny, double height_destiny);
Malha transf(double lat, double lon, double h);
void gen_rand_obs(Malha& m, int qt);
void add_obs (Malha &M, obstacle &O);
double dist_2pts(const Point &P1,const Point &P2);
int acha_posicao(vector <Point> d, vector <Point> m);
int pega_pos(vector <Point> &m, int p);

#endif // GLOBAL_FUNCTIONS_H_INCLUDED

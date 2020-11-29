#ifndef CLASS_POINT_H_INCLUDED
#define CLASS_POINT_H_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <stdlib.h>
#define pi 3.14159
#define EARTH_R 6378137

using namespace std;

class Point
{
    private:
        double latitude;
        double longitude;
        double height;

        int fechado = 0;//bool
        int pto_ant = 0;
        double peso = 99999;
        double real_dist = 99999;

        double x, y, z;

        int obs;//bool

    public:


        //constructors
	Point() {};
        Point(double lat, double lon, double h) : latitude(lat), longitude(lon), height(h){obs = 0;}
        Point(double lat, double lon, double h, double i, double j, double k) : latitude(lat), longitude(lon), height(h), x(i), y(j), z(k){obs = 0;}
        Point(double lat, double lon) : latitude(lat), longitude(lon){obs = 0;}

        //setters
        void set_point(double lat, double lon, double h){latitude = lat; longitude = lon; height = h;}
        void set_x(double aux){x = aux;}
        void set_y(double aux){y = aux;}
        void set_z(double aux){z = aux;}
        void set_fechado(){fechado = 1;}//fazer set aberto ?
        void set_ponto(int pto){pto_ant = pto;}//set_ponto_ant
        void set_peso(double weight){peso = weight;}
        void set_obs_true(){obs = 1;}
        void set_obs_false(){obs = 0;}
        void set_real_dist(double r_d){real_dist = r_d;}

        //getters
        double get_latitude()const {return latitude;}
        double get_longitude()const {return longitude;}
        double get_height()const {return height;}
        double get_x() const{return x;}
        double get_y() const {return y;}
        double get_z() const {return z;}
        double get_peso() const {return peso;}
        double get_real_dist() const {return real_dist;}
        int get_pto_ant(){return pto_ant;}
        int get_fechado(){return fechado;}
        int get_obs() {return obs;}

        //functions
        double distance_from(Point &P);
        double distance_from(double Dlat, double Dlon, double DH);

        //prints
        void print_point(){cout.precision(10); cout<< "X: "<< x <<", lat: " << latitude <<" | Y: "<< y<<", lon: "<<longitude << " | Z: "<<z <<", height: "<<height <<" | Obs: "<< obs<<endl;}
        void print_point_xyz(){cout<< "X: "<< x <<" | Y: "<< y << " | Z: "<< z <<endl;}

        //operators overload
        bool operator < (const Point& p) const {return peso < p.peso;}

};

#endif // CLASS_POINT_H_INCLUDED

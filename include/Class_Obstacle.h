#ifndef CLASS_OBSTACLE_H_INCLUDED
#define CLASS_OBSTACLE_H_INCLUDED

#include "Class_Point.h"

using namespace std;

class obstacle{
    private:
        double height;
        double radius;
        double obs_lat;
        double obs_lon;

        //iniciais e finais
        double lat_i = obs_lat - radius*(1.0/111139);
        double lat_f = obs_lat + radius*(1.0/111139);
        double lon_i = obs_lon - radius*(1.0/111139);
        double lon_f = obs_lon + radius*(1.0/111139);


    public:
        //constructor
        obstacle(double lat, double lon, double h, double r): obs_lat(lat), obs_lon(lon), height(h), radius(r){}

        //functions --none so far

        //getters
        double get_obs_lat(){return obs_lat;}
        double get_obs_lon(){return obs_lon;}
        double get_obs_height(){return height;}
        double get_radius(){return radius;}

        //print
        void print_obs(){cout<< "H: " << height << ", R: " << radius << ", Lat: " << obs_lat << ", Lon: " << obs_lon<<endl;}
        void print_obs_limit(){cout<< "H: " << height << ", Lat: "<< lat_i << ", " << lat_f<< ", Lon: "<< lon_i << ", " << lon_f << endl;}

        //sobrecarga de operadores
        obstacle& operator= (const obstacle& o);

};

#endif // CLASS_OBSTACLE_H_INCLUDED

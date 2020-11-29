#ifndef CLASS_MALHA_H_INCLUDED
#define CLASS_MALHA_H_INCLUDED

#include "Class_Point.h"

using namespace std;

class Malha{
    private:
        //vector <Point> malha;
        int N_Points;
        int N_lat;
        int N_lon;
        int N_H;
    public:
        //Variable public bc it's easier
        vector <Point> malha;

        //Constructors:
        Malha(Point &P, int nlat = 12, int nlon = 12, int nh = 6);
        //Malha(double la, double lo, double he); -- Nao precisei
        //Malha(double la, double lo); --Nao precisei

        //getters
        vector <Point> get_malha(){return malha;}
        int get_N_lat(){return N_lat;}
        int get_N_lon(){return N_lon;}
        int get_N_H(){return N_H;}
        int get_N_Points(){return N_Points;}

        //void add_point(); -- nao precisei

        //Prints
        void print_malha(); //prints lat lon h and x y z from every point
        void print_malha_xyz(); //print just x y z from every point
        void print_point_malha_xyz(int i){malha[i].print_point_xyz();} //print just x, y and z about a specific point from malha
        void print_point_malha(int i){cout.precision(9); malha[i].print_point();} //print just info about a specific point from malha
};

#endif // CLASS_MALHA_H_INCLUDED

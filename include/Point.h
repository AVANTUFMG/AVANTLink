#ifndef Point_H
#define Point_H

#include <iostream>
#include <cmath>
#include <vector>
#define pi 3.14159
#define EARTH_R 6378137

//recives latitude,longitude,heigh
//INTERESSANTE FAZER CONSTRUTOR COPIA E DESTRUTOR PARA A MALHA E TALVEZ SOBRECARREGAR =


//double transf(double lat, double lon, double h, double r, double lat_o, double lon_o); -- teste apenas ignorar
//Malha transf(double lat, double lon, double h); -- teste apenas ignorar

//functions used to calculate distance between two points (colocar tudo dentro da classe pontos?? Acho que nao)
double D_to_RAD(double D_x); //degrees to radians
double DELTA(double start, double destiny);//DELTA (start - destiny)
double distance_two_points(double lat1, double lat2, double delta_lon, double delta_lat); //distance between two points in KM (needs deltas, in radians)
double distance_between_two_points(double D_lat, double D_lon, double D_lat_destiny, double D_lon_destiny); //distance between two lat/lon points (in deegres, principal function)

using namespace std;
class Point
{
    private:
        double latitude;
        double longitude;
        double height;

        //talvez x,y,z virem int
        double x, y, z;

        //is obstacle?
        int obs; //POSSO FAZER UM BOOL

    public:
        //constructors
        Point(double lat, double lon, double h) : latitude(lat), longitude(lon), height(h){obs = 0;}
        Point(double lat, double lon, double h, double i, double j, double k) : latitude(lat), longitude(lon), height(h), x(i), y(j), z(k){obs = 0;}
        Point(double lat, double lon) : latitude(lat), longitude(lon){obs = 0;}

        //setters
        void set_point(double lat, double lon, double h){latitude = lat; longitude = lon; height = h;}
        void set_x(double aux){x = aux;}
        void set_y(double aux){y = aux;}
        void set_z(double aux){z = aux;}
        void set_obs_true(){obs = 1;}
        void set_obs_false(){obs = 0;}

        //getters
        double get_latitude()const {return latitude;}
        double get_longitude()const {return longitude;}
        double get_height()const {return height;}
        double get_x() const{return x;}
        double get_y() const {return y;}
        double get_z() const {return z;}
        int get_obs() {return obs;}

        //functions
        double distance_from(Point &P);
        double distance_from(double Dlat, double Dlon);

        //prints
        void print_point(){cout.precision(10); cout<< "X: "<< x <<", lat: " << latitude <<" | Y: "<< y<<", lon: "<<longitude << " | Z: "<<z <<", height: "<<height <<endl;}
        void print_point_xyz(){cout<< "X: "<< x <<" | Y: "<< y << " | Z: "<< z <<endl;}


};

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
        Malha(Point &P);
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

class obstacle{
    private:
        double height;
        double radius;
        double obs_lat;
        double obs_lon;

    public:
        //constructor
        obstacle(double lat, double lon, double h, double r): obs_lat(lat), obs_lon(lon), height(h), radius(r){}

        //functions --none so far

        //getters
        double get_obs_lat(){return obs_lat;}
        double get_obs_lon(){return obs_lon;}
        double get_obs_height(){return height;}
        double get_radius(){return radius;}

};

//talvez essa funcao seja excluida e coloque o que ela faz no pathfinding.h ja que e pouca coisa
Malha transf(double lat, double lon, double h); //seila pq q botei a funcao no final aqui tinha motivo mas nao lembro
void add_obs (Malha &M, obstacle &O); //add a obstacle *PRECISA DE MAIS TESTES*

#endif // Point_H

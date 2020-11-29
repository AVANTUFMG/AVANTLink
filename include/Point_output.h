#ifndef Point_output_H
#define Point_output_H

#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <stdlib.h>
#define pi 3.14159
#define EARTH_R 6378137

//recives latitude,longitude,heigh
//INTERESSANTE FAZER CONSTRUTOR COPIA E DESTRUTOR PARA A MALHA E TALVEZ SOBRECARREGAR =


//double transf(double lat, double lon, double h, double r, double lat_o, double lon_o); -- teste apenas ignorar
//Malha_O transf(double lat, double lon, double h); -- teste apenas ignorar

//functions used to calculate distance between two Point_Os (colocar tudo dentro da classe pontos?? Acho que nao)
double D_to_RAD_O(double D_x); //degrees to radians
double DELTA_O(double start, double destiny);//DELTA (start - destiny)
double distance_two_Point_Os(double lat1, double lat2, double delta_lon, double delta_lat); //distance between two Point_Os in KM (needs deltas, in radians)
double distance_between_two_Point_Os(double D_lat, double D_lon, double D_lat_destiny, double D_lon_destiny); //distance between two lat/lon Point_Os (in deegres, principal function)

using namespace std;
class Point_O
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
        Point_O(double lat, double lon, double h) : latitude(lat), longitude(lon), height(h){obs = 0;}
        Point_O(double lat, double lon, double h, double i, double j, double k) : latitude(lat), longitude(lon), height(h), x(i), y(j), z(k){obs = 0;}
        Point_O(double lat, double lon) : latitude(lat), longitude(lon){obs = 0;}

        //setters
        void set_Point_O(double lat, double lon, double h){latitude = lat; longitude = lon; height = h;}
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
        double distance_from(Point_O &P);
        double distance_from(double Dlat, double Dlon, double DH);

        //prints
        void print_Point_O(){cout.precision(10); cout<< "X: "<< x <<", lat: " << latitude <<" | Y: "<< y<<", lon: "<<longitude << " | Z: "<<z <<", height: "<<height <<" | Obs: "<< obs<<endl;}
        void print_Point_O_xyz(){cout<< "X: "<< x <<" | Y: "<< y << " | Z: "<< z <<endl;}
        void print_Point_O_xy(){cout<< "X: "<< x <<" | Y: "<< y <<endl;}


};

class Malha_O{
    private:
        //vector <Point_O> malha;
        int N_Point_Os;
        int N_lat;
        int N_lon;
        int N_H;
    public:
        //Variable public bc it's easier
        vector <Point_O> malha;

        //Constructors:
        Malha_O(Point_O &P, int nlat = 12, int nlon = 12, int nh = 6);
        //Malha(double la, double lo, double he); -- Nao precisei
        //Malha(double la, double lo); --Nao precisei

        //getters
        vector <Point_O> get_malha(){return malha;}
        int get_N_lat(){return N_lat;}
        int get_N_lon(){return N_lon;}
        int get_N_H(){return N_H;}
        int get_N_Point_Os(){return N_Point_Os;}

        //void add_Point_O(); -- nao precisei

        //Prints
        void print_malha(); //prints lat lon h and x y z from every Point_O
        void print_malha_xyz(); //print just x y z from every Point_O
        void print_Point_O_malha_xyz(int i){malha[i].print_Point_O_xyz();} //print just x, y and z about a specific Point_O from malha
        void print_Point_O_malha(int i){cout.precision(9); malha[i].print_Point_O();} //print just info about a specific Point_O from malha
};

class obstacle_o{
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
        obstacle_o(double lat, double lon, double h, double r): obs_lat(lat), obs_lon(lon), height(h), radius(r){}

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
        obstacle_o& operator= (const obstacle_o& o);

};

//talvez essa funcao seja excluida e coloque o que ela faz no pathfinding.h ja que e pouca coisa
Malha_O transf_O(double lat, double lon, double h); //seila pq q botei a funcao no final aqui tinha motivo mas nao lembro
void gen_rand_obs_O(Malha_O& m, int qt); //gerador de obstáculos
void add_obs_O (Malha_O &M, obstacle_o &O); //add a obstacle

#endif // Point_O_H

#include "Point_output.h"

using namespace std;

//Malha_O--------------------------------------------------------------
Malha_O::Malha_O(Point_O &P, int nlat, int nlon, int nh){
    //VANT in (x,y,z) = (0,0,0)
    int c = 0; //counter
    N_lat = 40;
    N_lon = 40;
    N_H = 4;

    P.set_x(0);
    P.set_y(0);
    P.set_z(0);

    for(int k = -N_H; k<= N_H; k++){
        for(int j = -N_lon; j<=N_lon; j++){
            for(int i = -N_lat; i<=N_lat;i++){
                Point_O aux(P.get_latitude() + (i*0.000135),P.get_longitude() + (j*0.000135), P.get_height() + 15*k);
                aux.set_x(i*15);
                aux.set_y(j*15);
                aux.set_z(k*15);
                c = c+1;
                malha.push_back(aux);
            }
        }
    }
    N_Point_Os = c;
}

void Malha_O::print_malha(){
    for(int i = 0; i<malha.size();i++){
        cout.precision(9);
        print_Point_O_malha(i);
        cout<<endl;
    }
}

void Malha_O::print_malha_xyz(){
    for(int i = 0; i<malha.size();i++){
        print_Point_O_malha_xyz(i);
        cout<<endl;
    }
}


//Functions--------------------------------------------------------------------------
 double D_to_RAD_O(double D_x){
        double R_x;
        R_x = D_x*(pi/180);
        return(R_x);
    }

double DELTA_O(double start, double destiny){
        double delta;
        delta = start - destiny;
        delta = sqrt(pow(delta,2));
        return (delta);
    }

double distance_two_Point_Os(double lat1, double lat2, double delta_lon, double delta_lat, double radius){
        double a, b, dist;

        a = (pow(sin((delta_lat/2)),2)) + cos(lat1)*(cos(lat2))*(pow(sin((delta_lon/2)), 2));
        b = 2 * (atan2(sqrt(a), sqrt(1-a)));
        dist = radius*b;
        return (dist);
    }

double distance_between_two_Point_Os(double D_lat, double D_lon, double height, double D_lat_destiny, double D_lon_destiny, double height_destiny){

        double R_lat, R_lon, R_lat_destiny, R_lon_destiny, delta_lat, delta_lon, delta_h, distance, R_polar, R_equat, e, R;


        //transforming all degrees to radians
        R_lon = D_to_RAD_O(D_lon);
        R_lat = D_to_RAD_O(D_lat);
        R_lat_destiny = D_to_RAD_O(D_lat_destiny);
        R_lon_destiny = D_to_RAD_O(D_lon_destiny);

        //calculating delta
        delta_lat = DELTA_O(R_lat, R_lat_destiny);
        delta_lon = DELTA_O(R_lon, R_lon_destiny);
        delta_h = DELTA_O(height, height_destiny);

        //calculating radius
        R = (EARTH_R - (21.385*sin(D_lat)));

        //calculating distance
        distance = distance_two_Point_Os(R_lat, R_lat_destiny, delta_lon, delta_lat, R);
        distance = sqrt(distance*distance+delta_h*delta_h);
        //cout<<distance<<endl;

        return distance;
}

//Point_Os-----------------------------------------------------------
double Point_O::distance_from(Point_O &p){

        return(distance_between_two_Point_Os(this->get_latitude(), this->get_longitude(), this->get_height(),p.get_latitude(), p.get_longitude(), p.get_height()));
}
double Point_O::distance_from(double Dlat, double Dlon, double DH){

        return(distance_between_two_Point_Os(this->get_latitude(), this->get_longitude(), this->get_height(), Dlat, Dlon, DH));
}

//Transform function----------------------------------------------------------------------
//talvez essa funcao seja excluida ja que nao está fazendo mt coisa, colocarei tudo no pathfinding.h
//double transf(double lat, double lon, double h, double r, double lat_o, double lon_o){
Malha_O transf_O(double lat, double lon, double h){

    Point_O P(lat,lon, h);
    Malha_O M(P);

    return M;
}

//obstacles----------------------------------------------------------------------------------


//Sobrecarga de =
obstacle_o& obstacle_o::operator=(const obstacle_o& o){

    height = o.height;

    radius = o.radius;

    obs_lat = o.obs_lat;

    obs_lon = o.obs_lon;

    return *this;

}

void add_obs_O (Malha_O &M, obstacle_o &O){

    cout.precision(10);
    // 1 degree = 111,139 m or 1m = 1/111139 degrees
    double lat_i, lat_f, lon_i, lon_f, division;
    division = 1.0/111139;

    lat_i = O.get_obs_lat() - (O.get_radius()*division);
    lat_f = O.get_obs_lat() + (O.get_radius()*division);
    lon_i = O.get_obs_lon() - (O.get_radius()*division);
    lon_f = O.get_obs_lon() + (O.get_radius()*division);

    for(int i = 0; i<M.malha.size();i++){
        if(M.malha[i].get_latitude() >= lat_i && M.malha[i].get_latitude() <= lat_f ){
                if(M.malha[i].get_longitude() >= lon_i && M.malha[i].get_longitude() <= lon_f){
                    if(M.malha[i].get_height() <= O.get_obs_height()){
                         M.malha[i].set_obs_true();
                    }
                }
            }
        }

}

//gerador de obstáculos
void gen_rand_obs_O(Malha_O& m, int qt){

    double max_lat, max_long, min_lat, min_long;

    int fim;

    fim = m.malha.size()-1;

    min_lat = m.malha[0].get_latitude();
    min_long = m.malha[0].get_longitude();
    max_lat = m.malha[fim].get_latitude();
    max_long = m.malha[fim].get_longitude();

     /*inicializando random seed*/
        srand (time(NULL));

    for(int i = 0; i < qt; i++){
        double o_height, o_radius, o_lat, o_lon;

        double r1, r2, r3, r4;

        /*random height, 30ft to 750ft*/

        r1 = (double)rand()/RAND_MAX; //228.600 9.144;

        o_height = 9.144 + r1*(228.600-9.144);

        //como rand é um int, para fazer a comversão em double

        //foi neceessário o desmenbramento da função em duas equações diferentes

        //min + r*(max - min), onde r é o fator de randomização.

        /*random radius, 30ft to 300ft*/

        r2 = (double)rand()/RAND_MAX; //91.440 9.144;

        o_radius = 9.144 + r2*(91.440-9.144);

        /*random latitude, inside campus*/

        // min_lat -> m.malha[malha.begin()].get_latitude();

        // max_lat -> m.malha[malha.end()].get_latitude();

        r3 = (double)rand()/RAND_MAX; //-19.871675 -19.866909;

        o_lat = (min_lat) +  r3*((max_lat)-(min_lat));

        /*random longitude, inside campus*/

        // min_lon -> m.malha[malha.begin()].get_longitude();

        // max_lon -> m.malha[malha.end()].get_longitude();

        r4 = (double)rand()/RAND_MAX; //-43.965245 -43.959322;

        o_lon = (min_long) + r4*((max_long)-(min_long));

        obstacle_o ran_obs(o_lat, o_lon, o_height, o_radius);//cria objeto
        add_obs_O(m, ran_obs);

        //printando obstaculo:
        //cout<<"-----Sobs-----"<<endl;
        //ran_obs.print_obs();
        //ran_obs.print_obs_limit();
        //cout<<"-----Eobs-----"<<endl;
    }
}

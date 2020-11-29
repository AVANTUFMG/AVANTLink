#include "Global_Functions.h"

using namespace std;

 double D_to_RAD(double D_x){
        double R_x;
        R_x = D_x*(pi/180);
        return(R_x);
    }

double DELTA(double start, double destiny){
        double delta;
        delta = start - destiny;
        delta = sqrt(pow(delta,2));
        return (delta);
    }

double distance_two_points(double lat1, double lat2, double delta_lon, double delta_lat, double radius){
        double a, b, dist;

        a = (pow(sin((delta_lat/2)),2)) + cos(lat1)*(cos(lat2))*(pow(sin((delta_lon/2)), 2));
        b = 2 * (atan2(sqrt(a), sqrt(1-a)));
        dist = radius*b;
        return (dist);
    }

double distance_between_two_points(double D_lat, double D_lon, double height, double D_lat_destiny, double D_lon_destiny, double height_destiny){

        double R_lat, R_lon, R_lat_destiny, R_lon_destiny, delta_lat, delta_lon, delta_h, distance, R_polar, R_equat, e, R;


        //transforming all degrees to radians
        R_lon = D_to_RAD(D_lon);
        R_lat = D_to_RAD(D_lat);
        R_lat_destiny = D_to_RAD(D_lat_destiny);
        R_lon_destiny = D_to_RAD(D_lon_destiny);

        //calculating delta
        delta_lat = DELTA(R_lat, R_lat_destiny);
        delta_lon = DELTA(R_lon, R_lon_destiny);
        delta_h = DELTA(height, height_destiny);

        //calculating radius
        R = (EARTH_R - (21.385*sin(D_lat)));

        //calculating distance
        distance = distance_two_points(R_lat, R_lat_destiny, delta_lon, delta_lat, R);
        distance = sqrt(distance*distance+delta_h*delta_h);
        //cout<<distance<<endl;

        return distance;
}

double dist_2pts(const Point &P1, const Point &P2){
    return distance_between_two_points(P1.get_latitude(), P1.get_longitude(), P1.get_height(), P2.get_latitude(), P2.get_longitude(), P2.get_height());
}

int pega_pos(vector <Point> &m, int p){
    double dist_aux = 9999;
    int pos_aux = 0;
    for(int i = 0; i < m.size(); i++){
        if(m[i].get_fechado() != 1 && ((m[i].get_peso() + m[i].get_real_dist()) < dist_aux)){
            dist_aux = m[i].get_peso() + m[i].get_real_dist();
            pos_aux = i;
        }
    }
    return pos_aux;
}

int acha_posicao(vector <Point> d, const vector <Point> m){
    for(int i = 0; i < d.size(); i++){
        if(d[i].get_fechado() != 1){
            for(int j = 0; j < m.size(); j++){
                if(m[j].get_x() == d[i].get_x() && m[j].get_y() == d[i].get_y() && m[j].get_z() == d[i].get_z()){
                    return j;
                }
            }
        }
    }
}

Malha transf(double lat, double lon, double h){

    Point P(lat,lon, h);
    Malha M(P);

    return M;
}

void add_obs (Malha &M, obstacle &O){

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


//gerador de obstáculos--------------------------------------------------------------------------------
void gen_rand_obs(Malha& m, int qt){

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

        obstacle ran_obs(o_lat, o_lon, o_height, o_radius);//cria objeto
        add_obs(m, ran_obs);

        //printando obstaculo:--------------
        /*
        cout<<"-----Sobs-----"<<endl;
        ran_obs.print_obs();
        ran_obs.print_obs_limit();
        cout<<"-----Eobs-----"<<endl;
        */
    }
}


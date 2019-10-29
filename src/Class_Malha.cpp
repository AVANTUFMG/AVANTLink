#include "Class_Malha.h"

using namespace std;

Malha::Malha(Point &P, int nlat, int nlon, int nh){
    //VANT in (x,y,z) = (0,0,0)
    int c = 0; //counter
    N_lat = 20;
    N_lon = 20;
    N_H = 5;

    P.set_x(0);
    P.set_y(0);
    P.set_z(0);

    for(int k = -N_H; k<= N_H; k++){
        for(int j = -N_lon; j<=N_lon; j++){
            for(int i = -N_lat; i<=N_lat;i++){
                Point aux(P.get_latitude() + (i*0.000135),P.get_longitude() + (j*0.000135), P.get_height() + 15*k);
                aux.set_x(i*15);
                aux.set_y(j*15);
                aux.set_z(k*15);
                c = c+1;
                if(i == -N_lat || i== N_lat || j == -N_lon || j == N_lon || k == -N_H || k == N_H){
                    aux.set_obs_true();
                }
                malha.push_back(aux);
            }
        }
    }
    N_Points = c;
}

void Malha::print_malha(){
    for(int i = 0; i<malha.size();i++){
        cout.precision(9);
        print_point_malha(i);
        cout<<endl;
    }
}

void Malha::print_malha_xyz(){
    for(int i = 0; i<malha.size();i++){
        print_point_malha_xyz(i);
        cout<<endl;
    }
}

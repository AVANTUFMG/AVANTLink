#include "Pathfinding.h"

using namespace std;

vector <Point> pathfinding_Astar(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs){
    //Fazer o construtor e destrutor copia da malha pode ser uma otima ideia

    //Iicializacao dos valores
    Malha M = transf(lat_drone, lon_drone, h_drone);
    Point destiny(lat_dest, lon_dest, h_dest);
    int arrived = 0; //colocar bool
    int pos = -1;
    int pos_aux;
    double dist_pts;
    double distance;
    double distance_aux;
    vector <Point> points_list;
    //vector <Point> dijkstra_list;

    //Colocando obstaculo aleatorio
    gen_rand_obs(M, q_obs);
   // M.malha[3].set_obs_true();
    //M.malha[8].set_obs_true();
    //M.malha[8].print_point();
    //M.malha[13].set_obs_true();
    //M.malha[18].set_obs_true();
    //M.malha[17].set_obs_true();
    //M.malha[16].set_obs_true();
    //Vizinhos sempre são <posicao do vetor> + 1 / <pv> - 1 / <pv> + (2* n_lat +1) / <pv> - (2*n_lat + 1).
    //Drone começa na posicao do vetor (tamanho do vetor)/2 ou seja em x,y,z = 0,0,0.

    do{
        if(pos == -1){
            pos = M.get_malha().size()/2;
            M.malha[pos].set_peso(0); //Define o peso do primeiro ponto como 0.
            distance = dist_2pts(M.malha[pos], destiny);
            M.malha[pos].set_real_dist(distance);
        }
        else{

            //cout << "Ponto sendo olhado: " << endl;
            //M.malha[pos].print_point();
            //cout << endl;

           //cout << "Vizinhos: " << endl;

            //RELAXAMENTO DOS VIZINHOS?
            pos_aux = pos - 1; //ponto "a esquerda do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso(); //esse e o peso certo?
                distance_aux = dist_2pts(M.malha[pos_aux], destiny); //esse auxiliar precisa?
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){ //pq esse realdist?

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + 1; //ponto "a direita do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){
					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);
                }
            }

            pos_aux = pos - (M.get_N_lat()*2 + 1); //ponto "atras do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 1); //ponto "a frente do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2); //ponto "esquerda-atrás do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2 + 2); //ponto "direita-atrás do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2); //ponto "esquerda-frente do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 2); //ponto "direita-frente do drone"
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1); //ponto acima do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1);//ponto acima e frente do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) + 1; //ponto acima e diagonal frente-direita do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) - 1; //ponto acima e diagonal frente-esquerda do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1); //ponto acima e atrás do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) + 1; //ponto acima e giagonal atrás-direita do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) - 1; //ponto acima e diagonal atrás-esquerda do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) + 1; //ponto acima e direita do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos + (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) - 1; //ponto acima e esquerda do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1);//ponto abaixo do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) + 1; //ponto abaixo e direita do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) - 1; //ponto abaixo e esquerda do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1); //ponto abaixo e atrás do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) + 1; //ponto abaixo e atrás-direita do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) - 1; //ponto abaixo e atrás-esquerda do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1); //ponto abaixo e frente do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) + 1; //ponto abaixo e frente-direita do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            pos_aux = pos - (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) - 1; //ponto abaixo e frente-esquerda do drone
            if(pos_aux >= 0 && pos_aux <= M.malha.size() && M.malha[pos_aux].get_fechado() != 1 && M.malha[pos_aux].get_obs() != 1){
                dist_pts = dist_2pts(M.malha[pos], M.malha[pos_aux]) + M.malha[pos].get_peso();
                distance_aux = dist_2pts(M.malha[pos_aux], destiny);
				if((dist_pts + /*M.malha[pos].get_real_dist()*/ distance_aux) < (M.malha[pos_aux].get_peso() + M.malha[pos_aux].get_real_dist())){

                    //M.malha[pos_aux].print_point();

					M.malha[pos_aux].set_peso(dist_pts); //Colocando o peso
					M.malha[pos_aux].set_ponto(pos); //Colocando o ponto. Utilizar o inteiro equivalente na malha.
					M.malha[pos_aux].set_real_dist(distance_aux);				}
            }

            M.malha[pos].set_fechado(); //fechando o ponto

            pos = pega_pos(M.malha, pos); //Agora ele olha só na malha, procurando pelo menor peso e se é fechado ou não

            //cout << "próximo ponto a ser olhado: " << endl;
            //M.malha[pos].print_point();
            //cout << endl;


            //M.malha[pos].print_point();

            distance = dist_2pts(M.malha[pos], destiny);

            //cout << distance << endl;

            //system("pause");
           // cout << endl;

            //cout << distance << endl;

            //Condição de parada.
            if (distance < 8){
				arrived = 1;
			}

			//dijkstra_list.clear();
        }
    }while(arrived == 0);

    //Organizar o vetor de pontos, começando do destino e "retraçando" o caminho até o início.
    int pos_aux2 = -1;
    do{
        points_list.push_back(M.malha[pos]);
        pos = M.malha[pos].get_pto_ant();
        pos_aux2 = pos;
    }while(pos_aux2 != M.malha.size()/2);

    return points_list;
}

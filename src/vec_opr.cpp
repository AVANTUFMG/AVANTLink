#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>

#define R_TERRA 6378000

using namespace std;

inline double p_grau(double radianos)
{
    return (radianos*(180.0 / M_PI));
}

inline double p_rad(double graus)
{
    return (graus*(M_PI/180));
}

inline double raio(double lat)
{
    return (R_TERRA - 21000*sin(lat));
}

class vetor_distancia //Uma instância desta classe possui um vetor unitário V e um módulo (distancia) R.
{
public:
    double R;
    double V[3];
    vetor_distancia();
    vetor_distancia atualiza(double*, double*,double,double);
    vetor_distancia operator + (const vetor_distancia& vec)
    {
        vetor_distancia temp;
        for(int i=0;i<3;i++)
        {
            temp.V[i] = V[i] + vec.V[i];
        }
        temp.R = sqrt(temp.V[0]*temp.V[0] + temp.V[1]*temp.V[1] + temp.V[2]*temp.V[2]);
        for(int i=0;i<3;i++)
        {
            temp.V[i] = temp.V[i]/temp.R;
        }
        return temp;
    }
    vetor_distancia operator - (const vetor_distancia& vec)
    {
        vetor_distancia temp;
        for(int i=0;i<3;i++)
        {
            temp.V[i] = V[i] - vec.V[i];
        }
        temp.R = sqrt(temp.V[0]*temp.V[0] + temp.V[1]*temp.V[1] + temp.V[2]*temp.V[2]);
        for(int i=0;i<3;i++)
        {
            temp.V[i] = temp.V[i]/temp.R;
        }
        return temp;
    }
};


vetor_distancia vetor_distancia::atualiza(double pt_ini[], double pt_fin[],double ang_ref,double brng_ref)
{//ang_ref é o ângulo de alcance lateral de referência da câmera
 //brng_ref é a direção da aeronave em termos de "bearing"
    vetor_distancia output;
    double lat1,lat2,lon1,lon2,alt1,alt2,ang1,dlon,dlat,mlat,a,c,dist_plan,dist,V_x,V_y,V_z;
    lat1=pt_ini[0];lon1=pt_ini[1];alt1=pt_ini[2]; //coord aeronave
    lat2=pt_fin[0];lon2=pt_fin[1];alt2=pt_fin[2]; //coord ponto qualquer
    double y = sin(lon2 - lon1)*cos(lat2);
    double x = cos(lat1)*sin(lat2) - sin(lat1)*cos(lat2)*cos(lon2-lon1);
    double brng = p_grau(atan2(y,x));
    ang1 = brng - brng_ref;
    if(ang1 > ang_ref)
        return output;
    /*Para achar a distância, usamos a fórmula de "haversine"*/
    dlon = lon2 - lon1;
    dlat = lat2 - lat1;
    mlat = fmin(lat1,lat2);
    a = pow(sin(dlat/2),2) + cos(lat1)*cos(lat2)*pow(sin(dlon/2),2);
    c = 2*asin(fmin(1,sqrt(a)));
    dist_plan = raio(dlat/2+mlat)*c;
    dist = sqrt(dist_plan*dist_plan + alt1*alt2);
    V_y = dist*sin(p_rad(brng));
    V_x = dist*cos(p_rad(brng));
    V_z = alt2 - alt1;
    output.V[0] = V_x;
    output.V[1] = V_y;
    output.V[2] = V_z;
    output.R = dist;
    for(int i=0;i<3;i++)
    {
        output.V[i] = output.V[i]/dist;
    }
    return output;
}

vetor_distancia::vetor_distancia()
{
    for(int i=0;i<3;i++)
    {
        V[i] = 0;
    }
    R = sqrt(V[0]*V[0]+V[1]*V[1]+V[2]*V[2]);
}

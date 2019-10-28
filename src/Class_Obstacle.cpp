#include "Class_Obstacle.h"

using namespace std;

obstacle& obstacle::operator=(const obstacle& o){

    height = o.height;

    radius = o.radius;

    obs_lat = o.obs_lat;

    obs_lon = o.obs_lon;

    return *this;

}

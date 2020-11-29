#include "Class_Point.h"
#include "Global_Functions.h"


using namespace std;

double Point::distance_from(Point &p){

        return(distance_between_two_points(this->get_latitude(), this->get_longitude(), this->get_height(),p.get_latitude(), p.get_longitude(), p.get_height()));
}
double Point::distance_from(double Dlat, double Dlon, double DH){

        return(distance_between_two_points(this->get_latitude(), this->get_longitude(), this->get_height(), Dlat, Dlon, DH));
}


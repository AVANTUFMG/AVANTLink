#ifndef ARESTAS_H_INCLUDED
#define ARESTAS_H_INCLUDED

#pragma once
#include <iostream>
#include <stdlib.h>
#include <list>

class Arestas
{
private:
    double A;
    double B;

public:
    void setA(double a);
    void setB(double b);

    double getA();
    double getB();
};



#endif // ARESTAS_H_INCLUDED
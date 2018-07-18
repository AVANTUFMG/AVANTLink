#include "Print.h"
#include <string>
#include <fstream>
#include <iostream>

std::ofstream file;

void logcat_open(std::string str)  //Inicia o log
{
    file.open(str);
    file<<"Initializing log"<<std::endl;
    file<<"AVANT-UFMG 2018"<<std::endl;
}

void logcat_close() //Fecha o log
{
    file.close();
}

void logcat(std::string str) //Imprime sem adicionar nova linha (adicionar Overloads conforme a necessidade)
{
    file<<str;
    std::cout<<str;
}

void logcat(int str) //Overload
{
    file<<str;
    std::cout<<str;
}

void logcatln(std::string str) //Imprime adicionando nova linha (adicionar Overloads conforme a necessidade)
{
    file<<str<<std::endl;
    std::cout<<str<<std::endl;
}

void logcatln(int str) //Overload
{
    file<<str<<std::endl;
    std::cout<<str<<std::endl;
}


/*
    Caio TBC
    Universidade Federal de Minas Gerais
    AVANT-UFMG 2018
*/

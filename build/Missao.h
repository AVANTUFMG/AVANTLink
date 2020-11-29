#ifndef MISSAO_H_INCLUDED
#define MISSAO_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include "Class_Point.h"
#include "PontoChegada.h"
#include "PontoPartida.h"
#include "Busca.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::ordered_json;

class Etapa {

private:
    /*Cada objeto etapa possui 4 atributos, cada um deles sendo um dos
    poss�veis tipos de etapa. O �nico que ser� inicializado � aquele que
    corresponde ao tipo de etapa que se quer, tendo os outros valor nulo*/
    Point waypoint;
    Busca aBusca;
    PontoChegada destino;
    PontoPartida origem;


    //BOOLS QUE PERMITEM SABER O TIPO QUE ETAPA REPRESENTA
    bool ehWaypoint = false;
    bool ehAreaBusca = false;
    bool ehBusca = false;
    bool ehPontoChegada = false;
    bool ehPontoPartida = false;

public:
    //CONSTRUTORES
    /*Cada construtor de 'Etapa' recebe um objeto. O objeto � salvo no atributo
    da 'Etapa' correspondente ao seu tipo*/
    Etapa() {}
    Etapa(Point p) : waypoint(p) { ehWaypoint = true; }
    Etapa(PontoChegada pC) : destino(pC) { ehPontoChegada = true; }
    Etapa(PontoPartida pO) : origem(pO) { ehPontoPartida = true; }
    Etapa(Busca b) : aBusca(b) { ehBusca = true; }

    //GETTERS
    Point getWaypoint() { return waypoint; }
    Busca getABusca() { return aBusca; }
    PontoChegada getDestino() { return destino; }
    PontoPartida getOrigem() { return origem; }

    //GETTERS DOS BOOLEANOS (usados nos m�todos abaixo, num primeiro momento)
    bool getEhWaypoint() { return ehWaypoint; }
    bool getEhBusca() { return ehBusca; }
    bool getEhPontoChegada() { return ehPontoChegada; }
    bool getEhPontoPartida() { return ehPontoPartida; }

    //RETORNA UM CHAR QUE REPRESENTA O TIPO DA ETAPA
    char getTipoEtapa();
};

class Missao {

public:
    string nomeMissao;
    std::string getNomeMissao() {
        return nomeMissao;
    }

    /*Uma lista duplamente encadeada de etapas e outra de velocidades*/
    list <Etapa> etapas;
    list <double> velocidades;


    //CONSTRUTORES
    Missao() {}
    Missao(string nome) : nomeMissao(nome) {};

    //M�TODOS
    void inicializaMissao(PontoPartida p);
    void finalizaMissao(PontoChegada f); //#########   NOVO   #########//

    void addEtapa(Etapa e);
    void addEtapa(Etapa e, int pos, double velo);//Sobrecarga que recebe posi��o e velocidade
    void addEtapa(Etapa e, double velo);//Sobrecarga que recebe apenas a velocidade
    void addEtapa(Etapa e, int pos);//Sobrecarga que recebe apenas a posi��o

    void removeEtapa(); //Remove a etapa do final da lista
    void removeEtapa(int pos); //Remove a etapa da posi��o oferecida

    void mudaVelo(int pos, double velo); //Modifica a velocidade de uma posi��o espec�fica da lista de velocidades

    void mudaNomeMissao(string n) { nomeMissao = n; }
    
    
    //JSON
    string enderecoJsonOut; //Guarda um endere�o onde ser� criado o arquivo JSON da miss�o
    void setEnderecoJsonOut(string str) {
        enderecoJsonOut = str;
    };

    json pointToJson(Point p); //#########   NOVO   #########//
    void missaoToJson(json& j);

    string enderecoJsonIn; //Guarda o endere�o de um arquivo JSON que ser� lido para criar a miss�o
    void setEnderecoJsonIn(string str) {
        enderecoJsonIn = str;
    };

    void fromJson(json& j);
    
};



#endif // MISSAO_H_INCLUDED

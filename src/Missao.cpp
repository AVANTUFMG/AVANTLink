#include "Missao.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <map>

using namespace std;

//RETORNA UM CHAR QUE REPRESENTA QUAL O TIPO DA ETAPA
//w - waypoint; i - ponto de partida; f - ponto de chegada; a - area de busca; b - area de busca teste
char Etapa::getTipoEtapa() {
    if (getEhBusca())
        return 'a';
    else if (getEhPontoChegada())
        return 'f';
    else if (getEhPontoPartida())
        return 'i';
    else if (getEhWaypoint())
        return 'w';
    //Se no futuro der algum problema, passar como parametro uma etapa x, em vez de n�o passar nenhum;
}

//INICIALIZA COM UMA POSI��O
void Missao::inicializaMissao(PontoPartida p) {
    Etapa e(p);
    etapas.push_front(e);
    velocidades.push_front(0);
}

//FINALIZA A MISS�O COM UM PONTO DE CHEGADA E VELOCIDADE 0
void Missao::finalizaMissao(PontoChegada f) {  //#########   NOVO   #########//
    Etapa e(f);
    etapas.push_back(e);
    velocidades.push_back(0);
}

//ADICIONA UMA ETAPA//
void Missao::addEtapa(Etapa e) {
    /*Insere a etapa na �ltima posi��o da lista e instancia sua velocidade
    como a velocidade da etapa anterior, se n�o for menor que 10*/
    etapas.push_back(e);
    double veloDoUltimo = velocidades.back();

    if (veloDoUltimo < 10)
        velocidades.push_back(10);
    else
        velocidades.push_back(veloDoUltimo);
}

void Missao::addEtapa(Etapa e, int pos, double velo) {
    list<Etapa>::iterator it = etapas.begin();
    list<double>::iterator it2 = velocidades.begin();

    advance(it, pos);
    advance(it2, pos);
    /*Insere a velocidade fornecida na posi��o(pos) da lista de velocidades
    e faz o mesmo com a etapa fornecida*/
    etapas.insert(it, e);
    velocidades.insert(it2, velo);
}

void Missao::addEtapa(Etapa e, double velo) {
    /*Nessa sobrecarga s�o oferecidos apenas o objeto etapa e a velocidade da
    etapa. A posi��o � sempre no final da lista*/
    etapas.push_back(e);
    velocidades.push_back(velo);
}

void Missao::addEtapa(Etapa e, int pos) {
    /*Nessa sobrecarga s�o oferecidos apenas o objeto etapa e a posi��o da
    etapa. A velocidade � a mesma da anterior, mas tem que ser no m�nimo 10*/
    list<Etapa>::iterator iteEtapa = etapas.begin();
    list<double>::iterator iteVelo = velocidades.begin();

    advance(iteEtapa, pos);
    advance(iteVelo, pos - 1);

    double veloAnterior = *iteVelo;
    advance(iteVelo, 1);

    etapas.insert(iteEtapa, e);
    if (veloAnterior < 10)
        velocidades.insert(iteVelo, 10);
    else
        velocidades.insert(iteVelo, veloAnterior);
}


//REMOVE UMA ETAPA
void Missao::removeEtapa() {
    etapas.pop_back();
    velocidades.pop_back();
}

void Missao::removeEtapa(int pos) {
    list<Etapa>::iterator it = etapas.begin();
    list<double>::iterator it2 = velocidades.begin();

    advance(it, pos);
    advance(it2, pos);

    etapas.erase(it);
    velocidades.erase(it2);
}

//MODIFICA VELOCIDADE
void Missao::mudaVelo(int pos, double velo) {
    list<double>::iterator iterate = velocidades.begin();

    advance(iterate, pos);

    velocidades.erase(iterate);
    velocidades.insert(iterate, velo);
}


//M�TODOS JSON

//Transforma uma miss�o em um arquivo .json

json Missao::pointToJson(Point p) { //#########   NOVO   #########//
    //Retorna um valor do tipo json montado com lat, long e altura

    json pontoJson = { p.get_latitude(), p.get_longitude(), p.get_height() };
        //{"Latitude", p.get_latitude()}, {"Longitude", p.get_longitude()}, {"Altura", p.get_height()}//Outra maneira
    return pontoJson;
}



void Missao::missaoToJson(json& j) { //#########   ATUALIZADO   #########//
        //Transforma uma miss�o em um arquivo .json

    j["Missao"] = nomeMissao;
    list<Etapa>::iterator iterEtapa;
    list<double>::iterator iterVelo;
    int position = 0; //Vari�vel auxiliar que diz a posi��o de cada etapa na lista

    //La�o para percorrer toda a lista de etapas e adicion�-las ao � vari�vel JSON
    for (iterEtapa = etapas.begin(), iterVelo = velocidades.begin();
        iterEtapa != etapas.end(), iterVelo != velocidades.end(); iterEtapa++, iterVelo++) {

        Etapa etAux = *iterEtapa;

        //Cria uma string �til no JSON, que junta a etapa ao inteiro de sua posi��o
        string numEtapa = "Etapa " + std::to_string(position);

        //Condicionais para pegar apenas as informa��es �teis de cada objeto etapa, segundo seu tipo
        if (etAux.getTipoEtapa() == 'a') {
            //json j1;
            //etAux.getABusca().getVertJson(j1);
            j[numEtapa] = {
                {"Tipo", "Area de Busca"},
                {"Posicao", position},
                {"Numero de vertices", etAux.getABusca().getNumVertices()},
                {"Distancia entre pontos", etAux.getABusca().getDist()},
                {"Vertices", etAux.getABusca().getVertJson()},
                {"Velocidade", *iterVelo}

            };
        }
        else if (etAux.getTipoEtapa() == 'i') {
            j[numEtapa] = {
                {"Tipo", "Ponto de Partida"},
                {"Posicao", position},
                {"Coordenadas do ponto inicial", pointToJson(etAux.getOrigem().getInitialPoint())},
                {"Coordenadas do ponto de aproximacao", pointToJson(etAux.getOrigem().getApproxPoint())},
                {"Velocidade", *iterVelo}
            };
        }
        else if (etAux.getTipoEtapa() == 'f') {
            j[numEtapa] = {
                {"Tipo", "Ponto de Chegada"},
                {"Posicao", position},
                {"Coordenadas do ponto final", pointToJson(etAux.getDestino().getLastPoint())},
                {"Coordenadas do ponto de aproximacao", pointToJson(etAux.getDestino().getApproxPoint())},
                {"Velocidade", *iterVelo}
            };
        }
        else if (etAux.getTipoEtapa() == 'w') {
            j[numEtapa] = {
                {"Tipo", "Waypoint"},
                {"Posicao", position},
                {"Coordenadas", pointToJson(etAux.getWaypoint())},
                {"Velocidade", *iterVelo}
            };
        }
        position++;
    }

    //Escreve num arquivo .json
    std::ofstream o(enderecoJsonOut);
    o << std::setw(4) << j << std::endl;
    cout << "Arquivo criado com sucesso!!" << endl;
}

/*Recebe um endere�o de um arquivo .json e o transforma num objeto da classe miss�o,
salvo na vari�vel que chamou o m�todo*/

void Missao::fromJson(json& j) {  //#########   ATUALIZADO   #########//
    /*Recebe um endere�o de um arquivo .json e o transforma num objeto da classe miss�o,
    salvo na vari�vel que chamou o m�todo*/

    std::ifstream i(enderecoJsonIn);
    i >> j;

    //Pega o nome da miss�o
    j.at("Missao").get_to(nomeMissao);

    for (int position = 0; ; position++) {

        string numEtapa = "Etapa " + std::to_string(position);

        //Atributos fixos dos objetos "Etapa" no JSON
        string tipoEtapa = (j.at(numEtapa).at("Tipo"));
        int posEtapa = (j.at(numEtapa).at("Posicao"));
        double veloEtapa = (j.at(numEtapa).at("Velocidade"));

        /*Condicionais que pegam o tipo da etapa e permitem pegar os
        atributos espec�ficos de cada objeto etapa diferente*/

        if (tipoEtapa == "Area de Busca") {
            //Pega os atributos espec�ficos
            int numV = j.at(numEtapa).at("Numero de vertices");
            double distancia = j.at(numEtapa).at("Distancia entre pontos");
            json vertices = j.at(numEtapa).at("Vertices"); //Separa o objeto json inteiro para ser tratado dentro do m�todo espec�fico

            //Constr�i um objeto do tipo
            Busca B;
            B.setDist(distancia);
            B.setNumVert(numV);
            B.setVertsFromJson(vertices); //Vai salvar o vetor auxiliar no vetor de vertices do objeto B
            //Inicializa uma etapa daquele tipo;
            Etapa etapaB(B);
            //Coloca a etapa na lista, usando a sobrecarga de addEtapa que pega velocidade e posi��o
            addEtapa(etapaB, posEtapa, veloEtapa);
        }

        else if (tipoEtapa == "Ponto de Partida") {
            //Pega os atributos espec�ficos
            //Essa l�gica pega o index do valor que se deseja dentro do objeto json
            double lat = j.at(numEtapa).at("Coordenadas do ponto inicial").at(0);
            double lon = j.at(numEtapa).at("Coordenadas do ponto inicial").at(1);
            double lat2 = j.at(numEtapa).at("Coordenadas do ponto de aproximacao").at(0);
            double lon2 = j.at(numEtapa).at("Coordenadas do ponto de aproximacao").at(1);
            double h2 = j.at(numEtapa).at("Coordenadas do ponto de aproximacao").at(2);
            //Constr�i um objeto do tipo
            PontoPartida I(lat, lon);
            I.setApproxPoint(lat2, lon2, h2);
            //Inicializa uma etapa daquele tipo;
            Etapa etapaI(I);
            //Coloca a etapa na lista, usando a sobrecarga de addEtapa que pega velocidade e posi��o
            addEtapa(etapaI, posEtapa, veloEtapa);
        }

        else if (tipoEtapa == "Ponto de Chegada") {
            //Pega os atributos espec�ficos
            double lat = j.at(numEtapa).at("Coordenadas do ponto final").at(0);
            double lon = j.at(numEtapa).at("Coordenadas do ponto final").at(1);
            double lat2 = j.at(numEtapa).at("Coordenadas do ponto de aproximacao").at(0);
            double lon2 = j.at(numEtapa).at("Coordenadas do ponto de aproximacao").at(1);
            double h2 = j.at(numEtapa).at("Coordenadas do ponto de aproximacao").at(2);
            //Constr�i um objeto do tipo
            PontoChegada F(lat, lon);
            F.setApproxPoint(lat2, lon2, h2);
            //Inicializa uma etapa daquele tipo;
            Etapa etapaF(F);
            //Coloca a etapa na lista, usando a sobrecarga de addEtapa que pega velocidade e posi��o
            addEtapa(etapaF, posEtapa, veloEtapa);

            //Como � sempre a �ltima etapa, ao fim faz com que saia do ciclo
            break;
        }
        else if (tipoEtapa == "Waypoint") {
            //Pega os atributos espec�ficos
            //Essa l�gica pega o index do valor que se deseja dentro do objeto json, no caso o "Coordenadas"
            double lat = j.at(numEtapa).at("Coordenadas").at(0);
            double lon = j.at(numEtapa).at("Coordenadas").at(1);
            double alt = j.at(numEtapa).at("Coordenadas").at(2);
            //Constr�i um objeto do tipo
            Point W(lat, lon, alt);
            //Inicializa uma etapa daquele tipo;
            Etapa etapaW(W);
            //Coloca a etapa na lista, usando a sobrecarga de addEtapa que pega velocidade e posi��o
            addEtapa(etapaW, posEtapa, veloEtapa);
        }

        i.close();
    }
    cout << "Missao criada com sucesso!!" << endl;
    /*OBS: Esse m�todo n�o funciona como deveria se a �ltima etapa n�o for um 'Ponto de Chegada', devido � presen�a
    do break (na posi��o que est�) no la�o acima*/
}


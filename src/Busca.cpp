#include "Busca.h"

using namespace std;


void Busca::setyMax(double k)
{
	this->ymax = k;
}

void Busca::setDist(double d)
{
	this->dist = d;
}

void Busca::setVertices(int vert)
{
	this->nvert = vert;
}

void Busca::setListaVertices(double x, double y, int i) {
	Point* point = new Point();

	cout << x << ", " << y << " na posicao " << i << endl;
	this->vertices[i] = point;

	vertices[i]->set_x(x);
	vertices[i]->set_y(y);

	cout << point->get_x() << ", " << point->get_y() << " na posicao " << i << endl;
}

int Busca::getPtsRota()
{
	return ptsRota;
}

int Busca::getNumVertices()
{
	return this->nvert;
}

double Busca::getDist()
{
	return this->dist;
}

double Busca::getyMax()
{
	return ymax;
}

void Busca::setArestas()
{
	int a, cnt, aux;
	double slope, inter;
	a = getNumVertices();
	aux = 0;
	// gerar arestas ligando os vertices:
	for (cnt = 0; cnt != a - 1; cnt++) {
		Arestas* are = new Arestas();
		this->arestas[cnt] = are;
		if (vertices[cnt + 1]->get_x() - vertices[cnt]->get_x() == 0) {
			slope = 97.849;
			arestas[cnt]->setA(slope);
			inter = vertices[cnt]->get_x();
			arestas[cnt]->setB(inter);
		}
		else {
			slope = (vertices[cnt + 1]->get_y() - vertices[cnt]->get_y()) / (vertices[cnt + 1]->get_x() - vertices[cnt]->get_x());
			arestas[cnt]->setA(slope);
			inter = (vertices[cnt + 1]->get_y()) - slope * vertices[cnt + 1]->get_x();
			arestas[cnt]->setB(inter);
		}
	}
	// aresta diferencial porque liga o ultimo vertice ao primeiro
	Arestas* are = new Arestas();
	this->arestas[cnt] = are;
	if (vertices[0]->get_x() - vertices[cnt]->get_x() == 0) {
		slope = 978.49;
		arestas[cnt]->setA(slope);
		inter = vertices[0]->get_x();
		arestas[cnt]->setB(inter);
	}
	else {
		slope = (vertices[0]->get_y() - vertices[cnt]->get_y()) / (vertices[0]->get_x() - vertices[cnt]->get_x());
		arestas[cnt]->setA(slope);
		inter = (vertices[cnt]->get_y()) - slope * vertices[cnt]->get_x();
		arestas[cnt]->setB(inter);
	}

	//Imprimir arestas:
	cout << "As arestas do poligono sao:\n";
	for (cnt = 0; cnt != a - 1; cnt++) {
		if (arestas[cnt]->getA() == 978.49) {
			cout << "X = " << arestas[cnt]->getB() << " ligando o ponto " << "(" << vertices[cnt]->get_x() << " , "
				<< vertices[cnt]->get_y() << ")" << " ao ponto " << "("
				<< vertices[cnt + 1]->get_x() << " , " << vertices[cnt + 1]->get_y() << ")" << "\n";
		}
		else {
			cout << "Y = " << arestas[cnt]->getA() << "X + " << arestas[cnt]->getB()
				<< " ligando o ponto " << "(" << vertices[cnt]->get_x() << " , "
				<< vertices[cnt]->get_y() << ")" << " ao ponto " << "("
				<< vertices[cnt + 1]->get_x() << " , " << vertices[cnt + 1]->get_y() << ")" << "\n";
		}
	}
	if (arestas[cnt]->getA() == 978.49) {
		cout << "X = " << arestas[cnt]->getB() << " ligando o ponto " << "(" << vertices[cnt]->get_x() << " , "
			<< vertices[cnt]->get_y() << ")" << " ao ponto " << "("
			<< vertices[0]->get_x() << " , " << vertices[0]->get_y() << ")" << "\n";
	}
	else {
		cout << "Y = " << arestas[cnt]->getA() << "X + " << arestas[cnt]->getB()
			<< " ligando o ponto " << "(" << vertices[cnt]->get_x() << " , "
			<< vertices[cnt]->get_y() << ")" << " ao ponto " << "("
			<< vertices[0]->get_x() << " , " << vertices[0]->get_y() << ")" << "\n";
	}
}

void Busca::setRepeticao(bool rept)
{
	this->loop = rept;
}

void Busca::setNumVert(int vert)
{
	this->nvert = vert;
	int a = 0;
	// iniciazizar pontos com base no numero de vertices digitado pelo usuario
	while (a != vert) {
		Point* v1 = new Point(NULL, NULL, 15);
		this->vertices[a] = v1;
		a++;
	}
}

void Busca::getVert()
{
	int a = 0, b;
	b = getNumVertices();
	//imprimir vertices:
	while (a != b) {
		cout << "(" << vertices[a]->get_x() << " , " << vertices[a]->get_y() << ")" << "\n";
		a++;
	}
}

string Busca::getVerticesString(int aux)
{
	int a = aux, b;
	b = getNumVertices();
	//imprimir vertices:

	std::stringstream ssx, ssy;
	while (a != b) {
		ssx << std::fixed << std::setprecision(2) << vertices[a]->get_x();
		ssy << std::fixed << std::setprecision(2) << vertices[a]->get_y();
		return " " + ssx.str() + ", " + ssy.str() + ",";
		a++;
	}
}

//-------INICIO DA PARTE QUE O PEDRO COLOCOU-------//
/*Transforma o vetor de *Point 'vertices' em um objeto json e o retorna.
Ele pode ser passado diretamente para o metodo missaoToJson, da classe Missao.*/

json Busca::getVertJson()
{
	json vetor;
	for (int i = 0; i < nvert; i++) {
		vetor[i] = { vertices[i]->get_x(), vertices[i]->get_y() };
	}

	return vetor;
}

/*Constrói o vetor de *Point 'vertices' a partir do que foi lido no json
e passado como parametro pra essa funcao. */
void Busca::setVertsFromJson(json j) {

	for (int i = 0; i < nvert; i++) {
		//Pega x e y de cada objeto json no array json "Vertices", de acordo com o index
		double xJson = j.at(i).at(0);
		double yJson = j.at(i).at(1);
		vertices[i]->set_x(xJson);
		vertices[i]->set_y(yJson);
	}
}
//-------FIM DA PARTE QUE O PEDRO COLOCOU------//

//-------PEDRO QUE FEZ ISSO, PODE TIRAR DEPOIS------//
/*Esse m�todo salva numa vari�vel json, oferecida como par�metro, um
map, j� convertido para json, que cont�m os v�rtices inseridos pelo usu�rio*/
//Foi usado map aqui, o c�digo est� propenso a erros. Precisa ser analisado no futuro

/*void Busca::getVertJson(json& j)
{
	int a = 0, b;
	std::map<int, int> c_map;
	b = getNumVertices();
	//imprimir vertices:
	while (a != b) {
		c_map.insert(pair<int, int>(vertices[a]->get_x(), vertices[a]->get_y()));
		a++;
	}
	json j_map(c_map);
	j = j_map;
}

//--------TESTE AQUI---------//
void Busca::jsonToVert(Point* vet[], int n){
	int a = 0, b;
	b = getNumVertices();
	while (a != b) {
		vertices[a] = vet[a];
		a++;
	}
}

//--------TESTE AQUI---------//

//-------PEDRO QUE FEZ ISSO, PODE TIRAR DEPOIS------/*/

void Busca::setPtsRota(int p)
{
	this->ptsRota = p;
}

void Busca::setTempo(int tempo)
{
	this->timeout = tempo;
}


void Busca::iniciarPol(int v, int temp, bool rep) {
	setNumVert(v);
	setRepeticao(rep);
	setTempo(temp);
}

void Busca::iniciarBusca(int met, Busca::objetos obj, double d) {
	setDist(d);

	int a;
	double n = 0, minx = 0, maxx = 0, miny = 0, maxy = 0;
	a = getNumVertices();
	int cnt = 0;
	//usuario entra com os valores dos vertices
	cin >> n;
	vertices[cnt]->set_x(n);
	//minx = n;
	//maxx = n;
	cin >> n;
	vertices[cnt]->set_y(n);
	//miny = n;
	maxy = n;
	for (cnt = 1; cnt != a; cnt++) {
		cin >> n;
		vertices[cnt]->set_x(n);
		//if (n <= minx)
			//minx = n;
		//if (n >= maxx)
			//maxx = n;
		cin >> n;
		vertices[cnt]->set_y(n);
		//if (n <= miny)
			//miny = n;
		if (n >= maxy)
			maxy = n;
	}

	setyMax(maxy);

	cout << "Voce entrou com os seguintes vertices:\n";
	getVert();


	//o metodo entrado define a funcionalidade a ser executada
	if (met == 1) {
		pontosDaRota();
	}
}

void Busca::pontosDaRota()
{
	int cnt = 1, cnt2 = 0, sentido = 1, cnt3 = 0;
	double xmin = 0, xmax = 0, d;
	d = getDist();
	int a;
	double rot, lim;
	a = getNumVertices() - 1;
	setArestas();

	rot = vertices[0]->get_y();
	rot += 1.0;
	lim = getyMax();

	Point* vaux1 = vertices[cnt];
	Point* vaux2 = vertices[a];

	Arestas* araux1 = arestas[cnt - 1];
	Arestas* araux2 = arestas[a];


	while (rot < lim) {
		while (vaux1->get_y() < rot) {
			cnt++;
			vaux1 = vertices[cnt];
			araux1 = arestas[cnt - 1];
		}
		while (vaux2->get_y() < rot) {
			cnt2++;
			vaux2 = vertices[a - cnt2];
			araux2 = arestas[a - cnt2];
		}

		xmin = (rot - araux2->getB()) / araux2->getA();
		xmax = (rot - araux1->getB()) / araux1->getA();
		if (araux2->getA() == 978.49) {
			xmin = araux2->getB();
		}
		if (araux1->getA() == 978.49) {
			xmax = araux1->getB();
		}

		if (sentido == 1) {
			xmin += d;
			while (xmin < xmax) {

				Point* ponto = new Point(NULL, NULL, 15);
				this->rota[cnt3] = ponto;
				rota[cnt3]->set_x(xmin);
				rota[cnt3]->set_y(rot);

				cnt3++;
				xmin += d;
			}
			sentido = -1;

		}
		else {
			xmax -= d;
			while (xmax > xmin) {

				Point* ponto = new Point(NULL, NULL, 15);
				this->rota[cnt3] = ponto;
				rota[cnt3]->set_x(xmax);
				rota[cnt3]->set_y(rot);

				cnt3++;
				xmax -= d;
			}
			sentido = 1;
		}
		rot += 1.0;
	}

	setPtsRota(cnt3);

	cout << "A rota sera composta pelos seguintes pontos:\n";
	for (cnt = 0; cnt != cnt3 - 1; cnt++) {
		cout << "(" << rota[cnt]->get_x() << " , " << rota[cnt]->get_y() << ") -> ";
	}
	cout << "(" << rota[cnt]->get_x() << " , " << rota[cnt]->get_y() << ")";
}

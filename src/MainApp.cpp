#include "MainApp.h"
#include "Missao.h"
#include "PontoPartida.h"
#include "PontoChegada.h"

#include <limits.h>
#include <sstream>


#define WAYPOINT 0
#define AREA_DE_BUSCA 1


//Regex
std::regex regPosicao("(^(-?\\b(([0-9]|[1-8][0-9]|90)(\\.[0-9]{1,6})?)\\b, -?\\b(([0-9]|[1-8][0-9]|9[0-9]|1[0-7][0-9]|180)(\\.[0-9]{1,6})?)\\b; -?\\b(([0-9]|[1-8][0-9]|90)(\\.[0-9]{1,6})?)\\b, -?\\b(([0-9]|[1-8][0-9]|9[0-9]|1[0-7][0-9]|180)(\\.[0-9]{1,6})?)\\b, \\b(([0-9]|[1-8][0-9]|9[0-9]|[1-8][0-9]{2}|9[0-8][0-9]|99[0-9]|1000)(\\.[0-9]{1,6})?)\\b)$)");
std::regex regPoint("(^(-?\\b(([0-9]|[1-8][0-9]|90)(\\.[0-9]{1,6})?)\\b, -?\\b(([0-9]|[1-8][0-9]|9[0-9]|1[0-7][0-9]|180)(\\.[0-9]{1,6})?)\\b, \\b(([0-9]|[1-8][0-9]|9[0-9]|[1-8][0-9]{2}|9[0-8][0-9]|99[0-9]|1000)(\\.[0-9]{1,6})?)\\b)$)");
std::regex regPointPos("(^(-?\\b(([0-9]|[1-8][0-9]|90)(\\.[0-9]{1,6})?)\\b, -?\\b(([0-9]|[1-8][0-9]|9[0-9]|1[0-7][0-9]|180)(\\.[0-9]{1,6})?)\\b, \\b(([0-9]|[1-8][0-9]|9[0-9]|[1-8][0-9]{2}|9[0-8][0-9]|99[0-9]|1000)(\\.[0-9]{1,6})?)\\b; \\b(\\d+)\\b)$)");
std::regex regArea("(^(\\b([0-9]+)\\b, \\b([0-9]+)\\b;( \\d+,)+)$)");
std::regex regAreaPos("(^(\\b([0-9]+)\\b, \\b([0-9]+)\\b; \\b(\\d+)\\b;( \\d+,)+)$)");
std::regex regVelocidade("(^(\\b(\\d{1,4})(\\.\\d{1,6})?\\b)$)");
std::regex regVeloPosicao("(^(\\b(\\d{1,4})(\\.\\d{1,6})?\\b, \\b(\\d+)\\b)$)");
std::regex regVeloPosRepet("(^(\\b(\\d{1,4})(\\.\\d{1,6})?\\b, \\b(\\d+)\\b, \\b(\\d+)\\b)$)");
std::regex regVeloRepeticao("(^(\\b(\\d{1,4})(\\.\\d{1,6})?\\b, , \\b(\\d+)\\b)$)");

// Autoexplicativos
bool vantConnected = false;
bool missaoSalva = false;
Missao* missaoAtual = nullptr;

// Variável que guarda qual tela está sendo exibida no momento
int sizerShown;

//Janela principal
MainFrame* MainWin;

//Sizers
wxBoxSizer* MainSizer;
wxBoxSizer* MainMenuSizer;
wxBoxSizer* ConfigConnectionSizer;
wxBoxSizer* TelemetrySizer;
wxBoxSizer* CreateMissionSizer;
wxBoxSizer* LoadMissionSizer;

//Chamado na inicialização do app
bool MainApp::OnInit()
{
	MainWin = new MainFrame(_("Monitoramento e configuração dos VANT's"), wxDefaultPosition, wxDefaultSize);
	

	MainWin->Show(TRUE);
	SetTopWindow(MainWin);

	MainWin->ShowMainMenu();

	return true;
}

//Eventos disparados ao clicar nos botões do menu
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	// Menu Principal
	EVT_BUTTON(BUTTON_Connect, MainFrame::ConnectToVant)
	EVT_BUTTON(BUTTON_Telemetry, MainFrame::ViewTelemetry)
	EVT_BUTTON(BUTTON_CreateMission, MainFrame::CreateMission)
	EVT_BUTTON(BUTTON_LoadMission, MainFrame::LoadMission)
	EVT_BUTTON(BUTTON_ConfigureAirframe, MainFrame::ConfigureAirframe)
	EVT_BUTTON(BUTTON_CurrentMission, MainFrame::CurrentMission)
	EVT_BUTTON(BUTTON_Voltar, MainFrame::Voltar)

	// Criar Missão
	EVT_BUTTON(BUTTON_AdicionarEtapa, MainFrame::AdicionarEtapa)
	EVT_LISTBOX_DCLICK(LISTBOX_Etapas, MainFrame::RemoverEtapa)
	EVT_BUTTON(BUTTON_AdicionarVelocidade, MainFrame::AdicionarVelocidade)
	EVT_LISTBOX_DCLICK(LISTBOX_Velocidades, MainFrame::RemoverVelocidade)
	EVT_BUTTON(BUTTON_SalvarMissao, MainFrame::SalvarMissao)
	EVT_BUTTON(BUTTON_EnviarMissao, MainFrame::EnviarMissao)

	// Carregar Missão
	EVT_LISTBOX_DCLICK(LISTBOX_EtapasLoad, MainFrame::ShowRota)
	EVT_BUTTON(BUTTON_EditarMissao, MainFrame::EditMission)
END_EVENT_TABLE()


//Menu pricipal
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, -1, title, pos, size)
{	

	//Botar um menu superior, caso queira mudar
	/*
		MenuBar = new wxMenuBar();
		wxMenu* MainMenu = new wxMenu();
		MainMenu->Append(BUTTON_Connect, wxT("Conectar a um Vant"), wxT("Visualizar conexão atual ou criar nova conexão"));
		MainMenu->Append(BUTTON_Telemetry, wxT("Mostrar Telemetria"), wxT("Ver dados de telemetria do VANT"));
		MainMenu->Append(BUTTON_CreateMission, wxT("Fazer Missão"), wxT("Criar nova missão para o VANT"));
		MainMenu->Append(BUTTON_LoadMission, wxT("Carregar Missão"), wxT("Carregar missão salva no disco"));
		MainMenu->Append(BUTTON_CurrentMission, wxT("Missão Atual"), wxT("Visualizar missão atual do VANT"));
		MainMenu->Append(BUTTON_ConfigureAirframe, wxT("Configurar Airframe"), wxT("Configurar Airframe :p"));
		SetMenuBar(MenuBar);
		MenuBar->Append(MainMenu, "Menu Principal");
		CreateStatusBar(2);
	*/

	//Para iniciar em tela cheia
	Maximize();
}

// Chamado por OnInit quando o programa é aberto para exibir o Menu Principal
void MainFrame::ShowMainMenu() {

	// Cria os componentes da interface (só botões nesse caso)
	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainMenuSizer = new wxBoxSizer(wxVERTICAL);

	BtnConnectVant = new wxButton(this, BUTTON_Connect, wxT("Conectar a um VANT"),
		wxPoint(20, 20), wxSize(200, 50));

	BtnTelemetry = new wxButton(this, BUTTON_Telemetry, wxT("Mostrar Telemetria"),
		wxPoint(20, 90), wxSize(200, 50));

	BtnCreateMission = new wxButton(this, BUTTON_CreateMission, wxT("Criar Missão"),
		wxPoint(20, 160), wxSize(200, 50));

	BtnLoadMission = new wxButton(this, BUTTON_LoadMission, wxT("Carregar Missão"),
		wxPoint(20, 230), wxSize(200, 50));

	BtnCurrentMission = new wxButton(this, BUTTON_CurrentMission, wxT("Mostrar Missão Atual do VANT"),
		wxPoint(20, 300), wxSize(200, 50));

	BtnConfigureAirframe = new wxButton(this, BUTTON_ConfigureAirframe, wxT("Configurar Airframe"),
		wxPoint(20, 370), wxSize(200, 50));

	// Adiciona os componentes ao sizer do menu
	MainMenuSizer->Add(BtnConnectVant, 0, wxALL, 20);
	MainMenuSizer->Add(BtnTelemetry, 0, wxALL, 20);
	MainMenuSizer->Add(BtnCreateMission, 0, wxALL, 20);
	MainMenuSizer->Add(BtnLoadMission, 0, wxALL, 20);
	MainMenuSizer->Add(BtnCurrentMission, 0, wxALL, 20);
	MainMenuSizer->Add(BtnConfigureAirframe, 0, wxALL, 20);

	// Adiciona sizer do menu ao sizer principal
	MainSizer->Add(MainMenuSizer);
	MainWin->SetSizer(MainSizer);

}

// Chamado quando o botão "Voltar ao Menu Principal" de *qualquer* tela é clicado. O comportamento de todos os botões 
// desse tipo é o mesmo, logo, a mesma função pode ser utilizada
void MainFrame::Voltar(wxCommandEvent &evt) {
	switch (sizerShown) 
	{
	case SHOWN_ConfigConnectionSizer:
		ConfigConnectionSizer->DeleteWindows();
		break;

	case SHOWN_TelemetrySizer:
		TelemetrySizer->DeleteWindows();
		break;

	case SHOWN_CreateMissionSizer:
		CreateMissionSizer->DeleteWindows();
		break;
	
	case SHOWN_LoadMissionSizer:
		LoadMissionSizer->DeleteWindows();
		break;
	}

	ShowMainMenu();
	evt.Skip();
}


// Chamado quando o botão "Conectar a um VANT" é clicado
void MainFrame::ConnectToVant(wxCommandEvent& evt)
{
	ConfigConnectionSizer = new wxBoxSizer(wxVERTICAL);

	BtnCurrentConnection = new wxButton(MainWin, BUTTON_CurrentConnection, wxT("Conexão Atual"),
		wxPoint(20, 20), wxSize(200, 50));

	BtnNewConnection = new wxButton(MainWin, BUTTON_NewConnection, wxT("Nova Conexão"),
		wxPoint(20, 90), wxSize(200, 50));

	BtnVoltar = new wxButton(MainWin, BUTTON_Voltar, wxT("Voltar ao Menu Principal"),
		wxPoint(20, 160), wxSize(200, 50));

	ConfigConnectionSizer->Add(BtnCurrentConnection, 0, wxALL, 20);
	ConfigConnectionSizer->Add(BtnNewConnection, 0, wxALL, 20);
	ConfigConnectionSizer->Add(BtnVoltar, 0, wxALL, 20);

	//MainMenuSizer->Hide(TRUE);
	MainMenuSizer->DeleteWindows();
	MainSizer->Replace(MainMenuSizer, ConfigConnectionSizer);

	sizerShown = SHOWN_ConfigConnectionSizer;
}

// Chamado quando o botão "Mostrar Telemetria" é clicado
void MainFrame::ViewTelemetry(wxCommandEvent &evt)
{

	if (vantConnected)
	{
		//Sizer pai
		TelemetrySizer = new wxBoxSizer(wxVERTICAL);

		
		//Elementos bitrate
		wxBoxSizer* bitrateSizer = new wxBoxSizer(wxHORIZONTAL);

		wxStaticText* bitrateTitle = new wxStaticText(MainWin, wxID_ANY, "Bitrate: ",
			wxPoint(20, 20), wxSize(70, 30));

		wxListBox* bitrate = new wxListBox(MainWin, wxID_ANY, wxPoint(130, 20), wxSize(400, 30));

		bitrateSizer->Add(bitrateTitle, 0, wxALL, 20);
		bitrateSizer->Add(bitrate, 0, wxALL, 20);


		//Elementos velocidade
		wxBoxSizer* velocitySizer = new wxBoxSizer(wxHORIZONTAL);

		wxStaticText* velocityTitle = new wxStaticText(MainWin, wxID_ANY, "Velocidade: ",
			wxPoint(20, 80), wxSize(70, 30));

		wxListBox* velocity = new wxListBox(MainWin, wxID_ANY, wxPoint(130, 80), wxSize(400, 30));

		velocitySizer->Add(velocityTitle, 0, wxALL, 20);
		velocitySizer->Add(velocity, 0, wxALL, 20);


		//Elementos bateria
		wxBoxSizer* batteryTensionSizer = new wxBoxSizer(wxHORIZONTAL);

		wxStaticText* batteryTensionTitle = new wxStaticText(MainWin, wxID_ANY, "Bateria: ",
			wxPoint(20, 140), wxSize(70, 30));

		wxListBox* batteryTension = new wxListBox(MainWin, wxID_ANY, wxPoint(130, 140), wxSize(400, 30));

		batteryTensionSizer->Add(batteryTensionTitle, 0, wxALL, 20);
		batteryTensionSizer->Add(batteryTension, 0, wxALL, 20);


		//Elementos latitude
		wxBoxSizer* latitudeSizer = new wxBoxSizer(wxHORIZONTAL);

		wxStaticText* latitudeTitle = new wxStaticText(MainWin, wxID_ANY, "Latitude: ",
			wxPoint(20, 200), wxSize(70, 30));

		wxListBox* latitude = new wxListBox(MainWin, wxID_ANY, wxPoint(130, 200), wxSize(400, 30));

		latitudeSizer->Add(latitudeTitle, 0, wxALL, 20);
		latitudeSizer->Add(latitude, 0, wxALL, 20);


		//Elementos longitude
		wxBoxSizer* longitudeSizer = new wxBoxSizer(wxHORIZONTAL);

		wxStaticText* longitudeTitle = new wxStaticText(MainWin, wxID_ANY, "Longitude: ",
			wxPoint(20, 260), wxSize(70, 30));

		wxListBox* longitude = new wxListBox(MainWin, wxID_ANY, wxPoint(130, 260), wxSize(400, 30));

		longitudeSizer->Add(longitudeTitle, 0, wxALL, 20);
		longitudeSizer->Add(longitude, 0, wxALL, 20);


		//Elementos altura
		wxBoxSizer* heightSizer = new wxBoxSizer(wxHORIZONTAL);

		wxStaticText* heightTitle = new wxStaticText(MainWin, wxID_ANY, "Altura: ",
			wxPoint(20, 320), wxSize(70, 30));

		wxListBox* altura = new wxListBox(MainWin, wxID_ANY, wxPoint(130, 320), wxSize(400, 30));

		heightSizer->Add(heightTitle, 0, wxALL, 20);
		heightSizer->Add(altura, 0, wxALL, 20);


		wxButton* BtnVoltar = new wxButton(MainWin, BUTTON_Voltar, "Voltar ao Menu Principal",
			wxPoint(20, 380), wxSize(200, 50));


		// Adiciona todos os componentes ao sizer
		TelemetrySizer->Add(bitrateSizer);
		TelemetrySizer->Add(velocitySizer);
		TelemetrySizer->Add(batteryTensionSizer);
		TelemetrySizer->Add(latitudeSizer);
		TelemetrySizer->Add(longitudeSizer);
		TelemetrySizer->Add(heightSizer);
		TelemetrySizer->Add(BtnVoltar, 0, wxALL, 20);

		// Troca a tela de menu principal pela de telemetria
		MainMenuSizer->DeleteWindows();
		MainSizer->Replace(MainMenuSizer, TelemetrySizer);

		// Necessário para ter controle do estado atual do programa i.e. qual tela está sendo exibida
		sizerShown = SHOWN_TelemetrySizer;

	}
	else 
	{

		// Exibe um dialog se nenhum VANT estiver conectado para exibir a telemetria
		wxMessageDialog* noConnectionDialog = new wxMessageDialog(MainWin, wxT("Nenhum VANT conectado no momento"),
			wxT("Sem conexão"), wxOK, wxDefaultPosition);

		noConnectionDialog->ShowModal();

	}
	evt.Skip();
}

// Chamado quando o botão "Criar Missão" é clicado
void MainFrame::CreateMission(wxCommandEvent& evt)
{
	ShowMissionEditor();
	evt.Skip();
}

// Chamado quando o botão "Carregar Missão" é clicado
void MainFrame::LoadMission(wxCommandEvent& evt)
{
	ShowMissionDisplay();

	//Exibe o dialog para escolher o arquivo para abrir
	wxFileDialog* FileDialog = new wxFileDialog(this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
		_("Arquivo JSON (*.json)|*.json"), wxFD_OPEN, wxDefaultPosition);

	if (FileDialog->ShowModal() == wxID_OK)		// Se o usuário clicou Ok ao invés de Cancelar
	{
		//Pegar o caminho do arquivo escolhido para abrir
		MissionPath = FileDialog->GetPath();
		std::string path = std::string(MissionPath.mb_str());

		//Precisa reinicializar o objeto
		missaoAtual = new Missao();

		//Diz qual o caminho pra abrir
		missaoAtual->setEnderecoJsonIn(path);

		json j;
		missaoAtual->fromJson(j);

		ShowMissionData();

	}

	evt.Skip();
}

// Carrega os dados do disco para exibí-los no display carregado por ShowMissionDisplay
void MainFrame::ShowMissionData() {

	list<Etapa>::iterator iterEtapa;
	list<double>::iterator iterVelo;

	nome->SetLabel(missaoAtual->getNomeMissao());
	nome->Refresh();

	//Esse laço é o que percorre a lista de etapas, imprimindo tudo
	for (iterEtapa = missaoAtual->etapas.begin(), iterVelo = missaoAtual->velocidades.begin();
		iterEtapa != missaoAtual->etapas.end(), iterVelo != missaoAtual->velocidades.end(); iterEtapa++, iterVelo++) {

		Etapa etAux = *iterEtapa;

		//LAÇO PARA DIZER QUAL O TIPO
		if (etAux.getTipoEtapa() == 'a') {

			double distDoisPontos = etAux.getABusca().getDist();
			int numeroVertices = etAux.getABusca().getNumVertices();
			double velo = *iterVelo;
			//Pros vertices eu não consegui, o getVert() já imprime direto na tela, talvez precisemos de um novo
			//método pra pegar os valores dos vértices, se já não tiver um que eu não saiba.

			// Falta adicionar as coordenadas dos vértices
			std::stringstream ssDist;
			ssDist << std::fixed << std::setprecision(2) << distDoisPontos;
			std::string areaLabel = to_string(numeroVertices) + ", " + ssDist.str() + "; ";

			std::string verticesString;
			for (int j = 0; j < numeroVertices; j++) {
				verticesString = etAux.getABusca().getVerticesString(j);
				areaLabel = areaLabel + verticesString;
			}

			areaLabel = areaLabel + " - Área de busca";
			etapas->Append(wxString(areaLabel));

			std::stringstream ssVelo;
			ssVelo << std::fixed << std::setprecision(2) << velo;
			velocidades->Append(wxString(ssVelo.str()));
		}

		else if (etAux.getTipoEtapa() == 'f') {

			double latChegada = etAux.getDestino().getLastPoint().get_latitude();
			double lonChegada = etAux.getDestino().getLastPoint().get_longitude();
			double velo = *iterVelo;

			// Formatar os pontos para duas casas decimais ao invés de seis
			std::stringstream ssLat, ssLon;
			ssLat << std::fixed << std::setprecision(2) << latChegada;
			ssLon << std::fixed << std::setprecision(2) << lonChegada;

			std::string chegadaLabel = "Chegada: " + ssLat.str() + ", " + ssLon.str();

			pontoChegadaText->SetLabel(chegadaLabel);
			pontoChegadaText->Refresh();

		}

		else if (etAux.getTipoEtapa() == 'i') {

			double latPartida = etAux.getOrigem().getInitialPoint().get_latitude();
			double lonPartida = etAux.getOrigem().getInitialPoint().get_longitude();
			double velo = *iterVelo;

			std::stringstream ssLat, ssLon;
			ssLat << std::fixed << std::setprecision(2) << latPartida;
			ssLon << std::fixed << std::setprecision(2) << lonPartida;

			std::string partidaLabel = "Partida: " + ssLat.str() + ", " + ssLon.str();

			pontoPartidaText->SetLabel(partidaLabel);
			pontoPartidaText->Refresh();
		}

		else if (etAux.getTipoEtapa() == 'w') {

			double latPonto = etAux.getWaypoint().get_latitude();
			double lonPonto = etAux.getWaypoint().get_longitude();
			double altPonto = etAux.getWaypoint().get_height();
			double velo = *iterVelo;

			std::stringstream ssLat, ssLon, ssH, ssVelo;
			ssLat << std::fixed << std::setprecision(2) << latPonto;
			ssLon << std::fixed << std::setprecision(2) << lonPonto;
			ssH << std::fixed << std::setprecision(2) << altPonto;
			ssVelo << std::fixed << std::setprecision(2) << velo;

			std::string pontoLabel = ssLat.str() + ", " + ssLon.str() + ", " + ssH.str() + " - Waypoint";
			etapas->Append(wxString(pontoLabel));

			velocidades->Append(wxString(ssVelo.str()));
		}

		cout << endl;
	}
}

// Chamado quando o botão "Mostrar Missão Atual do VANT" é clicado
void MainFrame::CurrentMission(wxCommandEvent& evt)
{
	if (missaoAtual == nullptr) {
		// Exibe um dialog se ocorrer um erro ao exibir a missão (e.g. não há missão para ser carregada)
		wxMessageDialog* noConnectionDialog = new wxMessageDialog(MainWin, wxT("Ocorreu um erro ao exibir a missão. Verifique se realmente há uma missão em andamento"),
			wxT("Erro"), wxOK, wxDefaultPosition);

		noConnectionDialog->ShowModal();
	}
	else {
		ShowMissionDisplay();
		ShowMissionData();
	}
	
	evt.Skip();
}

// Função para mostrar o display da missão. Usado tanto quando carrega missão do disco quanto 
// quando mostra a missão atual
void MainFrame::ShowMissionDisplay()
{
	//Sizer pai
	LoadMissionSizer = new wxBoxSizer(wxVERTICAL);

	//Nome da missão
	wxBoxSizer* nomeSizer = new wxBoxSizer(wxHORIZONTAL);

	nome = new wxStaticText(MainWin, STATICTEXT_NomeMissao, wxT("[Nome da missão vai aqui]"),
		wxPoint(20, 20), wxDefaultSize);

	wxFont fontBold = nome->GetFont();
	fontBold.SetPointSize(12);
	fontBold.SetWeight(wxFONTWEIGHT_BOLD);
	nome->SetFont(fontBold);

	nomeSizer->Add(nome, 0, wxALL, 20);

	//Ponto de partida e chegada
	wxBoxSizer* pontosSizer = new wxBoxSizer(wxHORIZONTAL);

	pontoPartidaText = new wxStaticText(MainWin, STATICTEXT_PontoPartida, wxT("Partida: [lat, long]"),
		wxPoint(20, 90), wxSize(130, 30));

	pontoChegadaText = new wxStaticText(MainWin, STATICTEXT_PontoPartida, wxT("Chegada: [lat, long]"),
		wxPoint(190, 90), wxSize(130, 30));

	/* 
	 * Se quiser deixar o texto maior. Não achei que ficou legal
	 * 
	 * wxFont font = nome->GetFont();
	 * font.SetPointSize(10);
	 *
	 * pontoPartida->SetFont(font);
	 * pontoChegada->SetFont(font);
	 * 
	 */

	pontosSizer->Add(pontoPartidaText, 0, wxALL, 20);
	pontosSizer->Add(pontoChegadaText, 0, wxALL, 20);

	//Titulos das listas de etapas e velocidades
	wxBoxSizer* etapaVeloTitulosSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* etapasTitulo = new wxStaticText(MainWin, wxID_ANY, wxT("Etapas"),
		wxPoint(20, 160), wxSize(400, 30));

	wxStaticText* velocidadesTitulo = new wxStaticText(MainWin, wxID_ANY, wxT("Velocidades"),
		wxPoint(560, 160), wxSize(400, 30));

	etapaVeloTitulosSizer->Add(etapasTitulo, 0, wxLEFT, 20);
	etapaVeloTitulosSizer->Add(velocidadesTitulo, 0, wxLEFT, 20);

	//Listas de etapas e velocidades
	wxBoxSizer* etapaVeloSizer = new wxBoxSizer(wxHORIZONTAL);

	etapas = new wxListBox(MainWin, LISTBOX_EtapasLoad, wxPoint(20, 190), wxSize(500, 120));

	velocidades = new wxListBox(MainWin, LISTBOX_EtapasLoad, wxPoint(560, 190), wxSize(400, 120));

	etapaVeloSizer->Add(etapas, 0, wxLEFT, 20);
	etapaVeloSizer->Add(velocidades, 0, wxLEFT, 20);

	//Botões da parte de baixo
	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

	wxButton* visualizar = new wxButton(MainWin, BUTTON_VisualizarMissao, wxT("Visualizar Missão"), wxPoint(20, 330),
		wxSize(120, 30));

	wxButton* editar = new wxButton(MainWin, BUTTON_EditarMissao, wxT("Editar Missão"), wxPoint(160, 330),
		wxSize(120, 30));

	wxButton* voltar = new wxButton(MainWin, BUTTON_Voltar, wxT("Voltar ao Menu Principal"), wxPoint(320, 330),
		wxSize(200, 30));

	buttonsSizer->Add(visualizar, 0, wxLEFT, 20);
	buttonsSizer->Add(editar, 0, wxLEFT, 20);
	buttonsSizer->Add(voltar, 0, wxLEFT, 20);

	LoadMissionSizer->Add(nomeSizer);
	LoadMissionSizer->Add(pontosSizer);
	LoadMissionSizer->Add(etapaVeloTitulosSizer);
	LoadMissionSizer->Add(etapaVeloSizer);
	LoadMissionSizer->Add(buttonsSizer);

	MainMenuSizer->DeleteWindows();
	MainSizer->Replace(MainMenuSizer, LoadMissionSizer);

	sizerShown = SHOWN_LoadMissionSizer;

}


void MainFrame::ShowMissionEditor() 
{
	// Sizer pai
	CreateMissionSizer = new wxBoxSizer(wxVERTICAL);

	// Nome da missão
	wxBoxSizer* nomeSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* nomeTxt = new wxStaticText(MainWin, wxID_ANY, wxT("Nome da Missão*:"),
		wxPoint(20, 20), wxSize(70, 30));

	nomeCtrl = new wxTextCtrl(MainWin, TEXTCTRL_NomeMissao, wxEmptyString,
		wxPoint(130, 20), wxSize(400, 30));


	nomeSizer->Add(nomeTxt, 0, wxALL, 20);
	nomeSizer->Add(nomeCtrl, 0, wxALL, 20);

	// Posição de partida
	wxBoxSizer* posPartidaSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* posPartidaTxt = new wxStaticText(MainWin, wxID_ANY, wxT("Posição de Partida*:"),
		wxPoint(20, 90), wxSize(70, 30));

	posPartidaCtrl = new wxTextCtrl(MainWin, TEXTCTRL_PosPartida, wxEmptyString,
		wxPoint(130, 90), wxSize(400, 30));

	wxStaticText* posChegadaTxt = new wxStaticText(MainWin, wxID_ANY, wxT("Posição de Chegada:"),
		wxPoint(570, 90), wxSize(70, 30));

	posChegadaCtrl = new wxTextCtrl(MainWin, TEXTCTRL_PosChegada, wxEmptyString,
		wxPoint(660, 90), wxSize(400, 30));

	posPartidaSizer->Add(posPartidaTxt, 0, wxALL, 20);
	posPartidaSizer->Add(posPartidaCtrl, 0, wxALL, 20);
	posPartidaSizer->Add(posChegadaTxt, 0, wxALL, 20);
	posPartidaSizer->Add(posChegadaCtrl, 0, wxALL, 20);

	// Etapas
	wxBoxSizer* adicionarEtapaTopSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* adicionarEtapaTxt = new wxStaticText(MainWin, wxID_ANY, wxT("Adicionar Etapa:"),
		wxPoint(20, 160), wxSize(70, 30));

	adicionarEtapaCtrl = new wxTextCtrl(MainWin, TEXTCTRL_AdicionarEtapa, wxEmptyString,
		wxPoint(130, 160), wxSize(400, 30));

	//Mudar isso aqui para dizer o index correspondente. Desse jeito funciona, mas é melhor 'consertar' para o código ficar mais claro para quem estiver lendo
	wxArrayString choices = wxArrayString();
	choices.Insert(wxT("Área de busca"), 0, 1);
	choices.Insert(wxT("Waypoint"), 0, 1);

	etapaRadioBox = new wxRadioBox(MainWin, RADIOBOX_Etapa, wxT("Qual tipo de etapa?"),
		wxPoint(570, 160), wxDefaultSize, choices, 0, wxRA_SPECIFY_ROWS, wxDefaultValidator, 
		wxT("Tipo de Etapa"));

	adicionarEtapaTopSizer->Add(adicionarEtapaTxt, 0, wxALL, 20);
	adicionarEtapaTopSizer->Add(adicionarEtapaCtrl, 0, wxALL, 20);
	adicionarEtapaTopSizer->Add(etapaRadioBox, 0, wxLEFT, 20);

	wxBoxSizer* adicionarEtapaBotSizer = new wxBoxSizer(wxVERTICAL);

	adicionarEtapaBtn = new wxButton(MainWin, BUTTON_AdicionarEtapa, wxT("Adicionar"),
		wxPoint(130, 210), wxSize(70, 30));

	etapasListBox = new wxListBox(MainWin, LISTBOX_Etapas, wxPoint(130, 250),
		wxSize(400, 120));

	//Conectar a list box com um evento de clique de botão direito para permitir a ediçaõ do campo
	etapasListBox->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MainFrame::EditarEtapa), NULL, this);

	adicionarEtapaBotSizer->Add(adicionarEtapaBtn);
	adicionarEtapaBotSizer->Add(etapasListBox, 0, wxTOP, 10);


	// Velocidades 
	wxBoxSizer* velocidadesTopSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* velocidadesTxt = new wxStaticText(MainWin, wxID_ANY, wxT("Lista de velocidades:"),
		wxPoint(20, 400), wxSize(70, 30));

	adicionarVelocidadeCtrl = new wxTextCtrl(MainWin, TEXTCTRL_AdicionarEtapa, wxEmptyString,
		wxPoint(130, 400), wxSize(400, 30));

	velocidadesTopSizer->Add(velocidadesTxt, 0, wxALL, 20);
	velocidadesTopSizer->Add(adicionarVelocidadeCtrl, 0, wxALL, 20);

	wxBoxSizer* velocidadeBotSizer = new wxBoxSizer(wxVERTICAL);

	adicionarVelocidadeBtn = new wxButton(MainWin, BUTTON_AdicionarVelocidade, wxT("Adicionar"),
		wxPoint(130, 440), wxSize(70, 30));

	velocidadesListBox = new wxListBox(MainWin, LISTBOX_Velocidades, wxPoint(130, 480),
		wxSize(400, 120));

	velocidadeBotSizer->Add(adicionarVelocidadeBtn);
	velocidadeBotSizer->Add(velocidadesListBox, 0, wxTOP, 10);


	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

	wxButton* salvarMissao = new wxButton(MainWin, BUTTON_SalvarMissao, wxT("Salvar Missão"),
		wxPoint(20, 620), wxSize(120, 30));

	wxButton* enviarMissao = new wxButton(MainWin, BUTTON_EnviarMissao, wxT("Enviar Missão para o VANT"),
		wxPoint(160, 620), wxSize(300, 30));

	wxButton* BtnVoltar = new wxButton(MainWin, BUTTON_Voltar, "Voltar ao Menu Principal",
		wxPoint(480, 620), wxSize(200, 30));


	buttonsSizer->Add(salvarMissao, 0, wxALL, 20);
	buttonsSizer->Add(enviarMissao, 0, wxALL, 20);
	buttonsSizer->Add(BtnVoltar, 0, wxALL, 20);

	CreateMissionSizer->Add(nomeSizer);
	CreateMissionSizer->Add(posPartidaSizer);
	CreateMissionSizer->Add(adicionarEtapaTopSizer);
	CreateMissionSizer->Add(adicionarEtapaBotSizer, 0, wxLEFT, 130);
	CreateMissionSizer->Add(velocidadesTopSizer, 0, wxTOP, 10);
	CreateMissionSizer->Add(velocidadeBotSizer, 0, wxLEFT, 130);
	CreateMissionSizer->Add(buttonsSizer);

	if (sizerShown == SHOWN_LoadMissionSizer) {
		// Veio pelo botão de "Editar Missão" 
		LoadMissionSizer->DeleteWindows();
		MainSizer->Replace(LoadMissionSizer, CreateMissionSizer);

	}
	else {
		// Veio pelo botão de "Criar Missão"
		MainMenuSizer->DeleteWindows();
		MainSizer->Replace(MainMenuSizer, CreateMissionSizer);
	}

	sizerShown = SHOWN_CreateMissionSizer;
}

void MainFrame::EditMission(wxCommandEvent &evt) {
	// Mostrar a interface do editor
	ShowMissionEditor();

	// Carregar os dados da missão para os componentes no editor
	list<Etapa>::iterator iterEtapa;
	list<double>::iterator iterVelo;

	nomeCtrl->ChangeValue(missaoAtual->getNomeMissao());
	
	//Esse laço é o que percorre a lista de etapas, imprimindo tudo
	for (iterEtapa = missaoAtual->etapas.begin(), iterVelo = missaoAtual->velocidades.begin();
		iterEtapa != missaoAtual->etapas.end(), iterVelo != missaoAtual->velocidades.end(); iterEtapa++, iterVelo++) {

		Etapa etAux = *iterEtapa;

		//LAÇO PARA DIZER QUAL O TIPO
		if (etAux.getTipoEtapa() == 'a') {

			double distDoisPontos = etAux.getABusca().getDist();
			int numeroVertices = etAux.getABusca().getNumVertices();
			double velo = *iterVelo;
			//Pros vertices eu não consegui, o getVert() já imprime direto na tela, talvez precisemos de um novo
			//método pra pegar os valores dos vértices, se já não tiver um que eu não saiba.

			// Falta adicionar as coordenadas dos vértices
			std::stringstream ssDist;
			ssDist << std::fixed << std::setprecision(2) << distDoisPontos;
			std::string areaLabel = to_string(numeroVertices) + ", " + ssDist.str() + "; ";

			std::string verticesString;
			for (int j = 0; j < numeroVertices; j++) {
				verticesString = etAux.getABusca().getVerticesString(j);
				areaLabel = areaLabel + verticesString;
			}

			areaLabel = areaLabel + " - Área de busca";
			etapasListBox->Append(wxString(areaLabel));

			std::stringstream ssVelo;
			ssVelo << std::fixed << std::setprecision(2) << velo;
			velocidadesListBox->Append(wxString(ssVelo.str()));
		}

		else if (etAux.getTipoEtapa() == 'f') {

			double latChegada = etAux.getDestino().getLastPoint().get_latitude();
			double lonChegada = etAux.getDestino().getLastPoint().get_longitude();
			double velo = *iterVelo;

			// Formatar os pontos para duas casas decimais ao invés de seis
			std::stringstream ssLat, ssLon;
			ssLat << std::fixed << std::setprecision(2) << latChegada;
			ssLon << std::fixed << std::setprecision(2) << lonChegada;

			std::string chegadaLabel = "Chegada: " + ssLat.str() + ", " + ssLon.str();

			posChegadaCtrl->SetLabel(chegadaLabel);

		}

		else if (etAux.getTipoEtapa() == 'i') {

			double latPartida = etAux.getOrigem().getInitialPoint().get_latitude();
			double lonPartida = etAux.getOrigem().getInitialPoint().get_longitude();
			double velo = *iterVelo;

			std::stringstream ssLat, ssLon;
			ssLat << std::fixed << std::setprecision(2) << latPartida;
			ssLon << std::fixed << std::setprecision(2) << lonPartida;

			std::string partidaLabel = "Partida: " + ssLat.str() + ", " + ssLon.str();

			posPartidaCtrl->SetLabel(partidaLabel);
		}

		else if (etAux.getTipoEtapa() == 'w') {

			double latPonto = etAux.getWaypoint().get_latitude();
			double lonPonto = etAux.getWaypoint().get_longitude();
			double altPonto = etAux.getWaypoint().get_height();
			double velo = *iterVelo;

			std::stringstream ssLat, ssLon, ssH, ssVelo;
			ssLat << std::fixed << std::setprecision(2) << latPonto;
			ssLon << std::fixed << std::setprecision(2) << lonPonto;
			ssH << std::fixed << std::setprecision(2) << altPonto;
			ssVelo << std::fixed << std::setprecision(2) << velo;

			std::string pontoLabel = ssLat.str() + ", " + ssLon.str() + ", " + ssH.str() + " - Waypoint";
			etapasListBox->Append(wxString(pontoLabel));

			velocidadesListBox->Append(wxString(ssVelo.str()));
		}

		cout << endl;
	}
}

void MainFrame::ShowRota(wxCommandEvent& evt)
{
	// AllocConsole();
	// freopen("CONOUT$", "w", stdout);
	// freopen("CONOUT$", "w", stderr);

	int posicao = etapas->GetSelection();

	list<Etapa>::iterator iter;
	iter = missaoAtual->etapas.begin();
	
	for (int i = 0; i <= posicao; i++) {
		iter++;
	}
	
	Etapa et = *iter;
	// et.getABusca().pontosDaRota();
}

void MainFrame::AdicionarEtapa(wxCommandEvent& evt)
{
	if (etapaRadioBox->GetSelection() == 0) {
		std::string input = std::string((adicionarEtapaCtrl->GetValue()).mb_str());
		if (validateStringWaypoint(input) == 0) {
			etapasListBox->AppendString(adicionarEtapaCtrl->GetValue() + " - Waypoint");

		}
		else if (validateStringWaypoint(input) == 1){
			//Dividir a string para achar a posição e adicionar na posição correspondente
			std::string delimeter = "; ";
			size_t pos = input.find(delimeter);
			std::string substring[2] = { input.substr(0, pos), input.substr(pos + delimeter.length(), input.length() - 1) };

			unsigned int posicao = stoi(substring[1]);

			etapasListBox->Insert(substring[0] + " - Waypoint", posicao);

		}
		else {
			wxMessageDialog* erroValidacaoDialog = new wxMessageDialog(MainWin, wxT("Erro na validação do waypoint inserido."),
				wxT("Erro na validação do campo"), wxOK, wxDefaultPosition);

			if (erroValidacaoDialog->ShowModal() == wxID_OK)
			{
				erroValidacaoDialog->Destroy();
			}
		}
	}
	else {
		std::string input = std::string((adicionarEtapaCtrl->GetValue()).mb_str());
		if (validateStringArea(input) == 0) {
			etapasListBox->AppendString(adicionarEtapaCtrl->GetValue() + " - Área de busca");
		}
		else if (validateStringArea(input) == 1) {
			//Dividir a string para achar a posicao e etc
			std::string delimeter = "; ";
			std::string substring[3];
			size_t pos = 0;
			for (int i = 0; (pos = input.find(delimeter)) != std::string::npos || i < 3; i++) {
				substring[i] = input.substr(0, pos);
				input.erase(0, pos + delimeter.length());
			}

			unsigned int posicao = stoi(substring[1]);

			etapasListBox->Insert(substring[0] + "; " + substring[2] + " - Área de busca", posicao);
		}
		else {
			wxMessageDialog* erroValidacaoDialog = new wxMessageDialog(MainWin, wxT("Erro na validação da área de busca inserida."),
				wxT("Erro na validação do campo"), wxOK, wxDefaultPosition);

			if (erroValidacaoDialog->ShowModal() == wxID_OK)
			{
				erroValidacaoDialog->Destroy();
			}
		}
	}

	evt.Skip();
}

void MainFrame::RemoverEtapa(wxCommandEvent& evt) 
{
	int index = etapasListBox->GetSelection();
	wxString dialogMessage;
	dialogMessage = wxString::Format(wxT("Desejar remover a %iª etapa? "), (index + 1));
	wxMessageDialog* removerEtapaDialog = new wxMessageDialog(MainWin, dialogMessage,
		wxT("Remover etapa"), wxOK|wxCANCEL, wxDefaultPosition);

	if (removerEtapaDialog->ShowModal() == wxID_OK)
	{
		etapasListBox->Delete(index);
	} 
	
	removerEtapaDialog->Destroy();

	evt.Skip();
}

void MainFrame::EditarEtapa(wxMouseEvent& evt) {

	//Pegar o index do item selecionado
	unsigned int position = etapasListBox->HitTest(evt.GetPosition());

	wxString valorAnterior;
	//Pegar o valor anterior do campo
	if (position != wxNOT_FOUND) {
		valorAnterior = etapasListBox->GetString(position);
	}
	else {
		//Ocorreu um problema; não teve clique ali
		return;
	}

	//Exibir o dialog com a caixa de texto para edição
	wxTextEntryDialog* dialog = new wxTextEntryDialog(this, wxT("Insira o novo valor da etapa"), wxT("Editar etapa"), 
		valorAnterior, wxOK | wxCANCEL, wxDefaultPosition);

	if (dialog->ShowModal() == wxID_OK) {
		std::string input = std::string((dialog->GetValue()).mb_str());
		size_t pos = input.find(" - Way");	//Só "way" pra ser mais fácil de editar área de busca pra waypoint
		std::string substring = input.substr(0, pos);
		
		//Valida o ponto inserido para evitar erros
		if (validateStringWaypoint(substring) == 0) {
			//Finalmente edita o valor
			wxString novoValor = wxString(substring) + wxString(" - Waypoint");
			etapasListBox->Insert(novoValor, position);
			etapasListBox->Delete(position + 1);
		}
		else {
			//A validação não foi bem sucedida; ou tem erro de digitação ou é uma área de busca
			pos = input.find(" - Área");	//Só "área" pra ser mais fácil de editar waypoint pra área de busca
			substring = input.substr(0, pos);
			
			//Valida para ver se é área de busca ou tem um erro
			if (validateStringArea(substring) == 0) {
				//Finalmente edita o valor
				wxString novoValor = wxString(substring) + wxString(" - Área de busca");
				etapasListBox->Insert(novoValor, position);
				etapasListBox->Delete(position + 1);
			}
			else {
				//Teve um erro de digitação
				wxMessageDialog* dialog = new wxMessageDialog(MainWin, wxT("Ocorreu um erro ao validar o valor inserido"),
					wxT("Erro na validação do campo"), wxOK, wxDefaultPosition);

				dialog->ShowModal();
			}
		}
		
	}
	
	dialog->Destroy();

	evt.Skip();
}

void MainFrame::AdicionarVelocidade(wxCommandEvent& evt)
{
	std::string input = std::string((adicionarVelocidadeCtrl->GetValue()).mb_str());

	if (validateStringVelocidade(input) == -1) {
		wxMessageDialog* erroDialog = new wxMessageDialog(MainWin, wxT("Houve um erro de digitação ao inserir a velocidade."),
			wxT("Erro na validação"), wxOK, wxDefaultPosition);

		erroDialog->ShowModal();
	}
	else if (validateStringVelocidade(input) == 0) {
		//Simplesmente adiciona a velocidade ao fim da lista
		velocidadesListBox->AppendString(adicionarVelocidadeCtrl->GetValue());
	}
	else if (validateStringVelocidade(input) == 1) {
		//Pega o número de itens da lista para verificar que a posição dada é válida
		int max = velocidadesListBox->GetCount();

		//Separa a string para pegar as substrings velocidade e a posição
		std::string delimeter = ", ";
		std::string substring[2];
		size_t pos = 0;
		for (int i = 0; (pos = input.find(delimeter)) != std::string::npos || i < 2; i++) {
			substring[i] = input.substr(0, pos);
			input.erase(0, pos + delimeter.length());
		}
		unsigned int posicao = stoi(substring[1]);

		//Verifica se a posição dada é valida; exibe um dialog se não for
		if (posicao > max) {
			wxMessageDialog* posicaoInvalidaDialog = new wxMessageDialog(MainWin, wxT("A posição inserida é maior que o tamanho atual da lista."),
				wxT("Posição inválida"), wxOK, wxDefaultPosition);

			posicaoInvalidaDialog->ShowModal();
		}
		else {
			//Precisa converter a velocidade para wxString novamente a fim de adicioná-la à ListBox
			wxString velocidadeStr(substring[0]);

			velocidadesListBox->Insert(velocidadeStr, posicao);
		}
	}
	else if (validateStringVelocidade(input) == 2) {
		//Pega o número de itens da lista para verificar que a posição dada é válida
		int max = velocidadesListBox->GetCount();

		//Separa a string para pegar as substrings velocidade e a posição
		std::string delimeter = ", ";
		std::string substring[3];
		size_t pos = 0;
		for (int i = 0; (pos = input.find(delimeter)) != std::string::npos || i < 3; i++) {
			substring[i] = input.substr(0, pos);
			input.erase(0, pos + delimeter.length());
		}
		unsigned int posicao = stoi(substring[1]);

		//Verifica se a posição dada é valida; exibe um dialog se não for
		if (posicao > max) {
			wxMessageDialog* posicaoInvalidaDialog = new wxMessageDialog(MainWin, wxT("A posição inserida é maior que o tamanho atual da lista."),
				wxT("Posição inválida"), wxOK, wxDefaultPosition);

			posicaoInvalidaDialog->ShowModal();
		}
		else {
			
			wxArrayString velocidadeArray = wxArrayString();
			wxString velocidadeStr(substring[0]);
			unsigned int n = stoi(substring[2]);
			
			//Cria um array de n cópias da velocidade inserida
			velocidadeArray.Insert(velocidadeStr, 0, n);

			//Adiciona a array na posição dada
			velocidadesListBox->Insert(velocidadeArray, posicao);
		}
	}
	else if (validateStringVelocidade(input) == 3) {
		//Separa a string para pegar as substrings velocidade e a posição
		std::string delimeter = ", ";
		std::string substring[3];
		size_t pos = 0;
		for (int i = 0; (pos = input.find(delimeter)) != std::string::npos || i < 3; i++) {
			substring[i] = input.substr(0, pos);
			input.erase(0, pos + delimeter.length());
		}
		
		wxArrayString velocidadeArray = wxArrayString();
		wxString velocidadeStr(substring[0]);
		unsigned int n = stoi(substring[2]);

		//Cria um array de n cópias da velocidade inserida
		velocidadeArray.Insert(velocidadeStr, 0, n);

		//Adiciona a array no final da lista
		velocidadesListBox->Append(velocidadeArray);
	}
	
	evt.Skip();
}

void MainFrame::RemoverVelocidade(wxCommandEvent& evt)
{
	int index = velocidadesListBox->GetSelection();
	wxString dialogMessage;
	dialogMessage = wxString::Format(wxT("Desejar remover a velocidade na posição %i? "), 
		(index + 1));

	wxMessageDialog* removerVelocidadeDialog = new wxMessageDialog(MainWin, dialogMessage,
		wxT("Remover velocidade"), wxOK | wxCANCEL, wxDefaultPosition);

	if (removerVelocidadeDialog->ShowModal() == wxID_OK)
	{
		velocidadesListBox->Delete(index);
	}

	removerVelocidadeDialog->Destroy();

	evt.Skip();
}


void MainFrame::SalvarMissao(wxCommandEvent& evt)
{
	int flagError = IniciarMissao();
	
	if (flagError == 1) {
		wxMessageDialog* erroValidacaoDialog = new wxMessageDialog(MainWin, wxT("Erro no campo \"Posição de Partida\"."),
			wxT("Erro na validação do campo"), wxOK, wxDefaultPosition);

		if (erroValidacaoDialog->ShowModal() == wxID_OK)
		{
			erroValidacaoDialog->Destroy();
		}
	}
	else if (flagError == 2) {
		wxMessageDialog* erroValidacaoDialog = new wxMessageDialog(MainWin, wxT("Erro no campo \"Posição de Chegada\"."),
			wxT("Erro na validação do campo"), wxOK, wxDefaultPosition);

		if (erroValidacaoDialog->ShowModal() == wxID_OK)
		{
			erroValidacaoDialog->Destroy();
		}
	}
	else if (flagError == 3) {
		wxMessageDialog* erroValidacaoDialog = new wxMessageDialog(MainWin, wxT("Algum valor está acima do limite."),
			wxT("Erro na validação do campo"), wxOK, wxDefaultPosition);

		if (erroValidacaoDialog->ShowModal() == wxID_OK)
		{
			erroValidacaoDialog->Destroy();
		}
	}
	else if (flagError == 4) {
		wxMessageDialog* erroValidacaoDialog = new wxMessageDialog(MainWin, wxT("As listas de etapas e velocidades têm tamanhos diferentes."),
			wxT("Erro ao associar etapa e velocidade"), wxOK, wxDefaultPosition);

		if (erroValidacaoDialog->ShowModal() == wxID_OK)
		{
			erroValidacaoDialog->Destroy();
		}
	}
	else if (flagError == 5) {
		wxMessageDialog* erroValidacaoDialog = new wxMessageDialog(MainWin, wxT("A quantidade de vértices (x, y) inseridos não corresponde ao número de vértices informado"),
			wxT("Erro ao criar área de busca"), wxOK, wxDefaultPosition);

		if (erroValidacaoDialog->ShowModal() == wxID_OK)
		{
			erroValidacaoDialog->Destroy();
		}
	}
	else if (flagError == 0) {
		//Um dialog só para confirmar que quer salvar a missão agora
		wxMessageDialog* confirmacaoDialog = new wxMessageDialog(MainWin, wxT("Deseja salvar a missão agora?"), wxT("Confirmação"),
			wxOK | wxCANCEL, wxDefaultPosition);
		
		if (confirmacaoDialog->ShowModal() == wxID_OK) {
			confirmacaoDialog->Destroy();

			//Salvar missão no disco usando JSON
			wxFileDialog* salvarMissaoDialog = new wxFileDialog(MainWin, wxT("Salvar missão"), wxEmptyString, wxEmptyString,
				wxT("Arquivo JSON (*.json)|*.json"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
			
			if (salvarMissaoDialog->ShowModal() == wxID_OK) {

				MissionPath = salvarMissaoDialog->GetPath();
				std::string path = std::string(MissionPath.mb_str());

				missaoAtual->setEnderecoJsonOut(path);
				json j;
				missaoAtual->missaoToJson(j);

				missaoSalva = true;
			}

			salvarMissaoDialog->Destroy();
		}
	}
	else if (flagError == -1) {
		wxMessageDialog* erroDeconhecidoDialog = new wxMessageDialog(MainWin, wxT("Ocorreu um erro desconhecido."),
			wxT("Erro desconhecido"), wxOK, wxDefaultPosition);

		if (erroDeconhecidoDialog->ShowModal() == wxID_OK)
		{
			erroDeconhecidoDialog->Destroy();
		}
	}
	else {
		//Não inseriu um campo obrigatório. Não precisa fazer nada
	}
	
}


int MainFrame::IniciarMissao()
{	
	if (nomeCtrl->IsEmpty()) 
	{
		wxMessageDialog* noNameDialog = new wxMessageDialog(MainWin, wxT("Por favor, insira o nome da missão"),
			wxT("Campo obrigatório"), wxOK, wxDefaultPosition);

		noNameDialog->ShowModal();
	
		noNameDialog->Destroy();

		return 5;
	}
	else 
	{
		if (posPartidaCtrl->IsEmpty())
		{
			wxMessageDialog* noPartidaDialog = new wxMessageDialog(MainWin, wxT("Por favor, insira o ponto de partida"),
				wxT("Campo obrigatório"), wxOK, wxDefaultPosition);

			noPartidaDialog->ShowModal();
		
			noPartidaDialog->Destroy();

			return 5;
		}
		else
		{
			if ((etapasListBox->GetCount()) != (velocidadesListBox->GetCount())) {
				return 4;
			}

			string nome = string((nomeCtrl->GetValue()).mb_str());
			missaoAtual = new Missao(nome);


			double lat, lon;

			// Texto inteiro retirado da caixa de texto
			std::string input = std::string((posPartidaCtrl->GetValue()).mb_str());
			size_t pos = 0;

			// Delimitadores para recortar as strings das caixas de texto

			std::string delimeter1 = "; ";
			std::string delimeter2 = ", ";
			std::string delimeter3 = " -";

			// Mostrar o terminal
			// AllocConsole();
			// freopen("CONOUT$", "w", stdout);
			// freopen("CONOUT$", "w", stderr);


			//Valida para evitar typos
			if (validateString(input, regPosicao) == false) {
				return 1;
			}

			std::string substring[2];
			double dataPartida[2], dataChegada[2], dataApproxPartida[3], dataApproxChegada[3];

			//Separa o ponto inicial e o ponto de aproximação
			for (int i = 0; (pos = input.find(delimeter1)) != std::string::npos || i < 2; i++) {
				substring[i] = input.substr(0, pos);
				input.erase(0, pos + delimeter1.length());
				std::cout << "Substring " << i << " " << substring[i] << std::endl;
			}

			//Recorta a latitude e longitude do ponto inicial
			for (int i = 0; (pos = substring[0].find(delimeter2)) != std::string::npos || i < 2; i++) {
				std::string substring2 = substring[0].substr(0, pos);
				dataPartida[i] = stod(substring2);
				substring[0].erase(0, pos + delimeter2.length());
				std::cout << "Partida " << dataPartida[i] << std::endl;

			}

			//Retornar erro se a latitude ou longitude passarem do limite
			if (dataPartida[0] > 90 || dataPartida[1] > 180) {
				return 3;
			}


			//Recorta a latitude, longitude e altura do ponto de aproximação
			for (int i = 0; (pos = substring[1].find(delimeter2)) != std::string::npos || i < 3; i++) {
				std::string substring2 = substring[1].substr(0, pos);
				dataApproxPartida[i] = stod(substring2);
				substring[1].erase(0, pos + delimeter2.length());
				std::cout << "Aprox Partida " << dataApproxPartida[i] << std::endl;
			}

			//Retorna erro se latitude, longitude ou altura estiverem acima do limite
			if (dataApproxPartida[0] > 90 || dataApproxPartida[1] > 180 || dataApproxPartida[2] > 1000) {
				return 3;
			}

			PontoPartida pp = PontoPartida(dataPartida[0], dataPartida[1]);
			pp.setApproxPoint(dataApproxPartida[0], dataApproxPartida[1], dataApproxPartida[2]);

			if (posChegadaCtrl->GetValue() != wxEmptyString) {
				input = std::string((posChegadaCtrl->GetValue()).mb_str());

				pos = input.find(delimeter3);
				input = input.substr(0, pos);

				//Retorna erro se o formato da string estiver errado
				if (validateString(input, regPosicao) == false) {
					return 2;
				}

				//Recorta os dados do ponto de chegada e de aproximação da chegada
				for (int i = 0; (pos = input.find(delimeter1)) != std::string::npos || i < 2; i++) {
					substring[i] = input.substr(0, pos);
					input.erase(0, pos + delimeter1.length());
					std::cout << "Substring " << i << " " << substring[i] << std::endl;
				}

				//Recorta os valores da latitude, longitude e altura do ponto de chegada
				for (int i = 0; (pos = substring[0].find(delimeter2)) != std::string::npos || i < 2; i++) {
					std::string substring2 = substring[0].substr(0, pos);
					dataChegada[i] = stod(substring2);
					substring[0].erase(0, pos + delimeter2.length());
					std::cout << "Chegada " << dataChegada[i] << std::endl;
				}

				//Retorna erro se a latitude ou longitude do ponto de chegade estiverem acima do limite
				if (dataChegada[0] > 90 || dataChegada[1] > 180) {
					return 3;
				}

				//Recorta os valores de latitude, longitude e altura do ponto de aproximação
				for (int i = 0; (pos = substring[1].find(delimeter2)) != std::string::npos || i < 3; i++) {
					std::string substring2 = substring[1].substr(0, pos);
					dataApproxChegada[i] = stod(substring2);
					substring[1].erase(0, pos + delimeter2.length());
					std::cout << "Aprox chegada " << dataApproxChegada[i] << std::endl;
				}

				//Retorna erro se a latitude, longitude ou altura do ponto de aproximação estiverem acima do limite
				if (dataApproxChegada[0] > 90 || dataApproxChegada[1] > 180 || dataApproxChegada[2] > 1000) {
					return 3;
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					dataChegada[i] = -200;
				}

				for (int i = 0; i < 3; i++) {
					dataApproxChegada[i] = -200;
				}
			}

			PontoChegada pc = PontoChegada(dataChegada[0], dataChegada[1]);
			pc.setApproxPoint(dataApproxChegada[0], dataApproxChegada[1], dataApproxChegada[2]);

			// Etapa eP = Etapa(pp); -> trocou addEtapa(0) para inicializaMissao
			missaoAtual->inicializaMissao(pp);

			int etapas = etapasListBox->GetCount();
			for (int i = 0; i < etapas; i++) {
				int selected;

				std::cout << "i: " << i << endl;

				Etapa e;
				unsigned int j = i;
				input = etapasListBox->GetString(j);

				pos = input.find(delimeter3);
				std::cout << input.substr(pos, input.length() - 1) << endl;

				//Tira o " - Waypoint" ou  " - Área de busca" do input
				if (input.substr(pos, input.length() - 1) == " - Waypoint") {
					selected = WAYPOINT;
				}
				else {
					selected = AREA_DE_BUSCA;
				}

				input = input.substr(0, pos);

				std::cout << "input: " << input << endl;

				if (selected == WAYPOINT) {

					Point point;
					double pointData[3];
					std::string substringPoint[3];
					for (int i = 0; (pos = input.find(delimeter2)) != std::string::npos || i < 3; i++) {
						substringPoint[i] = input.substr(0, pos);
						pointData[i] = stod(substringPoint[i]);
						input.erase(0, pos + delimeter2.length());
						std::cout << "Etapa P" << i << " " << substringPoint[i] << std::endl;
					}

					point = Point(pointData[0], pointData[1], pointData[2]);
					e = Etapa(point);
				}
				else {

					Busca busca = Busca();
					std::string substringBusca[2];

					for (int i = 0; (pos = input.find(delimeter1)) != std::string::npos || i < 2; i++) {
						substringBusca[i] = input.substr(0, pos);
						input.erase(0, pos + delimeter1.length());
						std::cout << "Substring A " << i << ": " << substringBusca[i] << std::endl;
					}

					// buscaData[0] é o número de vértices; buscaData[1] é a distancia
					double buscaData[2];
					std::string substringArea[2];
					for (int i = 0; (pos = substringBusca[0].find(delimeter2)) != std::string::npos || i < 2; i++) {
						substringArea[i] = substringBusca[0].substr(0, pos);
						buscaData[i] = stod(substringArea[i]);
						substringBusca[0].erase(0, pos + delimeter2.length());
						std::cout << "Etapa A " << i << ": " << buscaData[i] << std::endl;
					}

					int n = buscaData[0];
					std::string substringVertices[1000];
					Point* verticesData[1000];
					double maxy = INT_MIN;

					busca.setNumVert(buscaData[0]);
					busca.setDist(buscaData[1]);

					for (int i = 0; (pos = substringBusca[1].find(delimeter2)) != std::string::npos || i < n*2; i += 2) {
						
						// Se a quantidade de vértices informados não corresponderem ao número de vértices n, 
						// uma exceção seria lançada. O try/catch evita o fechamento do programa
						try {
							substringVertices[i] = substringBusca[1].substr(0, pos);
							double x = stod(substringVertices[i]);
							substringBusca[1].erase(0, pos + delimeter2.length());

							substringVertices[i + 1] = substringBusca[1].substr(0, pos);
							double y = stod(substringVertices[i + 1]);
							substringBusca[1].erase(0, pos + delimeter2.length());

							if (y > maxy) {
								maxy = y;
							}

							std::cout << "x" << i / 2 << " " << x << ", y" << i / 2 << " " << y << std::endl;

							busca.setListaVertices(x, y, i/2);
						}
						catch (...) {
							// Seria bom fazer um catch especifico e usar esse mais geral para retornar erro desconhecido
							// mas não sei qual exceção usar ainda =(
							return 5;
						}
					}

					busca.setyMax(maxy);
					// busca.getVert();
					
					e = Etapa(busca);

				}
			
				try {
					double velocidade = stod(string((velocidadesListBox->GetString(j)).mb_str()));
					missaoAtual->addEtapa(e, i, velocidade);

				}
				catch (...) {
					double velocidade = stod(string((velocidadesListBox->GetString(j - 1)).mb_str()));
					missaoAtual->addEtapa(e, i, velocidade);

				}
			}

			//Etapa eC = Etapa(pc); -> trocou addEtapa(pc) por finalizaMissao
			missaoAtual->finalizaMissao(pc);

		}
	}

	//Tudo correu bem!
	return 0;
}


void MainFrame::EnviarMissao(wxCommandEvent& evt)
{
	if (missaoSalva == true) {

		if (vantConnected == true) {

			// Enviar missão para o vant conectado

		}
		else 
		{
			wxMessageDialog* noConnectionDialog = new wxMessageDialog(MainWin, wxT("Nenhum VANT conectado no momento"),
				wxT("Sem conexão"), wxOK, wxDefaultPosition);

			if (noConnectionDialog->ShowModal())
			{
				noConnectionDialog->Destroy();

			}	
		}
	} 
	else
	{
		wxMessageDialog* removerVelocidadeDialog = new wxMessageDialog(MainWin, wxT("A missão ainda não foi salva. Deseja continuar?"),
			wxT("Enviar missão"), wxYES | wxNO, wxDefaultPosition);

		if (removerVelocidadeDialog->ShowModal() == wxYES)
		{
			if (vantConnected == true) {

				// Enviar missão para o vant conectado

			}
			else
			{
				wxMessageDialog* noConnectionDialog = new wxMessageDialog(MainWin, wxT("Nenhum VANT conectado no momento"),
					wxT("Sem conexão"), wxOK, wxDefaultPosition);

				if (noConnectionDialog->ShowModal() == wxID_OK) 
				{
					noConnectionDialog->Destroy();

				}
			}
		}
	}
}

void MainFrame::ConfigureAirframe(wxCommandEvent& evt)
{
	evt.Skip();
}

bool MainFrame::validateString(std::string str, std::regex reg) {
	//Aqui provavelmente vale a pena apenas ver se é valida ou não (usando reg_match) ao invés se salvar o match. Precisa avaliar

	//Usado para salvar as string que batem
	std::smatch matches;

	std::regex_search(str, matches, reg);

	//Retorna true se não estiver vazio, ou seja, se é válido
	return !matches.empty();
}

int MainFrame::validateStringWaypoint(std::string str) {

	if (std::regex_match(str, regPoint)) {
		return 0;
	}
	else if (std::regex_match(str, regPointPos)) {
		return 1;
	}
	else {
		return -1;
	}
}

int MainFrame::validateStringArea(std::string str) {
	if (std::regex_match(str, regArea)) {
		return 0;
	}
	else if (std::regex_match(str, regAreaPos)) {
		return 1;
	}
	else {
		return -1;
	}
}


int MainFrame::validateStringVelocidade(std::string str) {
	//Aqui provavelmente vale a pena apenas ver se é valida ou não ao invés se salvar o match. Precisa avaliar

	//Usado para salvar as string que batem
	std::smatch matches;

	std:regex reg[4] = { regVelocidade, regVeloPosicao, regVeloPosRepet, regVeloRepeticao };

	for (int i = 0; i < 4; i++) {
		if (std::regex_match(str, reg[i])) {
			return i;
		}
	}
	
	//Retorna -1 se não for validado em nenhum
	return -1;
}


IMPLEMENT_APP(MainApp);

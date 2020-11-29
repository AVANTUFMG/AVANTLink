#pragma once

#include "wx/wx.h"
#include "wx/sizer.h"

#include <regex>


class MainApp : public wxApp    //A classe da aplicação propriamente dita
{
public:
	virtual bool OnInit();	//Chamada quando incia a aplicação

};

class MainFrame : public wxFrame	//A classe inicial da janela e componentes. Contida na MainApp
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	wxScrolledWindow* scrolledWindow;

	//Salva o path do arquivo da missão no disco
	wxString MissionPath;

	//Botões menu principal
	wxButton* BtnVoltar;
	wxButton* BtnConnectVant;
	wxButton* BtnTelemetry;
	wxButton* BtnCreateMission;
	wxButton* BtnLoadMission;
	wxButton* BtnConfigureAirframe;
	wxButton* BtnCurrentMission;


	//Botões de "Conectar a um VANT"
	wxButton* BtnCurrentConnection;
	wxButton* BtnNewConnection;

	// Itens de "Criar Missão"
	wxTextCtrl* adicionarEtapaCtrl;
	wxButton* adicionarEtapaBtn;
	wxListBox* etapasListBox;
	wxTextCtrl* adicionarVelocidadeCtrl;
	wxButton* adicionarVelocidadeBtn;
	wxListBox* velocidadesListBox;
	wxRadioBox* etapaRadioBox;

	//Itens de "Carregar Missão"
	wxStaticText* nome;
	wxStaticText* pontoPartidaText;
	wxStaticText* pontoChegadaText;
	wxListBox* etapas;
	wxListBox* velocidades;

	//Métodos chamados pelos itens do menu
	void ShowMainMenu();
	void Voltar(wxCommandEvent& evt);
	void ConnectToVant(wxCommandEvent &evt);
	void ViewTelemetry(wxCommandEvent& evt);
	void CreateMission(wxCommandEvent& evt);
	void LoadMission(wxCommandEvent& evt);
	void CurrentMission(wxCommandEvent& evt);
	void ShowMissionDisplay();
	void ShowMissionEditor();
	void ShowRota(wxCommandEvent& evt);
	void ConfigureAirframe(wxCommandEvent& evt);

	// Parte de criar missão	
	void AdicionarEtapa(wxCommandEvent& evt);
	void RemoverEtapa(wxCommandEvent& evt);
	void EditarEtapa(wxMouseEvent& evt);
	void AdicionarVelocidade(wxCommandEvent& evt);
	void RemoverVelocidade(wxCommandEvent& evt);
	void EditarVelocidade(wxMouseEvent& evt);

	wxTextCtrl* nomeCtrl;
	wxTextCtrl* posPartidaCtrl;
	wxTextCtrl* posChegadaCtrl;

	/*
	 * O int retornado é uma flag para indicar um erro
	 * 
	 * -1 -> erro desconhecido
	 * 0 -> bem sucedido
	 * 1 -> erro em "Posição de Partida"
	 * 2 -> erro em "Posição de Chegada"
	 * 3 -> valor acima do limite e.g latitude = 90.5
	 * 4 -> tamanhos diferentes para as listas de etapas e velocidades
	 * 5 -> quantidade errada de vértices informados para a etapa de busca
	 */
	int IniciarMissao();

	void SalvarMissao(wxCommandEvent& evt);
	void EnviarMissao(wxCommandEvent& evt);
	bool validateString(std::string str, std::regex reg);
	
	/*
	 * O int retornado informa se a posição está incluída, ou também se houve um erro de digitação
	 * 
	 * -1 -> não bateu com nenhum; provavelmente erro de digitação
	 * 0 -> apenas a etapa (adiciona ao fim da lista)
	 * 1 -> a etapa e a posição
	 * 
	 * o mesmo padrão se repete para waypoint e area
	 */
	int validateStringWaypoint(std::string str);
	int validateStringArea(std::string str);


	/*
	 * O int retornado diz qual o que foi inserido (velocidade; velocidade + posição; velocidade + posição + repetição, 
	 * velocidade + repetição 
	 * 
	 * -1 -> nenhum, provavelmente erro de digitação
	 * 0 -> velocidade (é adicionada uma vez e na última posição)
	 * 1 -> velocidade + posicao (é adicionada uma vez e na posição indicada)
	 * 2 -> velocidade + posição + repetição (é adicionada 'repetição' vezes a partir da posição indicada)
	 * 3 -> velocidade + repetição (é adicionada 'repetição' vezes a partir da última posição)
	 */
	int validateStringVelocidade(std::string str);


	//Parte de carregar missão
	void ShowMissionData();
	void EditMission(wxCommandEvent &evt);

	DECLARE_EVENT_TABLE();
};


enum
{
	SHOWN_ConfigConnectionSizer = 0,
	SHOWN_TelemetrySizer,
	SHOWN_CreateMissionSizer,
	SHOWN_LoadMissionSizer,
};

enum
{
	// Menu Principal
	BUTTON_Connect = wxID_HIGHEST + 1,	
	BUTTON_Telemetry,												
	BUTTON_CreateMission,
	BUTTON_LoadMission,
	BUTTON_ConfigureAirframe,			
	BUTTON_CurrentMission,				
	
	// Configurar Conexão
	BUTTON_CurrentConnection,
	BUTTON_NewConnection,
	BUTTON_Voltar,

	// Criar Missão
	TEXTCTRL_NomeMissao,
	TEXTCTRL_PosPartida,
	TEXTCTRL_PosChegada,
	TEXTCTRL_AdicionarEtapa,
	BUTTON_AdicionarEtapa,
	LISTBOX_Etapas,
	TEXTCTRL_AdicionarVelocidade,
	BUTTON_AdicionarVelocidade,
	LISTBOX_Velocidades,
	BUTTON_SalvarMissao,
	BUTTON_EnviarMissao,
	RADIOBOX_Etapa,

	//Carregar missão
	STATICTEXT_NomeMissao,
	STATICTEXT_PontoPartida,
	STATICTEXT_PontoChegada,
	LISTBOX_EtapasLoad,
	LISTBOX_VelocidadesLoad,
	BUTTON_VisualizarMissao,
	BUTTON_EditarMissao
};

DECLARE_APP(MainApp);

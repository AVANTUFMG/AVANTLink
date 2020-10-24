#pragma once

#include "wx/wx.h"
#include "wx/sizer.h"

#include <regex>


class MainApp : public wxApp    //A classe da aplica��o propriamente dita
{
public:
	virtual bool OnInit();	//Chamada quando incia a aplica��o

};

class MainFrame : public wxFrame	//A classe inicial da janela e componentes. Contida na MainApp
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	wxScrolledWindow* scrolledWindow;

	//Salva o path do arquivo da miss�o no disco
	wxString MissionPath;

	//Bot�es menu principal
	wxButton* BtnVoltar;
	wxButton* BtnConnectVant;
	wxButton* BtnTelemetry;
	wxButton* BtnCreateMission;
	wxButton* BtnLoadMission;
	wxButton* BtnConfigureAirframe;
	wxButton* BtnCurrentMission;


	//Bot�es de "Conectar a um VANT"
	wxButton* BtnCurrentConnection;
	wxButton* BtnNewConnection;

	// Itens de "Criar Miss�o"
	wxTextCtrl* adicionarEtapaCtrl;
	wxButton* adicionarEtapaBtn;
	wxListBox* etapasListBox;
	wxTextCtrl* adicionarVelocidadeCtrl;
	wxButton* adicionarVelocidadeBtn;
	wxListBox* velocidadesListBox;
	wxRadioBox* etapaRadioBox;

	//Itens de "Carregar Miss�o"
	wxStaticText* nome;
	wxStaticText* pontoPartidaText;
	wxStaticText* pontoChegadaText;
	wxListBox* etapas;
	wxListBox* velocidades;

	//M�todos chamados pelos itens do menu
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

	// Parte de criar miss�o	
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
	 * O int retornado � uma flag para indicar um erro
	 * 
	 * -1 -> erro desconhecido
	 * 0 -> bem sucedido
	 * 1 -> erro em "Posi��o de Partida"
	 * 2 -> erro em "Posi��o de Chegada"
	 * 3 -> valor acima do limite e.g latitude = 90.5
	 * 4 -> tamanhos diferentes para as listas de etapas e velocidades
	 * 5 -> quantidade errada de v�rtices inforados para a etapa de busca
	 */
	int IniciarMissao();

	void SalvarMissao(wxCommandEvent& evt);
	void EnviarMissao(wxCommandEvent& evt);
	bool validateString(std::string str, std::regex reg);
	
	/*
	 * O int retornado informa se a posi��o est� inclu�da, ou tamb�m se houve um erro de digita��o
	 * 
	 * -1 -> n�o bateu com nenhum; provavelmente erro de digita��o
	 * 0 -> apenas a etapa (adiciona ao fim da lista)
	 * 1 -> a etapa e a posi��o
	 * 
	 * o mesmo padr�o se repete para waypoint e area
	 */
	int validateStringWaypoint(std::string str);
	int validateStringArea(std::string str);


	/*
	 * O int retornado diz qual o que foi inserido (velocidade; velocidade + posi��o; velocidade + posi��o + repeti��o, 
	 * velocidade + repeti��o 
	 * 
	 * -1 -> nenhum, provavelmente erro de digita��o
	 * 0 -> velocidade (� adicionada uma vez e na �ltima posi��o)
	 * 1 -> velocidade + posicao (� adicionada uma vez e na posi��o indicada)
	 * 2 -> velocidade + posi��o + repeti��o (� adicionada 'repeti��o' vezes a partir da posi��o indicada)
	 * 3 -> velocidade + repeti��o (� adicionada 'repeti��o' vezes a partir da �ltima posi��o)
	 */
	int validateStringVelocidade(std::string str);


	//Parte de carregar miss�o
	void ShowMissionData();

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
	
	// Configurar Conex�o
	BUTTON_CurrentConnection,
	BUTTON_NewConnection,
	BUTTON_Voltar,

	// Criar Miss�o
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

	//Carregar miss�o
	STATICTEXT_NomeMissao,
	STATICTEXT_PontoPartida,
	STATICTEXT_PontoChegada,
	LISTBOX_EtapasLoad,
	LISTBOX_VelocidadesLoad,
	BUTTON_VisualizarMissao
};

DECLARE_APP(MainApp);


#include "wx/wx.h"
#include "TspFrame.h"
#include <algorithm>
#include "GreedySolver.h"
#include "BruteforceSolver.h"
#include "IPathSolver.h"
#include "SolverType.h"
#include <iostream>
#include <fstream>

struct label_equal_x : std::unary_function<wxButton*, bool>
{
	bool operator()(const wxButton* arg) const {
		return arg->GetLabel() == "X";
	}
};

struct label_equal_start : std::unary_function<wxButton*, bool>
{
	bool operator()(const wxButton* arg) const {
		if (arg == nullptr)
			return false;

		return arg->GetLabel() == "START";
	}
};

enum
{
	ID_Hello = 1,
	ID_Start = 2,
	ID_Export = 3
};

wxBEGIN_EVENT_TABLE(TspFrame, wxFrame)
EVT_MENU(wxID_EXIT, TspFrame::OnExit)
EVT_MENU(wxID_ABOUT, TspFrame::OnAbout)
wxEND_EVENT_TABLE()

IPathSolver* TspFrame::CreateSolver(enum SolverType type) {
	switch (type) {
	case Greedy:
		return new GreedySolver();
	case Bruteforce:
		return new BruteforceSolver();
	}
}

TspFrame::TspFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu* menuFile = new wxMenu;
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	topSizer = new wxBoxSizer(wxHORIZONTAL);

	// wektor przechowujacy guziki miast
	buttons = std::vector<wxButton*>();
	buttonsGrid = new wxGridSizer(buttonsHeight, buttonsWidth, 0, 0);

	// wypelnianie guzikow miast
	for (int x = 0; x < buttonsWidth; x++)
	{
		for (int y = 0; y < buttonsHeight; y++)
		{
			int ordinal = (y * buttonsHeight + x);
			wxButton* button = new wxButton(this, 10000 + ordinal);
			button->Bind(wxEVT_BUTTON, &TspFrame::OnCityClick, this);
			button->Bind(wxEVT_RIGHT_DOWN, &TspFrame::OnCityClickRight, this);

			buttonsGrid->Add(button, 1, wxEXPAND | wxALL);
			buttons.push_back(button);
		}
	}

	topSizer->Add(buttonsGrid, 1, wxEXPAND | wxALL);

	buttonsGrid->Layout();

	// lista dostepnych do wyboru algorytmow
	menuSizer = new wxBoxSizer(wxVERTICAL);
	alg_list = new wxListBox(this, wxID_ANY, wxPoint(10, 10), wxSize(150, 150));
	alg_list->AppendString("Algorytm zach³anny");
	alg_list->AppendString("Algorytm si³owy");
	alg_list->Select(0);

	menuSizer->Add(alg_list);

	menuSizer->AddSpacer(5);

	// guzik start
	wxButton* startButton = new wxButton(this, ID_Start, "Start");

	startButton->Bind(wxEVT_BUTTON, &TspFrame::OnStartClick, this);

	menuSizer->Add(startButton, 1, wxEXPAND);

	// guzik eksportuj do pliku
	wxButton* exportButton = new wxButton(this, ID_Export, "Eksportuj do pliku");

	exportButton->Bind(wxEVT_BUTTON, &TspFrame::OnExportClick, this);

	menuSizer->Add(exportButton, 1, wxEXPAND);

	menuSizer->Layout();

	topSizer->Add(menuSizer);

	this->SetSizerAndFit(topSizer);

	Bind(wxEVT_PAINT, &TspFrame::PaintEvent, this);

	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Naciœnij start aby rozpocz¹æ");
}

void TspFrame::OnExportClick(wxCommandEvent& event)
{
	ofstream outputFile("tsp_output.json");

	outputFile << "[ ";

	for (std::vector<wxButton*>::iterator it = buttons.begin(); it < buttons.end(); it++)
	{
		if ((*it)->GetLabel() == "X") {
			outputFile << "{ \"X\": " << (*it)->GetPosition().x << ", \"Y\": " << (*it)->GetPosition().y <<  " },";
		}
	}

	outputFile << " ]";
	outputFile.close();
}

void TspFrame::OnStartClick(wxCommandEvent& event)
{
	auto btn = find_if(buttons.begin(), buttons.end(), label_equal_start());

	vector<City> c = vector<City>();

	wxPoint startLocation = (*btn)->GetPosition();
	City start = City();
	start.location = Point<int>{ startLocation.x, startLocation.y };
	start.name = "0";
	c.push_back(start);

	for (std::vector<wxButton*>::iterator it = buttons.begin() + 1; it < buttons.end(); it++)
	{
		if ((*it)->GetLabel() == "X") {
			wxPoint location = (*it)->GetPosition();
			City next = City();
			next.location = Point<int>{ location.x, location.y };
			next.name = c.size();
			c.push_back(next);
		}
	}

	int selected = alg_list->GetSelection();
	IPathSolver* solver = CreateSolver((enum SolverType)selected);
	SolverResult res = solver->Solve(c, 0);

	results = res.result;

	buttonsGrid->Show(false);
}

void TspFrame::OnCityClick(wxCommandEvent& event)
{
	wxButton* button = (wxButton*)event.GetEventObject();

	auto col = button->GetBackgroundColour();

	button->SetLabel("X");
	button->SetBackgroundColour(*wxLIGHT_GREY);
}

void TspFrame::OnCityClickRight(wxMouseEvent& event)
{
	wxButton* button = (wxButton*)event.GetEventObject();

	button->SetLabel("START");
	button->SetBackgroundColour(*wxGREEN);

	if (this->start != nullptr) {
		ResetButton(start);
	}

	start = button;
}

void TspFrame::ResetButton(wxButton* button) {
	button->SetLabel("");
	button->SetBackgroundColour(wxNullColour);
}

void TspFrame::PaintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void TspFrame::Render(wxDC& dc)
{
	dc.Clear();
	dc.SetPen(wxPen(wxColor(255, 0, 0), 3));
	if (results.size() >= 2) {
		for (std::vector<City>::iterator it = results.begin() + 1; it < results.end(); it++)
		{
			auto last = it - 1;
			dc.DrawLine(last->location.x, last->location.y, it->location.x, it->location.y);
		}
	}
}

void TspFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void TspFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Projekt C++ 2 Kaja Wieczorek i Przemys³aw Postrach",
		"About wx_tsp", wxOK | wxICON_INFORMATION);
}

TspFrame::~TspFrame()
{
}
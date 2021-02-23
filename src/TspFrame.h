#pragma once

#include <wx/wx.h>
#include <vector>
#include "City.h"
#include "IPathSolver.h"
#include "SolverType.h"

class TspFrame : public wxFrame
{
public:
	int buttonsWidth = 10;
	int buttonsHeight = 10;

	wxGridSizer* buttonsGrid = nullptr;
	wxBoxSizer* topSizer = nullptr;
	wxBoxSizer* menuSizer = nullptr;

	wxListBox* alg_list = nullptr;
	std::vector<wxButton*> buttons;
	std::vector<City> results = std::vector<City>();

	wxButton* start = nullptr;

	TspFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~TspFrame();
private:
	void OnStartClick(wxCommandEvent& event);
	void OnCityClick(wxCommandEvent& event);
	void OnCityClickRight(wxMouseEvent& event);
	void OnExportClick(wxCommandEvent& event);

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void PaintEvent(wxPaintEvent& evt);
	void Render(wxDC& dc);

	void ResetButton(wxButton* button);
	IPathSolver* CreateSolver(enum SolverType type);

	wxDECLARE_EVENT_TABLE();
};

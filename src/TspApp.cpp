#pragma once

#include "wx/wx.h"
#include "TspApp.h"
#include "TspFrame.h"

wxIMPLEMENT_APP(TspApp);

bool TspApp::OnInit()
{
	TspFrame* frame = new TspFrame("Traveling Salesman", wxPoint(50, 50), wxSize(800, 600));
	frame->Show(true);
	return true;
}
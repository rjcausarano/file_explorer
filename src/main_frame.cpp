#include "main_frame.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(500, 500)){
    CreateStatusBar();
    SetStatusText("No status update...");
    wxButton* button = new wxButton(this, wxID_ANY, "Say Hi...");
 
    Bind(wxEVT_BUTTON, &MainFrame::OnHello, this);
}

void MainFrame::OnHello(wxCommandEvent& event){
    SetStatusText("Hello there...");
}

#include "main_frame.h"
#include <wx/dirctrl.h>
#include "file.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(500, 500)){
    CreateStatusBar();
    SetStatusText("No status update...");

    wxTreeCtrl* dirlist = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(500, 420));
    dirlist->AddRoot("Root");

    wxButton* button = new wxButton(this, wxID_ANY, "Run");
 
    Bind(wxEVT_BUTTON, &MainFrame::OnHello, this);

    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(dirlist, wxSizerFlags(1).Expand().Border(wxALL));
    vSizer->Add(button, wxSizerFlags(0).Center().Border(wxALL));

    SetSizerAndFit(vSizer);
}

void MainFrame::OnHello(wxCommandEvent& event){
    // SetStatusText("Hello there... " + std::to_string(count_));
    try{
        File file("../test");
        file.list();
        std::cout << "file name: " << file.getName() << std::endl;
        file.del();
    } catch(const std::exception& e){
        std::cerr << "Caught exception: " << e.what() << '\n';
    }
}

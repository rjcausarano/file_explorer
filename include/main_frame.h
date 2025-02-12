#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame();
 
private:
    void OnHello(wxCommandEvent& event);

    unsigned char count_{0};
};

#include <wx/wx.h>
#include <iostream>

#include "main_frame.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override{
        MainFrame *frame = new MainFrame();
        frame->Show();
        return true;
    }
};
 
// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(MyApp);
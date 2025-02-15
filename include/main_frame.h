#pragma once

#include <wx/wx.h>
#include <wx/dirctrl.h>
#include "../proto/dir_descriptor.pb.h"

class MainFrame : public wxFrame {
public:
	MainFrame();

private:
	void onClick(wxCommandEvent& event);
  void updateTree(const Entity parentEntity, wxTreeItemId parentId);

  wxTreeCtrl* dirlist_;
};

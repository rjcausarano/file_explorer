#pragma once

#include <wx/wx.h>
#include <wx/dirctrl.h>
#include "comms/entity.pb.h"
#include "comms/communicator.h"

class MainFrame : public wxFrame {
public:
	MainFrame();

private:
	void onClick(wxCommandEvent& event);
  void updateTree(const Entity parentEntity, wxTreeItemId parentId);

  wxTreeCtrl* dirlist_;
  Communicator communicator_;
};

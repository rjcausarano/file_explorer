#include "main_frame.h"
#include "file.h"

MainFrame::MainFrame() : communicator_{"143.198.158.180"}, wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(500, 500)){
  CreateStatusBar();
  SetStatusText("No status update...");

  dirlist_ = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(500, 420));

  wxButton* button = new wxButton(this, wxID_ANY, "Run");

  Bind(wxEVT_BUTTON, &MainFrame::onClick, this);

  wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
  vSizer->Add(dirlist_, wxSizerFlags(1).Expand().Border(wxALL));
  vSizer->Add(button, wxSizerFlags(0).Center().Border(wxALL));

  SetSizerAndFit(vSizer);
}

void MainFrame::updateTree(const Entity parentEntity, wxTreeItemId parentId){
  for(Entity childEntity : parentEntity.entities()){
    wxTreeItemId childId = dirlist_->AppendItem(parentId, childEntity.name());
    if(childEntity.type() == Entity::DIRECTORY){
      updateTree(childEntity, childId);
    }
  }
}

void MainFrame::onClick(wxCommandEvent& event){
  Entity entity = communicator_.getDirTree("/home/rodri/server_root");
  dirlist_->DeleteAllItems();
  wxTreeItemId rootId = dirlist_->AddRoot(entity.name());
  updateTree(entity, rootId);
}

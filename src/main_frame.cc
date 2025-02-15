#include "main_frame.h"
#include "file.h"
#include "entity_processor.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(500, 500)){
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
  File file("../test/parent_dir");
	EntityProcessor entityProcessor(file);
  Entity entity = entityProcessor.getEntity();
  wxTreeItemId rootId = dirlist_->AddRoot(entity.name());
  updateTree(entity, rootId);
}

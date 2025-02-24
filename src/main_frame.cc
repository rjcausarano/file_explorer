#include "main_frame.h"
#include "file.h"
#include <string>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(500, 500)){
  wxMenuBar* menuBar = new wxMenuBar();
  wxMenu* fileMenu = new wxMenu();
  fileMenu->Append(wxID_ANY, "Connect to Server\tCtrl+C");
  menuBar->Append(fileMenu, "&File");  // Alt+F shortcut
  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("No status update...");
  config_ = new wxConfig("FileExplorer", "RCSolutions");
  dirlist_ = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(500, 420));

  wxString ip;
  config_->Read("ServerIp", &ip, "0.0.0.0");
  // config_->Write("ServerIp", "0.0.0.0");
  // config_->Flush();
  wxButton* button = new wxButton(this, wxID_ANY, "Run");

  Bind(wxEVT_BUTTON, &MainFrame::onClick, this);
  Bind(wxEVT_MENU, &MainFrame::onConnect, this);
  Bind(wxEVT_TREE_ITEM_RIGHT_CLICK, &MainFrame::onTreeRightClick, this);

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

void MainFrame::onConnect(wxCommandEvent& event) {
  wxTextEntryDialog dialog(this, "Enter the IP address to connect:", "Connect to Server", "0.0.0.0");
  if (dialog.ShowModal() == wxID_OK) {
    communicator_.connect(dialog.GetValue().ToStdString());
  }
}

// void MainFrame::onClick(wxCommandEvent& event){
  // Entity entity = communicator_.getDirTree("/Users/rodric/projects/file_explorer");
  // dirlist_->DeleteAllItems();
  // wxTreeItemId rootId = dirlist_->AddRoot(entity.name());
  // updateTree(entity, rootId);
// }

void MainFrame::onTreeRightClick(wxTreeEvent& event){
  wxTreeItemId item = event.GetItem();
  if (item.IsOk()) {
    SetStatusText("Right-clicked on: " + dirlist_->GetItemText(item));
  } else {
    SetStatusText("Right-clicked outside of any item");
  }

  wxFileDialog openFileDialog(this, 
    "Open File", 
    "", 
    "", 
    "All files (*.*)|*.*", 
    wxFD_OPEN | wxFD_FILE_MUST_EXIST);

  if (openFileDialog.ShowModal() == wxID_OK) {
    wxString path = openFileDialog.GetPath();
    SetStatusText("Selected file: " + path);
  }
}
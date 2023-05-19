#include "mainframe.hpp"
#include <wx/wx.h>
#include <wx/string.h>

#include <iostream>
#include <sstream>

#include <vector>
#include <fstream> 
#include <filesystem>

std::string to_hex(std::string s )
{
  std::ostringstream oss;

  for (auto c: s)
  {
    oss.width(2);
    oss << std::hex << (unsigned int) c;
  }
  return oss.str();
}

void MainFrame::OnAsciiKeyDown(wxKeyEvent& key) {
  if (key.GetUnicodeKey() == 8) { // Handling backspace
    wxString asciiStr = asciiInput->GetValue();
    if(!asciiStr.IsEmpty()) {
      asciiStr.RemoveLast();
      asciiInput->SetValue(asciiStr); 

      wxString hexStr = hexInput->GetValue();
      if(!hexStr.IsEmpty()) { 
        hexStr.RemoveLast(2); 
        hexInput->SetValue(hexStr);
      }
    }
  } else { // For all other keys
    std::string keyStr(1, static_cast<char>(key.GetUnicodeKey()));
    asciiInput->AppendText(keyStr);
    hexInput->AppendText(to_hex(keyStr));
  }
}


int MainFrame::WriteInFile(std::string str, bool append) {
  std::ofstream myfile;
  if(append) {
    myfile.open("data.txt", std::ofstream::out | std::ofstream::app);
  } else {
    myfile.open("data.txt", std::ofstream::out);
  }

  if(myfile.is_open()){
      myfile << str << std::endl;
      myfile.close();
  } else {
      std::cerr << "Unable to open file" << std::endl;
      return -1;
  }
  return 0;
}

void MainFrame::OnSaveButton(wxCommandEvent& event) {
  if(asciiInput->GetValue().ToStdString() != "") {
    std::string asciiText = asciiInput->GetValue().ToStdString();
    std::vector<std::string> asciiT;
    asciiT.push_back(asciiText);
    
    // erase data and write ascii
    for(auto& e : asciiT) {WriteInFile(e, false);}
    
    // append hex
    for(auto& e : asciiT) {WriteInFile(to_hex(e), true);}
  }
}



void MainFrame::OnClearButton(wxCommandEvent& event) {
  asciiInput->Clear();
  hexInput->Clear();
}


void MainFrame::OnLoadButton(wxCommandEvent& event) {
  std::ifstream myfile;
  std::string str, ascii, hex;
  myfile.open("data.txt");
  if(myfile.is_open()){
    while(std::getline(myfile, str)) {
      if(ascii == "") {
        ascii = str;
      } else {
        hex = str; 
      }
    }
    myfile.close();

    // Assuming the ASCII string is on the first line and the hex string is on the second line
    asciiInput->SetValue(ascii);
    hexInput->SetValue(hex);
  } else {
    std::cerr << "Unable to open file" << std::endl;
  }
}


MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
  
  panel = new wxPanel(this);
  asciiInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 0), wxSize(1000,500));
  asciiInput->Bind(wxEVT_CHAR, &MainFrame::OnAsciiKeyDown, this);
  hexInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 500), wxSize(1000,500));
  hexInput->Bind(wxEVT_CHAR, &MainFrame::OnAsciiKeyDown, this);
  clearButton = new wxButton(panel, wxID_ANY, "CLEAR", wxPoint(0, 1000), wxSize(300, 200));
  clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButton, this);
  saveButton = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(350, 1000), wxSize(300,200));
  saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButton, this);
  loadButton = new wxButton(panel, wxID_ANY, "LOAD", wxPoint(700, 1000), wxSize(300,200));
  loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadButton, this);
}


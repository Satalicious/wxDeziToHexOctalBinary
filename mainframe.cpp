#include "mainframe.hpp"
#include <wx/wx.h>
#include <wx/string.h>

#include <iostream>
#include <sstream>

#include <vector>
#include <fstream> 
#include <chrono>
#include <ctime>

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

int writeOnfile (char* filetext) {
   std::ofstream myfile;
   myfile.open ("data.txt", std::fstream::app);
   myfile << filetext;
   myfile.close();
   return 0;
}


int MainFrame::LoadFromFile() {
  //TODO:
  std::ofstream myfile;
  myfile.open ("data.txt", std::fstream::app);
  
  return 0;
}


void MainFrame::OnAsciiKeyDown(wxKeyEvent& key) {
  //The 1 specifies the length of the string to create, and the char being passed in is what to fill that string with. 
  //So it's creating a new string of length 1, filled with the char that was created from the Unicode key.
  std::string keyStr(1, static_cast<char>(key.GetUnicodeKey()));

  // Append the Unicode character to the ASCII input field
  asciiInput->AppendText(keyStr);

  // Convert the Unicode character to hexadecimal and append it to the hex input field
  hexInput->AppendText(to_hex(keyStr));
}

void MainFrame::OnClearButton(wxCommandEvent& event) {
  asciiInput->Clear();
  hexInput->Clear();
}

void MainFrame::OnSaveButton(wxCommandEvent& event) {
  if(asciiInput->GetValue().ToStdString() != "") {
    std::string asciiText = asciiInput->GetValue().ToStdString();
    std::vector<std::string> asciiT;
    asciiT.push_back(asciiText);
    // write ascii
    for(auto& e : asciiT) {WriteInFile(e);}
    // write hex
    for(auto& e : asciiT) {WriteInFile(to_hex(e));}
  }

}

void MainFrame::OnLoadButton(wxCommandEvent& event) {
  //TODO:
  LoadFromFile();
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


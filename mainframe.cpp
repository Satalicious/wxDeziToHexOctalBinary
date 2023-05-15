#include "mainframe.hpp"
#include <wx/wx.h>
#include <wx/string.h>

#include <iostream>
#include <sstream>

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
  //std::cout << key.GetUnicodeKey() << std::endl;
  asciiInput->AppendText(key.GetUnicodeKey());
  hexInput->AppendText(to_hex(asciiInput->GetValue().ToStdString()));

}


MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
  
  panel = new wxPanel(this);

  asciiInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 0), wxSize(1000,500));
  asciiInput->Bind(wxEVT_KEY_DOWN, &MainFrame::OnAsciiKeyDown, this);
  hexInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 500), wxSize(1000,500));
  clearButton = new wxButton(panel, wxID_ANY, "CLEAR", wxPoint(0, 1000), wxSize(200, 200));

}


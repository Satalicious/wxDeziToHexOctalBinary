#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP
#include <wx/generic/grid.h>
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
  MainFrame(const wxString &title);

private:
  wxPanel *panel;
  wxTextCtrl* asciiInput;
  wxTextCtrl* hexInput;
  wxButton *clearButton;

  void OnAsciiKeyDown(wxKeyEvent& key);
};

#endif // MAINFRAME_HPP

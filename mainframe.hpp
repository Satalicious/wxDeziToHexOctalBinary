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
  wxButton* clearButton;
  wxButton* saveButton;
  wxButton* loadButton;
  

  void OnAsciiKeyDown(wxKeyEvent& key);
  void OnClearButton(wxCommandEvent &event);
  void OnSaveButton(wxCommandEvent &event);
  void OnLoadButton(wxCommandEvent &event);
  int WriteInFile(std::string text);
  int LoadFromFile();
  
};

#endif // MAINFRAME_HPP

#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP
#include <wx/generic/grid.h>
#include <wx/wx.h>


class MainFrame : public wxFrame {
public:
  MainFrame(const wxString &title);
  virtual ~MainFrame();

private:
  wxPanel *panel;
  wxTextCtrl* asciiInput;
  wxTextCtrl* hexInput;
  wxButton* clearButton;
  wxButton* saveButton;
  wxButton* loadButton;
  
  void OnAsciiKeyDown(wxKeyEvent& key);
  void OnHexKeyDown(wxKeyEvent& key);
  void OnClearButton(wxCommandEvent &event);
  void OnSaveButton(wxCommandEvent &event);
  void OnLoadButton(wxCommandEvent &event);
  int WriteInFile(std::string str, bool append);
  void SaveSession();
  void LoadSession();
  void OnClose(wxCloseEvent& event);

  
};

#endif // MAINFRAME_HPP

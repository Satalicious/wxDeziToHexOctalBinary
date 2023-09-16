#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP
#include <wx/generic/grid.h>
#include <wx/wx.h>


class MainFrame : public wxFrame {
public:
  MainFrame(const wxString &title);
  ~MainFrame() {}

private:
  wxPanel *panel;
  wxTextCtrl* hexInput;
  wxTextCtrl* octalInput;
  wxTextCtrl* binaryInput;
  wxTextCtrl* decimalInput;

  wxButton* clearButton;
  wxButton* saveButton;
  wxButton* loadButton;
  

  void OnClearButton(wxCommandEvent &event);
  


  void OnClose(wxCloseEvent& event);

  void OnDecimalKeyDown(wxCommandEvent& event);

  
};

#endif // MAINFRAME_HPP

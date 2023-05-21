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
  if (key.GetUnicodeKey() == 8) {
    wxString asciiStr = asciiInput->GetValue();
    if(!asciiStr.IsEmpty()) {
      asciiStr.RemoveLast();
      asciiInput->SetValue(asciiStr);

      // reconvert entire ASCII to HEX
      hexInput->SetValue(to_hex(asciiStr.ToStdString()));
    }
  } else { // For all other keys
    std::string keyStr(1, static_cast<char>(key.GetUnicodeKey()));
    asciiInput->AppendText(keyStr);
    hexInput->SetValue(to_hex(asciiInput->GetValue().ToStdString()));
  }
}

std::string hex_to_ascii(std::string hex) {
    std::string ascii = "";
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byte = hex.substr(i, 2);
        char chr = static_cast<char>(stoi(byte, nullptr, 16));
        // Check if character is printable
        if ((chr >= 32 && chr <= 126) || (chr >= 161 && chr <= 255)) {
            ascii += chr;
        } else {
            ascii += '.'; // Append '.' for non-printable characters
        }
    }
    return ascii;
}

void MainFrame::OnHexKeyDown(wxKeyEvent& key) {
  int keyCode = key.GetUnicodeKey();
  if ((keyCode >= '0' && keyCode <= '9') || 
      (keyCode >= 'a' && keyCode <= 'f') || 
      (keyCode >= 'A' && keyCode <= 'F')) { 
    // Only allow hexadecimal characters
    std::string keyStr(1, static_cast<char>(key.GetUnicodeKey()));
    hexInput->AppendText(keyStr);

    // reconvert entire HEX to ASCII
    asciiInput->SetValue(hex_to_ascii(hexInput->GetValue().ToStdString()));
  } else if (key.GetUnicodeKey() == 8) {
    wxString hexStr = hexInput->GetValue();
    if(!hexStr.IsEmpty()) {
      hexStr.RemoveLast();
      hexInput->SetValue(hexStr);

      // reconvert entire HEX to ASCII
      asciiInput->SetValue(hex_to_ascii(hexStr.ToStdString()));
    }
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

void MainFrame::OnClearButton(wxCommandEvent& event) {
  asciiInput->Clear();
  hexInput->Clear();
}

void MainFrame::OnSaveButton(wxCommandEvent& event) {
  SaveSession();
}

void MainFrame::OnLoadButton(wxCommandEvent& event) {
  LoadSession();
}

void MainFrame::OnClose(wxCloseEvent& event) {
    // Save session before closing
    SaveSession();
    event.Skip(); // make sure the default handler still gets called. We don't want to eat the event.
}


MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
  
  panel = new wxPanel(this);
  asciiInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 0), wxSize(1000,500));
  asciiInput->Bind(wxEVT_CHAR, &MainFrame::OnAsciiKeyDown, this);
  hexInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 500), wxSize(1000,500));
  hexInput->Bind(wxEVT_CHAR, &MainFrame::OnHexKeyDown, this);
  clearButton = new wxButton(panel, wxID_ANY, "CLEAR", wxPoint(0, 1000), wxSize(300, 200));
  clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButton, this);
  saveButton = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(350, 1000), wxSize(300,200));
  saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButton, this);
  loadButton = new wxButton(panel, wxID_ANY, "LOAD", wxPoint(700, 1000), wxSize(300,200));
  loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadButton, this);

  LoadSession();
}

MainFrame::~MainFrame() {
    // Save session before closing
    SaveSession();
}

void MainFrame::SaveSession() {
    if(asciiInput->GetValue().ToStdString() != "") {
        std::string asciiText = asciiInput->GetValue().ToStdString();
        std::string hexText = hexInput->GetValue().ToStdString();

        WriteInFile(asciiText, false);
        WriteInFile(hexText, true);
    }
}

void MainFrame::LoadSession() {
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

        asciiInput->SetValue(ascii);
        hexInput->SetValue(hex);
    }
}


/* #include <string>
#include <iostream>

class Animal {
protected:
    std::string name;
public:
    void setName(std::string name) {this->name = name;}
    virtual void makeSound() = 0;
};

class Dog : public Animal { // Inheritance
public:
    void makeSound() override { 
        std::cout << name << " says Woof!" << std::endl; 
    }
};

int main() {
    Dog dog;
    dog.setName("Rex");
    dog.makeSound(); 
    return 0;
} 

    We created a base class Animal with the protected data member name and the public setter method setName(), showing Encapsulation. The makeSound() method is declared but not defined, expecting derived classes to provide the definition.
    The Dog class inherit from Animal and provides their own implementation for makeSound(), showing Polymorphism.
    Instances of Dog are treated as Animal and behave according to their types when makeSound() is called, demonstrating both Inheritance and Polymorphism.
*/



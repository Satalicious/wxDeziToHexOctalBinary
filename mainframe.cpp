#include "mainframe.hpp"
#include <wx/wx.h>
#include <wx/string.h>

#include <iostream>
#include <sstream>

#include <vector>
#include <fstream> 
#include <filesystem>


std::string decimal_to_hex(unsigned int dec) {
    std::stringstream ss;
    ss << std::hex << dec;
    return ss.str();
}
std::string decimal_to_octal(unsigned int dec) {
    std::stringstream ss;
    ss << std::oct << dec;
    return ss.str();
}
std::string decimal_to_binary(unsigned int dec) {
    std::string binary;
    while (dec) {
        binary = (dec & 1 ? '1' : '0') + binary;
        dec >>= 1;
    }
    return binary.empty() ? "0" : binary;
}


void MainFrame::OnDecimalKeyDown(wxCommandEvent& event)  {
    long unsigned int decimalValue; // Changed the type here

    // Passed the address of decimalValue
    if(decimalInput->GetValue().ToULong(&decimalValue)) {
        hexInput->SetValue(decimal_to_hex(decimalValue));
        octalInput->SetValue(decimal_to_octal(decimalValue));
        binaryInput->SetValue(decimal_to_binary(decimalValue));
    } else {
        hexInput->Clear();
        octalInput->Clear();
        binaryInput->Clear();
    }
}









void MainFrame::OnClearButton(wxCommandEvent& event) {
  hexInput->Clear();
  octalInput->Clear();
  binaryInput->Clear();
  decimalInput->Clear();
}



void MainFrame::OnClose(wxCloseEvent& event) {
    // Save session before closing

    event.Skip(); // make sure the default handler still gets called. We don't want to eat the event.
}


MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
  
  panel = new wxPanel(this);

  decimalInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 0), wxSize(1000,200));
  decimalInput->Bind(wxEVT_TEXT, &MainFrame::OnDecimalKeyDown, this);


  hexInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 200), wxSize(1000,200));


  octalInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 400), wxSize(1000,200));


  binaryInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 600), wxSize(1000,200));





  clearButton = new wxButton(panel, wxID_ANY, "CLEAR", wxPoint(0, 1000), wxSize(300, 200));
  clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButton, this);
  saveButton = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(350, 1000), wxSize(300,200));

  loadButton = new wxButton(panel, wxID_ANY, "LOAD", wxPoint(700, 1000), wxSize(300,200));


  //LoadSession();
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



#include "about.h"
#include "window.h"


enum
{
    ID_OK
};

wxBEGIN_EVENT_TABLE(About, wxFrame)
    EVT_BUTTON(ID_OK, About::OnExit)
wxEND_EVENT_TABLE()

About::About() :
    wxFrame(
        nullptr,
        wxID_ANY,
        "About",
        wxDefaultPosition,
        wxSize(600, 400),
        wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU & (~wxRESIZE_BORDER)
    )
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    
    wxBoxSizer *sizer1;
    wxBoxSizer *sizer2;
    wxBoxSizer *sizer3;
    wxBoxSizer *sizer4;
    
    sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer2 = new wxBoxSizer(wxVERTICAL);
    sizer3 = new wxBoxSizer(wxVERTICAL);
    sizer4 = new wxBoxSizer(wxVERTICAL);
    
    panel = new wxPanel(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxSize(1050, 640),
        wxBORDER_SUNKEN | wxTAB_TRAVERSAL
    );
    
    title1 = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("Programmers"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    title1->Wrap(-1);
    title1->SetFont(
        wxFont(
            12,
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD,
            false,
            wxEmptyString
        )
    );
    
    title2 = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("License"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    title2->Wrap(-1);
    title2->SetFont(
        wxFont(
            12,
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD,
            false,
            wxEmptyString
        )
    );
    
    title3 = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("Copyright"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    title3->Wrap(-1);
    title3->SetFont(
        wxFont(
            12,
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD,
            false,
            wxEmptyString
        )
    );
    
    name1 = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("Daniel Grant"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    name1->Wrap(-1);
    name1->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD,
            false,
            wxEmptyString
        )
    );
    
    email1 = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("d.grant@uleth.ca"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    email1->Wrap(-1);
    email1->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );
    
    name2 = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("Brayden Carlson"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    name2->Wrap(-1);
    name2->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD,
            false,
            wxEmptyString
        )
    );
    
    email2 = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("brayden.carlson@uleth.ca"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    email2->Wrap(-1);
    email2->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );
    
    license = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("MIT License (MIT)"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    license->Wrap(-1);
    license->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );
    
    copyright = new wxStaticText(
        panel,
        wxID_ANY,
        wxT("Copyright 2021 Daniel Grant, Brayden Carlson"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    copyright->Wrap(-1);
    copyright->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );
    
    button = new wxButton(this, ID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0);
    
    sizer4->Add(title1, 0, wxALL, 5);
    sizer4->Add(0, 5, 0, wxEXPAND, 0);
    sizer4->Add(name1, 0, wxALL, 5);
    sizer4->Add(email1, 0, wxALL, 5);
    sizer4->Add(0, 5, 0, wxEXPAND, 0);
    sizer4->Add(name2, 0, wxALL, 5);
    sizer4->Add(email2, 0, wxALL, 5);
    sizer4->Add(0, 0, 1, wxEXPAND, 5);
    sizer4->Add(title2, 0, wxALL, 5);
    sizer4->Add(0, 5, 0, wxEXPAND, 0);
    sizer4->Add(license, 0, wxALL, 5);
    sizer4->Add(0, 0, 1, wxEXPAND, 5);
    sizer4->Add(title3, 0, wxALL, 5);
    sizer4->Add(0, 5, 0, wxEXPAND, 0);
    sizer4->Add(copyright, 0, wxALL, 5);
    sizer3->Add(sizer4, 1, wxALL | wxEXPAND, 5);
    panel->SetSizer(sizer3);
    panel->Layout();
    sizer2->Add(panel, 1, wxALL | wxEXPAND, 5);
    sizer2->Add(button, 0, wxALIGN_CENTER | wxALL, 5);
    sizer1->Add(sizer2, 1, wxALL | wxEXPAND, 0);
    
    this->SetSizer(sizer1);
    this->Layout();
    this->Centre(wxBOTH);
}

About::~About()
{

}

void About::OnExit(wxCommandEvent &event)
{
    Close(true);
}

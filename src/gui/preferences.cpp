#include "app.h"
#include "ini.h"
#include "preferences.h"
#include "utilities.h"
#include "window.h"


enum
{
    ID_SAVE,
    ID_CANCEL,
    ID_AUTOSCAN
};

DECLARE_APP(App);

wxBEGIN_EVENT_TABLE(Preferences, wxFrame)
    EVT_BUTTON(ID_SAVE, Preferences::OnSave)
    EVT_BUTTON(ID_CANCEL, Preferences::OnExit)
    EVT_CHECKBOX(ID_AUTOSCAN, Preferences::OnAutoscan)
wxEND_EVENT_TABLE()

Preferences::Preferences(wxWindow *parent) :
    wxFrame(
        parent,
        wxID_ANY,
        "Preferences",
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
    wxGridSizer *sizer5;
    wxBoxSizer *sizer6;
    wxBoxSizer *sizer7;
    wxBoxSizer *sizer8;
    wxBoxSizer *sizer9;

    sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer2 = new wxBoxSizer(wxVERTICAL);
    sizer3 = new wxBoxSizer(wxVERTICAL);
    sizer4 = new wxBoxSizer(wxVERTICAL);
    sizer5 = new wxGridSizer(0, 2, 0, 0);
    sizer6 = new wxBoxSizer(wxVERTICAL);
    sizer7 = new wxBoxSizer(wxVERTICAL);
    sizer8 = new wxBoxSizer(wxVERTICAL);
    sizer9 = new wxBoxSizer(wxHORIZONTAL);

    panel1 = new wxPanel(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxBORDER_SUNKEN | wxTAB_TRAVERSAL
    );

    title = new wxStaticText(
        panel1,
        wxID_ANY,
        wxT("Default Directories"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    title->Wrap(-1);
    title->SetFont(
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
        panel1,
        wxID_ANY,
        wxT("Options"),
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

    label1 = new wxStaticText(
        panel1,
        wxID_ANY,
        wxT("Input Directory"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    label1->Wrap(-1);
    label1->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );

    label2 = new wxStaticText(
        panel1,
        wxID_ANY,
        wxT("Output Directory"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    label2->Wrap(-1);
    label2->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );

    directory1 = new wxDirPickerCtrl(
        panel1,
        wxID_ANY,
        wxEmptyString,
        wxT("Select a folder"),
        wxDefaultPosition,
        wxSize(400, -1),
        wxDIRP_DEFAULT_STYLE | wxDIRP_DIR_MUST_EXIST
    );
    directory2 = new wxDirPickerCtrl(
        panel1,
        wxID_ANY,
        wxEmptyString,
        wxT("Select a folder"),
        wxDefaultPosition,
        wxSize(400, -1),
        wxDIRP_DEFAULT_STYLE | wxDIRP_DIR_MUST_EXIST
    );

    checkbox1 = new wxCheckBox(
        panel1,
        ID_AUTOSCAN,
        wxT("  Autoscan input directory for .fasta or .gb files"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    checkbox1->SetValue(true);
    checkbox1->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );

    checkbox2 = new wxCheckBox(
        panel1,
        wxID_ANY,
        wxT("  Autoscan input directories recursively for .fasta and .gb files"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    checkbox2->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );

    checkbox3 = new wxCheckBox(
        panel1,
        wxID_ANY,
        wxT("  Open output directory after processing"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );
    checkbox3->SetValue(true);
    checkbox3->SetFont(
        wxFont(
            wxNORMAL_FONT->GetPointSize(),
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            wxEmptyString
        )
    );

    save_button = new wxButton(
        this,
        ID_SAVE,
        wxT("Save"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );

    cancel_button = new wxButton(
        this,
        ID_CANCEL,
        wxT("Cancel"),
        wxDefaultPosition,
        wxDefaultSize,
        0
    );

    sizer4->Add(title, 0, wxALL | wxEXPAND, 5);
    sizer3->Add(sizer4, 0, wxALL | wxEXPAND, 5);
    sizer5->Add(label1, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer5->Add(directory1, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL, 5);
    sizer5->Add(label2, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer5->Add(directory2, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL, 5);
    sizer3->Add(sizer5, 0, wxALL | wxEXPAND, 5);
    sizer3->Add(0, 5, 0, wxALL | wxEXPAND, 5);
    sizer6->Add(title2, 0, wxALL | wxEXPAND, 5);
    sizer6->Add(0, 7, 0, wxALL, 0);
    sizer7->Add(checkbox1, 0, wxALL | wxEXPAND, 5);
    sizer7->Add(checkbox2, 0, wxALL | wxEXPAND, 5);
    sizer7->Add(checkbox3, 0, wxALL | wxEXPAND, 5);
    sizer6->Add(sizer7, 1, wxALL | wxEXPAND, 5);
    sizer3->Add(sizer6, 0, wxALL | wxEXPAND, 5);
    panel1->SetSizer(sizer3);
    panel1->Layout();
    sizer3->Fit(panel1);
    sizer2->Add(panel1, 1, wxALL | wxEXPAND, 5);
    sizer1->Add(sizer2, 1, wxALL | wxEXPAND, 5);
    sizer9->Add(0, 0, 1, wxEXPAND, 5);
    sizer9->Add(save_button, 0, wxALL, 5);
    sizer9->Add(cancel_button, 0, wxALL, 5);
    sizer8->Add(sizer9, 0, wxEXPAND, 5);
    sizer1->Add(sizer8, 0, wxALL | wxEXPAND, 5);

    this->SetSizer(sizer1);
    this->Layout();
    this->Centre(wxBOTH);
    this->OnLoad();
}

Preferences::~Preferences()
{

}

void Preferences::OnLoad()
{
    std::string path = get_base_path();

    fs::path preferences = path;
    preferences /= "preferences.ini";

    mINI::INIFile file(preferences.string());
    mINI::INIStructure ini;
    file.read(ini);

    std::string &input = ini["directory"]["input"];
    std::string &output = ini["directory"]["output"];

    std::string &autoscan = ini["options"]["autoscan"];
    std::string &recursive = ini["options"]["recursive"];
    std::string &launch = ini["options"]["launch"];

    directory1->SetPath(input);
    directory2->SetPath(output);

    if (autoscan == "true")
    {
        checkbox1->SetValue(true);
        checkbox2->Enable();
    }
    else
    {
        checkbox1->SetValue(false);
        checkbox2->SetValue(false);
        checkbox2->Disable();
    }

    if (recursive  == "true")
    {
        checkbox2->SetValue(true);
    }
    else
    {
       checkbox2->SetValue(false);
    }

    if (launch == "true")
    {
        checkbox3->SetValue(true);
    }
    else
    {
        checkbox3->SetValue(false);
    }
}

void Preferences::OnAutoscan(wxCommandEvent &event)
{
    bool checked = checkbox1->GetValue();

    if (checked)
    {
        checkbox2->Enable();
    }
    else
    {
        checkbox2->SetValue(false);
        checkbox2->Disable();
    }
}

void Preferences::OnSave(wxCommandEvent &event)
{
    std::string base = get_base_path();

    fs::path preferences = base;
    preferences /= "preferences.ini";

    mINI::INIFile file(preferences.string());
    mINI::INIStructure ini;
    file.read(ini);

    bool autoscan = checkbox1->GetValue();
    bool recursive = checkbox2->GetValue();
    bool launch = checkbox3->GetValue();

    std::string input = directory1->GetPath();
    std::string output = directory2->GetPath();

    ini["directory"].set(
        {
            {"input", input},
            {"output", output}
        }
    );

    ini["options"].set(
        {
            {"autoscan", autoscan ? "true" : "false"},
            {"recursive", recursive ? "true" : "false"},
            {"launch", launch ? "true" : "false"}
        }
    );

    bool write = file.write(ini, true);

    if (write)
    {
        fs::path directory = output;
        fs::create_directory(directory);

        Close(true);
        wxGetApp().SetRestart(true);
        wxGetApp().ExitMainLoop();
    }
    else
    {
        wxMessageBox(
            "There was an issue saving your preferences.",
            "Error",
            wxOK | wxICON_ERROR | wxCENTRE
        );
    }
}

void Preferences::OnExit(wxCommandEvent &event)
{
    Close(true);
}


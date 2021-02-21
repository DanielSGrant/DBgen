#include "about.h"
#include "app.h"
#include "menu.h"
#include "preferences.h"
#include "window.h"


enum
{
    // macOS does not let a menu item start at 0
    ID_RELOAD = 1,
    ID_PREFERENCES,
    ID_EXIT,
    ID_ABOUT
};

DECLARE_APP(App);

wxBEGIN_EVENT_TABLE(Menu, wxMenuBar)
    EVT_MENU(ID_RELOAD, Menu::OnReload)
    EVT_MENU(ID_PREFERENCES, Menu::OnPreferences)
    EVT_MENU(ID_EXIT, Menu::OnExit)
    EVT_MENU(ID_ABOUT, Menu::OnAbout)
wxEND_EVENT_TABLE()

Menu::Menu() : wxMenuBar()
{
    menu1 = new wxMenu();
    menu2 = new wxMenu();

    wxMenuItem *menuitem1;
    wxMenuItem *menuitem2;
    wxMenuItem *menuitem3;
    wxMenuItem *menuitem4;

    menuitem1 = new wxMenuItem(
        menu1,
        ID_RELOAD,
        wxString(wxT("Reload")) ,
        wxEmptyString,
        wxITEM_NORMAL
    );

    menuitem2 = new wxMenuItem(
        menu1,
        ID_PREFERENCES,
        wxString(wxT("Preferences")) ,
        wxEmptyString,
        wxITEM_NORMAL
    );

    menuitem3 = new wxMenuItem(
        menu1,
        ID_EXIT,
        wxString(wxT("Exit")),
        wxEmptyString,
        wxITEM_NORMAL
    );

    menuitem4 = new wxMenuItem(
        menu2,
        ID_ABOUT,
        wxString(wxT("About")),
        wxEmptyString,
        wxITEM_NORMAL
    );

    menu1->Append(menuitem1);
    menu1->Append(menuitem2);
    menu1->Append(menuitem3);
    menu2->Append(menuitem4);

    this->Append(menu1, wxT("File"));
    this->Append(menu2, wxT("Help"));
}

Menu::~Menu()
{

}

void Menu::OnReload(wxCommandEvent &event)
{
    wxGetApp().SetRestart(true);
    wxGetApp().ExitMainLoop();
}

void Menu::OnPreferences(wxCommandEvent &event)
{
    Preferences *preferences = new Preferences((wxWindow *) GetParent());
    preferences->Show();
}

void Menu::OnExit(wxCommandEvent &event)
{
    Connect(
        ID_EXIT,
        wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Window::OnExit)
    );
}

void Menu::OnAbout(wxCommandEvent &event)
{
    About *about = new About((wxWindow *) GetParent());
    about->Show();
}

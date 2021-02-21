#include "about.h"
#include "menu.h"
#include "preferences.h"
#include "window.h"


enum
{
    // macOS does not let a menu item start at 0
    ID_PREFERENCES = 1,
    ID_EXIT,
    ID_ABOUT
};

wxBEGIN_EVENT_TABLE(Menu, wxMenuBar)
    EVT_MENU(ID_PREFERENCES, Menu::OnPreferences)
    EVT_MENU(ID_EXIT, Window::OnExit)
    EVT_MENU(ID_ABOUT, Menu::OnAbout)
wxEND_EVENT_TABLE()

Menu::Menu() : wxMenuBar()
{
    menu1 = new wxMenu();
    menu2 = new wxMenu();

    wxMenuItem* menuitem1;
    wxMenuItem* menuitem2;
    wxMenuItem* menuitem3;

    menuitem1 = new wxMenuItem(
        menu1,
        ID_PREFERENCES,
        wxString(wxT("Preferences")) ,
        wxEmptyString,
        wxITEM_NORMAL
    );

    menuitem2 = new wxMenuItem(
        menu1,
        ID_EXIT,
        wxString(wxT("Exit")),
        wxEmptyString,
        wxITEM_NORMAL
    );

    menuitem3 = new wxMenuItem(
        menu2,
        ID_ABOUT,
        wxString(wxT("About")),
        wxEmptyString,
        wxITEM_NORMAL
    );

    menu1->Append(menuitem1);
    menu1->Append(menuitem2);
    menu2->Append(menuitem3);

    this->Append(menu1, wxT("File"));
    this->Append(menu2, wxT("Help"));
}

Menu::~Menu()
{

}

void Menu::OnPreferences(wxCommandEvent &event)
{
    Preferences *preferences = new Preferences((wxWindow *) GetParent());
    preferences->Show();
}

void Menu::OnAbout(wxCommandEvent &event)
{
    About *about = new About((wxWindow *) GetParent());
    about->Show();
}

void Menu::OnExit(wxCommandEvent &event)
{
    Connect(
        ID_EXIT,
        wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Window::OnExit)
    );
}

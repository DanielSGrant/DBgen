#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class Menu : public wxMenuBar
{
public:
    Menu();
    ~Menu();

public:
    void OnPreferences(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

private:
    wxMenu
    *menu1,
    *menu2;

    wxMenuItem
    *menuitem1,
    *menuitem2,
    *menuitem3;

    wxDECLARE_EVENT_TABLE();
};

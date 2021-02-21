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
    void OnReload(wxCommandEvent&);
    void OnPreferences(wxCommandEvent&);
    void OnExit(wxCommandEvent&);
    void OnAbout(wxCommandEvent&);

private:
    wxMenu
    *menu1,
    *menu2;

    wxMenuItem
    *menuitem1,
    *menuitem2,
    *menuitem3,
    *menuitem4;

    wxDECLARE_EVENT_TABLE();
};

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "about.h"
#include "options.h"


class Menu : public wxMenuBar
{
    public:
        Menu();
        ~Menu();
        
    public:
        void OnReload(wxCommandEvent &);
        void OnOptions(wxCommandEvent &);
        void OnExit(wxCommandEvent &);
        void OnAbout(wxCommandEvent &);
        
        void ShowAbout();
        void OnAboutClose(wxCloseEvent &event);
        
        void ShowOptions();
        void OnOptionsClose(wxCloseEvent &event);
        
    private:
        wxMenu
        *menu1,
        *menu2;
        
        wxMenuItem
        *menuitem1,
        *menuitem2,
        *menuitem3,
        *menuitem4;
        
        Options
        *options = NULL;
        
        About
        *about = nullptr;
        
        wxDECLARE_EVENT_TABLE();
};

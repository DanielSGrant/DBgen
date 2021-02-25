#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class Listbox : public wxListBox
{
    public:
        Listbox(wxWindow *);
        ~Listbox();
        
    public:
        void OnKeyDown(wxKeyEvent &);
        
    private:
        wxDECLARE_EVENT_TABLE();
};

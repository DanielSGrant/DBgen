#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class Listbox : public wxListBox
{
public:
    Listbox(wxWindow*);
    ~Listbox();

public:
    void Create();
    void OnKeyDown(wxKeyEvent &event);
};

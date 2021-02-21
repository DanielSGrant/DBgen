#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class AboutFrame : public wxFrame
{
public:
    AboutFrame(wxWindow*);
    ~AboutFrame();

public:
    void OnExit(wxCommandEvent &event);

private:
    wxPanel
    *panel;

    wxButton
    *button;

    wxStaticText
    *title1,
    *title2,
    *title3,
    *name1,
    *name2,
    *email1,
    *email2,
    *license,
    *copyright;

    wxDECLARE_EVENT_TABLE();
};

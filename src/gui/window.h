#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class Window : public wxFrame
{
public:
    Window();
    ~Window();

public:
    void OnExit(wxCommandEvent &event);
    void Browse(wxCommandEvent &event);
    void Make(wxCommandEvent &event);
    void Merge(wxCommandEvent &event);
    void OnTimer(wxTimerEvent &event);

private:
    wxMenuBar *menubar;

    wxStaticText
    *text;

    wxButton
    *browse_button,
    *make_button,
    *merge_button;

    wxListBox
    *listbox;

    wxTimer
    *timer;

    wxDECLARE_EVENT_TABLE();
};

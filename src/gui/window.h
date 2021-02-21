#pragma once
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
    void OnTimer(wxTimerEvent&);
    void OnBrowse(wxCommandEvent&);
    void OnMake(wxCommandEvent&);
    void OnMerge(wxCommandEvent&);
    void OnExit(wxCommandEvent&);

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

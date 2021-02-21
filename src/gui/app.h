#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "window.h"


class App : public wxApp
{
public:
    App();
    ~App();

private:
    void Bootstrap();

    Window*
    window = nullptr;

public:
    virtual bool OnInit();
};

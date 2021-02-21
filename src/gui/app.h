#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "window.h"


class App : public wxApp
{
public:
    App();

private:
    void OnBootstrap();

    Window
    *window = nullptr;

public:
    virtual bool OnInit();
    void SetRestart(bool flag) { restart = flag; }

protected:
    bool restart;

    virtual ~App()
    {
        if (restart)
        {
            wxExecute(argv[0]);
        }
    };
};

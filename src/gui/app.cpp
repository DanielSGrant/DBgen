#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <filesystem>
#include <string>

#include "app.h"
#include "ini.h"
#include "utilities.h"

namespace fs = std::filesystem;


wxIMPLEMENT_APP(App);

App::App()
{

}

App::~App()
{

}

bool App::OnInit()
{
    this->Bootstrap();

    window = new Window();
    window->Show(true);

    return true;
}

void App::Bootstrap()
{
    std::string path = get_base_path();

    fs::path preferences = path;
    preferences /= "preferences.ini";

    if (!exists(preferences))
    {
        fs::path input = path;
        input /= "input";

        fs::path output = path;
        output /= "output";

        set_default_preferences(input, output, preferences);
    }

    mINI::INIFile file(preferences.string());
    mINI::INIStructure ini;
    file.read(ini);

    std::string &in = ini["directory"]["input"];
    std::string &out = ini["directory"]["output"];

    fs::path input = in;
    fs::path output = out;

    fs::create_directories(input);
    fs::create_directories(output);
}

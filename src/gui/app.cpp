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
    this->OnBootstrap();
}

bool App::OnInit()
{
    restart = false;
    
    if (!wxApp::OnInit())
        return false;
        
    window = new Window();
    window->Show(true);
    
    return true;
}

void App::OnBootstrap()
{
    std::string base = get_base_path();
    fs::path options = base / fs::path("options.ini");
    
    if (!exists(options))
    {
        fs::path input = base / fs::path("input");
        fs::path output = base / fs::path("output");
        set_default_options(input, output, options);
    }
    
    mINI::INIFile file(options.string());
    mINI::INIStructure ini;
    file.read(ini);
    
    fs::path input = fs::path(ini["directory"]["input"]);
    fs::path output = fs::path(ini["directory"]["output"]);
    
    fs::create_directories(input);
    fs::create_directories(output);
}

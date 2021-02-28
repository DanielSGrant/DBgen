#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "ini.h"
#include "whereami.h"

namespace fs = std::filesystem;


std::string get_base_path()
{
    char *path = NULL;
    int length, dirname_length;
    std::string base;
    
    length = wai_getExecutablePath(NULL, 0, &dirname_length);
    
    if (length > 0)
    {
        path = (char *) malloc(length + 1);
        
        if (!path)
            abort();
            
        wai_getExecutablePath(path, length, &dirname_length);
        path[dirname_length] = '\0';
        
        base.assign(path);
        free(path);
    }
    
    return base;
}

void set_default_options(fs::path input, fs::path output, fs::path options)
{
    mINI::INIFile file(options.string());
    mINI::INIStructure ini;
    
    ini["directory"]["input"] = input.string();
    ini["directory"]["output"] = output.string();
    
    ini["options"]["autoscan"] = "true";
    ini["options"]["recursive"] = "false";
    
    file.generate(ini, true);
}

std::vector<std::string> autoscan()
{
    std::string base = get_base_path();
    fs::path options = base / fs::path("options.ini");
    
    mINI::INIFile file(options.string());
    mINI::INIStructure ini;
    file.read(ini);
    
    fs::path input = fs::path(ini["directory"]["input"]);
    std::string &autoscan = ini["options"]["autoscan"];
    std::string &recursive = ini["options"]["recursive"];
    
    std::vector<std::string> files;
    
    if (autoscan == "true")
    {
        if (recursive == "true")
        {
            for (const auto &e : fs::recursive_directory_iterator(input))
            {
                if (e.path().extension() == ".fasta" || e.path().extension() == ".gb")
                {
                    std::string path = e.path().string();
                    files.push_back(path);
                }
            }
        }
        else
        {
            for (const auto &e : fs::directory_iterator(input))
            {
                if (e.path().extension() == ".fasta" || e.path().extension() == ".gb")
                {
                    std::string path = e.path().string();
                    files.push_back(path);
                }
            }
        }
        
    }
    
    return files;
}

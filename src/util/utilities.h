#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;


std::string get_base_path();

std::vector<std::string> autoscan();

void set_default_preferences(fs::path, fs::path, fs::path);

void initialize();

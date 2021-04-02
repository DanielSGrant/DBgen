#include <string>
#include <filesystem>

namespace fs = std::filesystem;


struct Sequence;
struct Gene;
struct Node;

void getGBData(Node **, fs::path);
void writeList(struct Node *node, fs::path);
void addGene(struct Node **head, Gene Gene_data);
void DatabaseMaker(fs::path, fs::path);
void deleteList(Node **head);
void upCase(std::string &);
// void displayList(struct Node *node);

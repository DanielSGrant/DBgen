#include <string>
#include <filesystem>

namespace fs = std::filesystem;


struct Sequence;
struct Gene;
struct Node;

void DatabaseMerge(fs::path, fs::path, fs::path);
void readList(Node **, Node **, std::string, std::string);
void addGene(struct Node **head, Gene Gene_data);
bool checkUniques(Node **, const Gene &);
void writeList(struct Node *, struct Node *, std::string, std::string);
void deleteList(Node **head);
// void displayList(struct Node *node);

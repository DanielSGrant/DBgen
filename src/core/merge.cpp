/*

This program creates a merges two fasta databases of format:
--------------------------------------------------
>Kindgom;Phylum;Class;Order;Family:Genus:Species;
NNNNNNNNNNN ...          ... NNNNNNNNNNNNNNNNNNN

>Kindgom;Phylum;Class;Order;Family:Genus:Species;
NNNNNNNNNNN ...          ... NNNNNNNNNNNNNNNNNNN
--------------------------------------------------
Author: Daniel Grant
Email:  d.grant@uleth.ca
Date:   Feb 10, 2021
--------------------------------------------------
Input: two .fasta files

*/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <string>

#include "merge.h"

namespace fs = std::filesystem;


// struct Sequence
// {
//     std::string cds;
//     struct sequence *next;
// };

struct Gene
{
    std::string taxonomy;
    // struct Sequence sequence;
    std::string sequence;
};

struct Node
{
    struct Gene gene;
    struct Node *next;
};


const int ASCII9 = static_cast<int> ('9');


//
// Description:     This function merges two databases and keeps unique values
//
// Parameter(s)     Input:  The path of two inputs and one output
//                  Output:
//                  I/O:
// Returns:
//

void DatabaseMerge(fs::path input1, fs::path input2, fs::path output)
{
    struct Node *uniques = NULL, *repeats = NULL;

    // Separate input into components
    fs::path base1 = input1.parent_path();
    fs::path filename1 = input1.stem();
    fs::path extension1 = input1.extension();

    fs::path base2 = input2.parent_path();
    fs::path filename2 = input2.stem();
    fs::path extension2 = input2.extension();

    fs::path unique = output / fs::path("merged_uniques.fasta");
    fs::path repeat = output / fs::path("merged_repeats.fasta");

    // Input
    std::string path1 = (base1 / filename1).string() + extension1.string();
    std::string path2 = (base2 / filename2).string() + extension2.string();

    // Output
    std::string path3 = unique.string();
    std::string path4 = repeat.string();

    // Reading in files and creating linked lists
    readList(&uniques, &repeats, path1, path2);

    // Writing files to unique and repeat files
    writeList(uniques, repeats, path3, path4);

    // Deleting lists and freeing allocated memory
    deleteList(&uniques);
    deleteList(&repeats);
}

//
// Description:     This function reads data from the opened files into a linked list
//
// Parameter(s)     Input:  The filenames for both input files
//                  Output:
//                  I/O:    Node **uniques
//                          Node **repeats
//                          std::string input1
//                          std::string input2
//
// Returns:
//

void readList(Node **uniques, Node **repeats, std::string input1, std::string input2)
{
    Gene gene;

    std::ifstream file1;
    file1.open(input1);

    while (file1 >> gene.taxonomy >> gene.sequence)
    {
        // Repeat until entire file is in linked list
        addGene(uniques, gene);
    }

    // Close first file
    file1.close();


    std::ifstream file2;
    file2.open(input2);

    // Read in the first data point
    while (file2 >> gene.taxonomy >> gene.sequence)
    {
        // Append new read to uniques linked list if unique
        if (checkUniques(uniques, gene))
        {
            addGene(uniques, gene);
        }
        // Append read to repeats if false
        else
        {
            addGene(repeats, gene);
        }
    }

    // Close second file
    file2.close();
}

//
// Description:    This function appeds a new node to a linked list
//
// Parameter(s):   Input:   Gene Gene_data
//                 Output:
//                 I/O:     Node **head
//
// Returns:
//

inline void addGene(struct Node **head, Gene Gene_data)
{
    // Create and allocate new node
    struct Node* newNode = new Node;
    struct Node* last = *head;

    // Assign data to the node
    newNode->gene = Gene_data;

    // Make next pointer of new node NULL
    newNode->next = NULL;

    // If list is empty, new node becomes first node
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    // else traverse to last node
    while (last->next != NULL)
    {
        last = last->next;
    }

    // Change next of last node
    last->next = newNode;
    return;
}

//
// Description:    This function checks whether a gene is a unique value or a repeat
//
// Parameter(s):   Input:   Names of two input and two output file names
//                 Output:
//                 I/O:
// Returns:
//

bool checkUniques(Node **head, const Gene &gene)
{
    // Dereference to get the real head
    Node *current = *head;

    // Read to the end of the list, comparing values to the gene
    while (current != NULL)
    {
        if (current->gene.taxonomy == gene.taxonomy && current->gene.sequence == gene.sequence)
        {
            return false;
        }

        current = current->next;
    }

    return true;
}

//
// Description:    This writes the contents of a linked list to 2 output files
//
// Parameter(s):   Input:   Names of two output file names
//                 Output:
//                 I/O:     Node *uniques
//                          Node *repeats,
//                          std::string output1
//                          std::string output2
//
// Returns:
//

void writeList(struct Node *uniques, struct Node *repeats, std::string output1, std::string output2)
{
    std::ofstream file1;
    file1.open(output1);

    // Traverse the list to print each node to uniques output file
    while (uniques != NULL)
    {
        file1 << uniques->gene.taxonomy << std::endl << uniques->gene.sequence << std::endl;
        uniques = uniques->next;
    }

    // Close uniques output file
    file1.close();

    std::ofstream file2;
    file2.open(output2);

    // Traverse the list to print each node to repeats output file
    while (repeats != NULL)
    {
        file2 << repeats->gene.taxonomy << std::endl << repeats->gene.sequence << std::endl;
        repeats = repeats->next;
    }

    // Close repeats output file
    file2.close();
}

//
// Description:    This function frees all allocated memory from a linked list
//
// Parameter(s):   Input:
//                 Output:
//                 I/O:     Node **head
//
// Returns:
//

inline void deleteList(Node **head)
{

    // Deref  to get the real head
    Node* current = *head;
    Node* next = NULL;

    // Read until the end of list, deleting each node
    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }

    // Deref head_ref to affect the real head back in the caller.
    *head = NULL;
}

// // A function for displaying a linked list. Testing purposes only.

// inline void displayList(struct Node *node)
// {
//    // Traverse the list to display each node
//     while (node != NULL)
//     {
//         std::cout << node->gene.taxonomy << std::endl;
//         node = node->next;
//     }

//     if (node== NULL)
//         std::cout << "Finished Displaying List" << std::endl;
// }

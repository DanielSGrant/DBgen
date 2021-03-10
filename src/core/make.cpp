/*

This program creates a database in the format of a fasta file of form
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
Input: sequence.gb file from NCBI

*/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

#include "make.h"

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
    std::vector<std::string> sequence;
};

struct Node
{
    struct Gene gene;
    struct Node *next;
};

const int ASCII9 = static_cast<int>('9');


void DatabaseMaker(fs::path input, fs::path output)
{
    struct Node *head = NULL;
    
    // Pull information from .gb file
    getGBData(&head, input);
    
    // Write valid and invalid data to output files
    writeList(head, output);
    
    // Free allocated memory
    deleteList(&head);
}

//
// Description:     This function reads in genbank data from the opened file into an linked list
//
// Parameter(s):    Input:  string input -   input file name
//                  Output:
//                  I/O:    Node **data -    pointer to linked list
//                          fs::path input - input file
//
// Returns:
//

void getGBData(Node **data, fs::path input)
{
    std::ifstream in;
    
    fs::path base = input.parent_path();
    fs::path filename = input.stem();
    fs::path extension = input.extension();
    std::string file = (base / filename).string() + extension.string();
    
    in.open(file);
    
    // Variable declaration
    std::string temp, tax, species, sequence;
    std::vector <std::string> seqVec;
    int stringCount;
    Gene tempGene;
    bool write;
    
    while (in >> temp)
    {
        write = true;
        
        // Reset tax to empty string for next round of reads
        tax = "";
        sequence = "";
        
        // Read until you hit ORGANISM. then read in taxonomy
        if (temp == "ORGANISM")
        {
            // Get full line for species
            getline(in, species);
            
            // Remove unwanted spaces from species name if they exist
            if (species[0] == ' ')
            {
                species = species.substr(species.find_first_not_of(' '), species.length() - 1);
            }
            
            //Read in taxonomy
            do
            {
                in >> temp;
                
                // Remove unwanted group and terms from taxonomy if present
                if (temp.find("group") != std::string::npos)
                {
                    tax = tax.substr(0, tax.find_last_of(";") + 1);
                }
                else if (temp.find("environmental") != std::string::npos)
                {
                    tax = tax.substr(0, tax.find_last_of(";") + 1);
                }
                else if (temp.find("unclassified") != std::string::npos)
                {
                    tax = tax.substr(0, tax.find_last_of(";") + 1);
                }
                else if (temp.find("samples") != std::string::npos)
                {
                    tax = tax.substr(0, tax.find_last_of(";") + 1);
                }
                // If the program reads to far into the next field terinate loop
                else if (temp == "REFERENCE")
                {
                    tax.back() = '.';
                }
                // Add next member of taxonomy
                else
                {
                    tax += temp;
                }
                
            }
            while (tax[tax.length() - 1] != '.');
            
            // Change period at end of genus to semicolon
            tax.back() = ';';
            
            // Concatenate species onto string of taxonomix data
            tax += species + ";";
            
            // Change spaces and any other punctuation to underscore character
            for (int i = 0; i < static_cast<int>(tax.length()); i++)
            {
                if (tax[i] == '.')
                {
                    tax.erase(i, 1);
                }
                
                if (tax[i] == ' ' || tax[i] == '-' || tax[i] == ':' || tax[i] == '=')
                {
                    tax[i] = '_';
                }
            }
            
            // Read until sequence data starts or you hit the end of that data point
            while (temp != "ORIGIN" && in >> temp)
            {
                //If there is no sequence data break to avoid writing incomplete data
                if (temp == "//")
                {
                    write = false;
                    break;
                }
                
            }
            
            // If you reach ORIGIN, read in the sequence data
            if (temp == "ORIGIN")
            {
                in >> temp;
                stringCount = 0;
                do
                {
                    if (static_cast<int>(temp[0]) > ASCII9 && (temp[0] == 'a' || temp[0] == 'c' ||
                            temp[0] == 'g' || temp[0] == 't' || temp[0] == 'n'))
                    {
                        sequence += temp;
                        stringCount++;
                    }
                    //If string length is over 10000 BP, push to vector and reset to avoid overflow
                    if(stringCount > 1000)
                    {
                        seqVec.push_back(sequence);
                        stringCount = 0;
                    }
                    
                    in >> temp;
                    
                }
                while (temp != "//");
                //Push latest sequence to seqVec
                seqVec.push_back(sequence);
            }
            
            // Write data to array if new data is available
            if (write)
            {
                tempGene.taxonomy = tax;
                tempGene.sequence = seqVec;
                addGene(data, tempGene);
            }
        }
    }
    
    // Close input file
    in.close();
}

//
// Description:     This function appeds a new node to a linked list
//
// Parameter(s):    Input:  Gene Gene_data
//                  Output:
//                  I/O:    Node **head
//
// Returns:
//

inline void addGene(struct Node **head, Gene Gene_data)
{
    // Create and allocate new node
    struct Node *newNode = new Node;
    struct Node *last = *head;
    
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
// Description:     This function writes the values stored in a linked list to 2 output files
//
// Parameter(s)     Input:  The strings containing names of output files
//                  Output:
//                  I/O:    Node *node,
//                          fs::path output
//
// Returns:
//

void writeList(struct Node *node, fs::path output)
{
    bool isValid;
    int count;
    
    fs::path base = output.parent_path();
    fs::path filename = output.stem();
    fs::path extension = output.extension();
    
    std::string valid_file = (base / filename).string() + "_valid.fasta";
    std::string invalid_file = (base / filename).string() + "_invalid.fasta";
    
    std::ofstream valid, invalid;
    valid.open(valid_file);
    invalid.open(invalid_file);
    
    // Traverse the list to print each node to output file
    while (node != NULL)
    {
        // Reset variables
        isValid = false;
        count = 0;
        
        // Check how many entries there are for taxonomy
        for (int i = 0; i < static_cast<int>(node->gene.taxonomy.length()); i++)
        {
            if (node->gene.taxonomy[i] == ';')
            {
                count++;
            }
        }
        
        // If there are less than 8 pieces of taxonomy info it is valid
        if (count <= 7)
        {
            isValid = true;
        }
        
        // Write valids to valid output file and invalids to invalid output file
        if (isValid)
        {
            valid << ">" << node->gene.taxonomy << std::endl;
            for(auto i = node->gene.sequence.begin(); i != node->gene.sequence.end();i++)
            {
                valid << *i;
            }
            valid << std::endl;
                
        }
        else
        {
            invalid << ">" << node->gene.taxonomy << std::endl;
            for(auto i = node->gene.sequence.begin(); i != node->gene.sequence.end();i++)
            {
                invalid << *i;
            }
            invalid << std::endl;
        }
        
        // Move to next node
        node = node->next;
    }
    
    if (node == NULL)
    {
        return;
    }
}

//
// Description:     This function frees all allocated memory from a linked list
//
// Parameters       Input:
//                  Output:
//                  I/O:    Node **head
//
// Returns:
//

inline void deleteList(Node **head)
{

    // Deref to get the real head
    Node *current = *head;
    Node *next = NULL;
    
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

// // A function for displaying a linked list. Testing purposes only

// inline void displayList(struct Node *node)
// {
//     // Traverse the list to display each node
//     while (node != NULL)
//     {
//         std::cout << node->gene.taxonomy << std::endl
//         << node->gene.sequence << std::endl;
//         node = node->next;
//     }

//     if (node== NULL)
//         std::cout << "Finished Displaying List" << std::endl;
// }

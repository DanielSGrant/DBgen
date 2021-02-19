/*This program creates a merges two fasta databases of format
--------------------------------------------------
>Kindgom;Phylum;Class;Order;Family:Genus:Species;
NNNNNNNNNNN ...          ... NNNNNNNNNNNNNNNNNNN
>Kindgom;Phylum;Class;Order;Family:Genus:Species;
NNNNNNNNNNN ...          ... NNNNNNNNNNNNNNNNNNN
--------------------------------------------------
Author: Daniel Grant
d.grant@uleth.ca
Feb 10, 2021
Input Data: two .fasta files
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

// struct Sequence
// {
// 	std::string cds;
// 	struct sequence *next;
// };

struct Gene
{
	std::string taxonomy;
	//struct Sequence sequence;
	std::string sequence; 
};

struct Node
{
	struct Gene gene;
	struct Node *next;
};

void addGene(struct Node **, Gene);
void writeList(struct Node *node, std::ofstream &, std::ofstream &, std::string, std::string);
void deleteList(Node**);
void DatabaseMaker(std::string, std::string, std::string);
void DatabaseMerge(std::string, std::string, std::string, std::string);
void readList(std::ifstream &, std::string, std::ifstream &, std::string, Node **, Node **);
bool checkUniques(Node**, const Gene &);
void writeList(struct Node *, std::ofstream &, std::string, struct Node *, std::ofstream &, std::string);

const int ASCII9 = static_cast <int> ('9');

int main()
{
	DatabaseMerge("./valid.fasta", "./invalid.fasta", "./uniques.fasta", "./repeats.fasta");
	return 0;
}


//Function description: This function merges two databases and keeps unique values
//Funtion parameters Input: Names of two input and two output file names
//                  Output: 
//                  Input/Output: 
//Returns:
void DatabaseMerge(std::string inputFile1, std::string inputFile2, std::string outputFile1, std::string outputFile2)
{
	std::ifstream in1, in2;
	std::ofstream out1, out2;
	struct Node *uniques = NULL, *repeats = NULL;
	
	//Reading in files and creating linked lists
	readList(in1, inputFile1, in2, inputFile2, &uniques, &repeats);
	//Writing files to unique and repeat files
	writeList(uniques, out1, outputFile1, repeats, out2, outputFile2);
	//Deleting lists and freeing allocated memory
	deleteList(&uniques);
	deleteList(&repeats);
}

//Function description This function reads data from the opened files into a linked list
//Funtion parameters Input: filenames for both input files
//                  Output:
//                  Input/Output: ifstream &in1 and &in2, Node **uniques and **repeats
//Returns:
void readList(std::ifstream &in1, std::string input1, std::ifstream &in2, std::string input2, Node **uniques, Node **repeats)
{
	Gene gene;

	//Open and process first file
	do
	{
		in1.open(input1.c_str());
		if(in1.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> input1;
		}
	}
	while(in1.fail());

	//Read in the first data point
	std::cout << "First input file for database merging opened successfully" << std::endl;
	

	while(in1 >> gene.taxonomy >> gene.sequence)
	{
		//Repeat until entire file is in linked list
		addGene(uniques, gene);
	}

	//close first file
	in1.close();

	//Open second file
	do
	{
		in2.open(input2.c_str());
		if(in2.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> input2;
		}
	}
	while(in2.fail());

	std::cout << "Second input file for database merging opened successfully" << std::endl;

	//Read in the first data point
	

	while(in2 >> gene.taxonomy >> gene.sequence)
	{
		//Append new read to uniques linked list if unique
		if(checkUniques(uniques, gene))
		{
			addGene(uniques, gene);
		}
		//Append read to repeats if false
		else
		{
			addGene(repeats, gene);
		}
	}
	//close second file
	in2.close();

}

//Function description: This function appeds a new node to a linked list
//Funtion parameters Input: Gene Gene_data
//                  Output: 
//                  Input/Output: Node **head 
//Returns:
void addGene(struct Node **head, Gene Gene_data)
{
	//Create and allocate new node
	struct Node* newNode = new Node;
	struct Node* last = *head;

	//Assign data to the node
	newNode -> gene = Gene_data;

	//Make next pointer of new node NULL
	newNode -> next = NULL;

	//if List is empty, new node becomes first node
	if(*head == NULL)
	{
		*head = newNode;
		return;
	}

	//else traverse to last node
	while(last -> next != NULL)
	{
		last = last -> next;
	}

	//change next of last node
	last -> next = newNode;
	return;
}

//Function description: This function checks whether a gene is a unique value or a repeat
//Funtion parameters Input: Names of two input and two output file names
//                  Output: 
//                  Input/Output: 
//Returns:
bool checkUniques(Node** head, const Gene &gene)
{
    // dereference to get the real head
    Node* current = *head;

 	//Read to the end of the list, comparing values to the gene
    while (current != NULL) 
    {
        if(current->gene.taxonomy == gene.taxonomy && current->gene.sequence == gene.sequence)
        {
        	return false;
        }
        current = current->next;
    }
 
    return true;
}

//Function description: This writes the contents of a linked list to 2 output files
//Funtion parameters Input: Names of two output file names
//                  Output: 
//                  Input/Output: Node *uniques and * repeats, ofstream &out1 and &out2
//Returns:
void writeList(struct Node *uniques, std::ofstream &out1, std::string output1, struct Node *repeats, std::ofstream &out2, std::string output2)
{
	//open files
   do
	{
		out1.open(output1.c_str());
		if(out1.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> output1;	
		}

	}
	while(out1.fail());

	do
	{
		out2.open(output2.c_str());
		
		if(out2.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> output2;	
		}
	}
	while(out2.fail());

	std::cout << "Output files opened successfully, writing to output files." << std::endl;

   //traverse the list to print each node to uniques output file
   while (uniques != NULL)
   {
   		out1 << ">" << uniques->gene.taxonomy << std::endl << uniques->gene.sequence << std::endl;
   		uniques = uniques->next;
		
   }

   //close uniques output file
   out1.close();

	//traverse the list to print each node to repeats output file
   while (repeats != NULL)
   {
   		out2 << ">" << uniques->gene.taxonomy << std::endl << uniques->gene.sequence << std::endl;
   		repeats = repeats->next;
		
   }
 
 	//close repeats output file
	out2.close();
}


//Function description: This function frees all allocated memory from a linked list
//Funtion parameters Input: 
//                  Output: 
//                  Input/Output: Node **head
//Returns:
void deleteList(Node** head)
{
 
    /* deref  to get the real head */
    Node* current = *head;
    Node* next = NULL;
 	
 	//Read until the end of list, deleting each node
    while (current != NULL) 
    {
        next = current->next;
        delete current;
        current = next;
    }
 
    // deref head_ref to affect the real head back in the caller.
    *head = NULL;
}



//Function for displaying a linked list, for testing purposes only
// void displayList(struct Node *node)
// {
//    //traverse the list to display each node
//    while (node != NULL)
//    {
//       std::cout << node->gene.taxonomy << std::endl 
//       << node->gene.sequence << std::endl;
//       node = node->next;
//    }
 
// 	if(node== NULL)
// 	std::cout << "Finished Displaying List" << std::endl; 
// } 

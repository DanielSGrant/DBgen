/*This program creates a database in the format of a fasta file of form
--------------------------------------------------
>Kindgom;Phylum;Class;Order;Family:Genus:Species;
NNNNNNNNNNN ...          ... NNNNNNNNNNNNNNNNNNN
>Kindgom;Phylum;Class;Order;Family:Genus:Species;
NNNNNNNNNNN ...          ... NNNNNNNNNNNNNNNNNNN
Author: Daniel Grant
d.grant@uleth.ca
Feb 10, 2021
--------------------------------------------------
Input Data: sequence.fasta and sequence.gb files from NCBI
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

void getGBData(std::ifstream &, Node **, std::string);
void addGene(struct Node **, Gene);
void writeList(struct Node *node, std::ofstream &, std::ofstream &, std::string);
void deleteList(Node**);
void DatabaseMaker(std::string, std::string);
void DatabaseMerge(std::string, std::string, std::string);
void readList(std::ifstream &, std::string, std::ifstream &, std::string, Node **, Node **);
bool checkUniques(Node**, const Gene &);
void writeList(struct Node *, std::ofstream &, struct Node *, std::ofstream &, std::string);

const int ASCII9 = static_cast <int> ('9');

int main()
{
	//DatabaseMaker("./sequence.gb", "./" );
	DatabaseMerge("./valid.fasta", "./invalid.fasta", "./");
	return 0;
}

void DatabaseMaker(std::string inputFile, std::string outputFilepath)
{
	std::ifstream in;
	std::ofstream valid, invalid; 
	struct Node *head = NULL;


	//Pull information from .gb file
	getGBData(in, &head, inputFile);
	writeList(head, valid, invalid, outputFilepath);
	deleteList(&head);
}

//Function description: This function reads in genbank data from the opened file into an linked list
//Funtion parameters Input:
//                  Output: 
//                  Input/Output: ifstream in, ofstream out;
//Returns:
void getGBData(std::ifstream &in, Node **data, std::string input)
{
	
	do
	{
		in.open(input.c_str());
		if(in.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> input;
		}
	}
	while(in.fail());

	std::cout << "Input file opened successfully" << std::endl;
	
	std::string temp, tax, species, sequence;
	Gene tempGene;
	bool write;

	in >> temp;
	while(!in.eof())
	{
		write = true;
		//Reset tax to empty string for next round of reads
		tax = "";
		sequence = "";


		//Read until you hit ORGANISM. then read in taxonomy
		if(temp == "ORGANISM")
		{
			//get full line for species
			getline(in, species);

			//Remove unwanted spaces from species name if they exist
			if(species[0] == ' ')
			{
				species = species.substr(species.find_first_not_of(' '),species.length() - 1);
			}

			while(tax[tax.length()-1] != '.')
			{

				in >> temp;

				//Remove unwanted group and terms from taxonomy if present
				if (temp.find("group") != std::string::npos) 
				{
					tax = tax.substr(0,tax.find_last_of(";") + 1);
				}
				else if (temp.find("environmental") != std::string::npos) 
				{
					tax = tax.substr(0,tax.find_last_of(";") + 1);
				}
				else if (temp.find("unclassified") != std::string::npos) 
				{
					tax = tax.substr(0,tax.find_last_of(";") + 1);
				}
				else if (temp.find("samples") != std::string::npos) 
				{
					tax = tax.substr(0,tax.find_last_of(";") + 1);
				}
				//If the program reads to far into the next field
				else if (temp == "REFERENCE") 
				{
					tax[tax.length()-1] = '.';
				}
				//Add next member of taxonomy
				else
				{
					tax += temp;
				}   
			}

			//change period at end of genus to semicolon
			tax[tax.length() - 1] = ';';
			//concatenate species onto string of taxonomix data
			tax += species + ";";
			//change spaces and any other punctuation to underscore character
			for(int i = 0; i < static_cast <int> (tax.length()); i++)
			{
				if(tax[i] == '.')
				{
					tax.erase(i,1);
				}

				if(tax[i] == ' ' || tax[i] == '-' || tax[i] == ':' || tax[i] == '=')
				{
					tax[i] = '_';
				}

			}

			//Read until sequence data starts or
			while(temp != "ORIGIN" && !in.eof())
			{
				in >> temp;
				if(temp == "//")
				{
					write = false;
					break;
				}
				
			}
			if(temp == "ORIGIN")
			{
				in >> temp;
				do
				{
					if(static_cast <int> (temp[0]) > ASCII9 && (temp[0] == 'a' || temp[0] == 'c' ||
						temp[0] == 'g' || temp[0] == 't' || temp[0] == 'n'))
					{
						sequence += temp;
					}
					
					in >> temp;	
				}
				while(temp != "//");
				
			}
			//write data to array
			if(write)
			{
				tempGene.taxonomy = tax;
				tempGene.sequence = sequence;
				addGene(data, tempGene);
			}
			

		}
		
		//read in new value for next loop
		in >> temp;

	}

	in.close();

}

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

void writeList(struct Node *node, std::ofstream &valid, std::ofstream &invalid, std::string output)
{
   std::string v = output + "valid.fasta";
   std::string i = output + "invalid.fasta";
   bool isValid;
   int count;

   do
	{
		valid.open(v.c_str());
		if(valid.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> v;	
		}

	}
	while(valid.fail());

	do
	{
		invalid.open(i.c_str());
		
		if(invalid.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> i;	
		}
	}
	while(invalid.fail());

	std::cout << "Output files opened successfully, writing to output files." << std::endl;

   //traverse the list to display each node
   while (node != NULL)
   {
   		isValid = false;
   		count = 0;
   		
   		
   		for(int i = 0; i < static_cast <int> (node->gene.taxonomy.length()); i++)
   		{
   			if(node->gene.taxonomy[i] == ';')
   			{
   				count++;
   			}
   			
   		}
   		
   		if(count <= 8)
		{
			isValid = true;
		}

   		if(isValid)
   		{
   			valid << ">" << node->gene.taxonomy << std::endl 
			<< node->gene.sequence << std::endl;
			
   		}
   		else
   		{
   			invalid << ">" << node->gene.taxonomy << std::endl 
			<< node->gene.sequence << std::endl;
   		}
   		node = node->next;
		
   }
 
	if(node== NULL)
	return;
} 

void deleteList(Node** head)
{
 
    /* deref  to get the real head */
    Node* current = *head;
    Node* next = NULL;
 
    while (current != NULL) 
    {
        next = current->next;
        delete current;
        current = next;
    }
 
    /* deref head_ref to affect the real head back
        in the caller. */
    *head = NULL;
}

/*****************************************************************************
Functions for database merger
******************************************************************************/

void DatabaseMerge(std::string inputFile1, std::string inputFile2, std::string outputFilepath)
{
	std::ifstream in1, in2;
	std::ofstream out1, out2;
	struct Node *uniques = NULL, *repeats = NULL;

	std::cout << "Variables created" << std::endl;
	
	readList(in1, inputFile1, in2, inputFile2, &uniques, &repeats);
	std::cout << "Files read into linked list" << std::endl;
	writeList(uniques, out1, repeats, out2, outputFilepath);
	std::cout << "New files written" << std::endl;

	deleteList(&uniques);
	deleteList(&repeats);
	std::cout << "Lists deleted" << std::endl;
}

//Function description This function reads data from the opened files into a linked list
//Funtion parameters Input:
//                  Output:
//                  Input/Output: gene [], int &size
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
	std::cout << "File 1 opened" << std::endl;

	//Read in the first data point
	in1 >> gene.taxonomy >> gene.sequence;

	while(!in1.eof())
	{
		//Repeat until entire file is in linked list
		addGene(uniques, gene);
		in1 >> gene.taxonomy >> gene.sequence;
	}

	//close first file
	in1.close();

	std::cout << "File1 Closed" << std::endl;
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
	std::cout << "File 2 Opened" << std::endl;

	//Read in the first data point
	in2 >> gene.taxonomy >> gene.sequence;

	while(!in2.eof())
	{
		std::cout << "Loop entered" << std::endl;
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
		std::cout << "Finished checking uniques" << std::endl;
		in2 >> gene.taxonomy >> gene.sequence;
	}
	//close second file
	in2.close();
	std::cout << "File 2 closed" << std::endl;

}

bool checkUniques(Node** head, const Gene &gene)
{
    std::cout << "Checking uniques" << std::endl;
    // dereference to get the real head
    Node* current = *head;

 
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

void writeList(struct Node *uniques, std::ofstream &out1, struct Node *repeats, std::ofstream &out2, std::string output)
{
   std::string u = output + "uniques.fasta";
   std::string r = output + "repeats.fasta";

   do
	{
		out1.open(u.c_str());
		if(out1.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> u;	
		}

	}
	while(out1.fail());

	do
	{
		out2.open(r.c_str());
		
		if(out2.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> r;	
		}
	}
	while(out2.fail());

	std::cout << "Output files opened successfully, writing to output files." << std::endl;

   //traverse the list to display each node
   while (uniques != NULL)
   {
   		out1 << ">" << uniques->gene.taxonomy << std::endl << uniques->gene.sequence << std::endl;
   		uniques = uniques->next;
		
   }

   //close uniues output file
   out1.close();

   while (repeats != NULL)
   {
   		out2 << ">" << uniques->gene.taxonomy << std::endl << uniques->gene.sequence << std::endl;
   		repeats = repeats->next;
		
   }
 
 	//close uniues output file
	out2.close();
}

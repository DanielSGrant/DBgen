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

void getGBData(std::ifstream &, Node **);
void addGene(struct Node **, Gene);
void writeList(struct Node *node, std::ofstream &, std::ofstream &);
void deleteList(Node**);


const int ASCII9 = static_cast <int> ('9');

int main()
{
	std::ifstream in;
	std::ofstream valid, invalid; 
	struct Node *head = NULL;


	//Pull information from .gb file
	getGBData(in, &head);
	//displayList(head);
	writeList(head, valid, invalid);
	deleteList(&head);

	return 0;
}

//Function description: This function reads in genbank data from the opened file into an linked list
//Funtion parameters Input:
//                  Output: 
//                  Input/Output: ifstream in, ofstream out;
//Returns:
void getGBData(std::ifstream &in, Node **data)
{
	std::string input = "sequence.gb";
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

	std::cout << "File opened successfully" << std::endl;
	
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

void writeList(struct Node *node, std::ofstream &valid, std::ofstream &invalid)
{
   std::string v = "valid.fasta";
   std::string i = "invalid.fasta";
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


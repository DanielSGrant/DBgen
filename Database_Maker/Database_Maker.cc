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
Input Data: sequence.gb file from NCBI
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
void writeList(struct Node *node, std::ofstream &, std::ofstream &, std::string, std::string);
void deleteList(Node**);
void DatabaseMaker(std::string, std::string, std::string);


const int ASCII9 = static_cast <int> ('9');

int main()
{
	DatabaseMaker("./sequence.gb", "./valid.fasta", "./invalid.fasta" );
	return 0;
}

void DatabaseMaker(std::string inputFile, std::string outputFile1, std::string outputFile2)
{
	std::ifstream in;
	std::ofstream valid, invalid; 
	struct Node *head = NULL;


	//Pull information from .gb file
	getGBData(in, &head, inputFile);
	//Write valid and invalid data to output files 
	writeList(head, valid, invalid, outputFile1, outputFile2);
	//Free allocated memory
	deleteList(&head);
}

//Function description: This function reads in genbank data from the opened file into an linked list
//Funtion parameters Input: string input - input file name
//                  Output: 
//                  Input/Output: ifstream in - input file, Node **data - pointer to linked list 
//Returns:
void getGBData(std::ifstream &in, Node **data, std::string input)
{
	//Open file
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

	std::cout << "Input file for database generation opened successfully" << std::endl;
	
	//Variable declaration
	std::string temp, tax, species, sequence;
	Gene tempGene;
	bool write;

	
	while(in >> temp)
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

			//Read in taxonomy
			do
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
				//If the program reads to far into the next field terinate loop
				else if (temp == "REFERENCE") 
				{
					tax.back() = '.';
				}
				//Add next member of taxonomy
				else
				{
					tax += temp;
				}   
			}
			while(tax[tax.length()-1] != '.');

			//change period at end of genus to semicolon
			tax.back() = ';';
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

			//Read until sequence data starts or you hit the end of that data point
			while(temp != "ORIGIN" && in >> temp)
			{
				if(temp == "//")
				{
					write = false;
					break;
				}
				
			}
			//if you reach ORIGIN, read in the sequence data
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
			//write data to array if new data is available
			if(write)
			{
				tempGene.taxonomy = tax;
				tempGene.sequence = sequence;
				addGene(data, tempGene);
			}
			

		}
		

	}
	//Close input file
	in.close();

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




//Function description: This function writes the values stored in a linked list to 2 output files
//Funtion parameters Input: strings containing names of output files
//                  Output: 
//                  Input/Output: Node *node, ofstream &valid and &invalid 
//Returns:
void writeList(struct Node *node, std::ofstream &valid, std::ofstream &invalid, std::string output1, std::string output2)
{
   bool isValid;
   int count;
   //Open first output file
   do
	{
		valid.open(output1.c_str());
		if(valid.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> output1;	
		}

	}
	while(valid.fail());

	//open second output file
	do
	{
		invalid.open(output2.c_str());
		
		if(invalid.fail())
		{
			std::cout << "Failed to open default filename, please enter filename: ";
			std::cin >> output2;	
		}
	}
	while(invalid.fail());

	std::cout << "Output files opened successfully, writing to output files." << std::endl;

   //traverse the list to print each node to output file
   while (node != NULL)
   {
   		//Reset variables
   		isValid = false;
   		count = 0;
   		
   		//Check how many entries there are for taxonomy
   		for(int i = 0; i < static_cast <int> (node->gene.taxonomy.length()); i++)
   		{
   			if(node->gene.taxonomy[i] == ';')
   			{
   				count++;
   			}
   			
   		}
   		//If there are less than 8 pieces of taxonomy info it is valid
   		if(count <= 8)
		{
			isValid = true;
		}
		//Write valids to valid output file and invalids to invalid output file
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
   		//Move to next node
   		node = node->next;
		
   }
 
	if(node== NULL)
	{
		return;	
	}
	
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
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


struct gene
{
	std::string taxonomy;
	std::string sequence[20]; 
};

void getGBData(std::ifstream &, std::string &, gene [], int &);

const int ARRAY_SIZE = 5000;

int main()
{
	std::ifstream in;
	std::ofstream out1, out2; 
	std::string input1, input2, output1, output2;
	gene data[ARRAY_SIZE];
	int size = 0;

	//Pull information from .gb file
	input1 = "sequence.gb";
	getGBData(in, input1, data, size);

	for(int i = 0; i < size; i++)
	{
		std::cout << data[i].taxonomy << std::endl << data[i].sequence[0] << std::endl;
	}

	return 0;
}

//Function description: This function reads in genbank data from the opened file into an array
//Funtion parameters Input:
//                  Output: 
//                  Input/Output: ifstream in, ofstream out;
//Returns:
void getGBData(std::ifstream &in, std::string &input, gene data[], int &s)
{
	do
	{
		in.open(input.c_str());
		std::cout << "Failed to open file, please enter filename: ";
		std::cin >> input;
	}
	while(in.fail());
	
	std::string temp, locus, tax, species, sequence;

	in >> temp;
	while(!in.eof())
	{
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
			for(unsigned int i = 0; i < tax.length(); i++)
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
			while(temp == "ORGANISM")
			{
				in >> temp;
				if(temp == "ORIGIN")
				{
					while(temp != "//")
					{
						sequence += temp;
						in >> temp;	
					}
					
					
				}
			}

		}
		//write data to array
		data[s].taxonomy = tax;
		data[s].sequence[0] = sequence;
		s++;
		//read in new value for next loop
		in >> temp;

	}

	in.close();

}

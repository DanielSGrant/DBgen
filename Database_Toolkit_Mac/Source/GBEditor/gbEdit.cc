//This file reads locus and taxonomy data out of a genbank file
//Input: Genbank file downloaded from NCBI
//Output: File consisting of locus and taxonomy information only
//Author: Daniel Grant - d.grant@uleth.ca
//Date: Feb 6, 2021

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void openFile(ifstream &);
void closeFile(ifstream &);
void openFile(ofstream &);
void closeFile(ofstream &);
void getData(ifstream &, ofstream &);
void writeFile(const string &, ofstream &);


int main()
{
	ifstream inFile;
	ofstream outFile;
	openFile(inFile);
  cout << "Pulling data from .gb file" << endl;
	openFile(outFile);
	getData(inFile, outFile);
	closeFile(inFile);
	closeFile(outFile);

  cout << "Done" << endl;
  return 0;
}


//Function description This function opens a file with a user specified name
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ifstream i -- input stream variable
//Returns:
void openFile(ifstream &file)
{
	string filename;
	do
	{
		cin >> filename;
		file.open(filename.c_str());
	}
	while (file.fail());
}

//Function description This function opens a file with a user specified name
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ifstream i -- input stream variable
//Returns:
void openFile(ofstream &file)
{
	string filename;
	do
	{
		cin >> filename;
		file.open(filename.c_str());
	}
	while (file.fail());
}

//Function description: This function reads in data from the opened file
//Funtion parameters Input:
//                  Output: int size -- actual array size, student array[] -- array of student type
//                  Input/Output: ifstream i -- input stream variable
//Returns:
void getData(ifstream &in, ofstream &out)
{
  string temp, locus, tax, species;
  in >> temp;
  
  while(!in.eof())
  {
    //Reset tax to empty string for next round of reads
  	tax = "";

    //Check to see if the locus for the next read
  	if(temp == "ACCESSION")
  	{
      //if so read in locus and write to outfile
  		in >> locus;
  		locus = ">" + locus;
  		writeFile(locus, out);
  	}
    //Read until you hit ORGANISM. then read in taxonomy
  	else if(temp == "ORGANISM")
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
  			if (temp.find("group") != string::npos) 
        {
          tax = tax.substr(0,tax.find_last_of(";") + 1);
        }
        else if (temp.find("environmental") != string::npos) 
        {
          tax = tax.substr(0,tax.find_last_of(";") + 1);
        }
        else if (temp.find("unclassified") != string::npos) 
        {
          tax = tax.substr(0,tax.find_last_of(";") + 1);
        }
        else if (temp.find("samples") != string::npos) 
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
      for(uint i = 0; i < tax.length(); i++)
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
      //write full taxonomy to output file
  		writeFile(tax, out);
  	}

    //read in new value for next loop
  	in >> temp;
  }
}


//Function description: This function writes data from the input file to the output file
//Funtion parameters Input: const string &data
//                  Output: 
//                  Input/Output: fstream &out 
//Returns:
void writeFile(const string &data, ofstream &out)
{
	out << data << "\n";
}

//Function description This function closes an open input file
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ifstream i - input stream variable
//Returns:
void closeFile(ifstream &file)
{
  file.close();
}

//Function description This function closes an open output file
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ofstream &i - output stream variable
//Returns:
void closeFile(ofstream &file)
{
  file.close();
}
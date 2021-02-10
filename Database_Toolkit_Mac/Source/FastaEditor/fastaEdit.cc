//This file reads locus and taxonomy data out of a fasta file
//Input: Fasta file downloaded from NCBI
//Output: File consisting of locus and coding sequence only
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
  cout << "Editing fasta file." << endl;
	openFile(outFile);
	getData(inFile, outFile);
	closeFile(inFile);
	closeFile(outFile);

  cout << "Done" << endl;
  return 0;
}


//Function description This function opens an input file with a user specified name
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ifstream &file -- input stream variable
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

//Function description This function opens an output file with a user specified name
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ofstream &file -- input stream variable
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

//Function description: This function reads in data from the opened file and writes data to the output file
//Funtion parameters Input:
//                  Output: 
//                  Input/Output: ifstream &in -- input stream variable, ofstream &out -- output stream variable
//Returns:
void getData(ifstream &in, ofstream &out)
{
  string temp;
  in >> temp;

  //Read until the end of file
  while(!in.eof())
  {
  	//If you find start of locus
  	if(temp[0] == '>')
  	{
      //Take out version number if it exists
      if(temp[temp.length() - 2] == '.')
      {
        temp = temp.substr(0, temp.length() - 2);
      }

      //take out pdb if it exists
      if(temp[1] == 'p' && temp[2] == 'd' && temp[3] == 'b')
      {
        temp = ">" + temp.substr(temp.find_first_of('|') + 1, temp.length() - temp.find_first_of('|'));
        temp[temp.find_first_of('|')] = '_';
      }
      //>pdb|6T21|E Chain E, N-terminal domain of EcoKMcrA restriction endonuclease (NEco) in complex with T5mCGA target sequence

      //write trimmed locus to file
      writeFile(temp, out);
      //Read rest of line to discard
      getline(in, temp);
  	}
  	//Write sequence data to outfile
  	else
  	{
  		writeFile(temp, out);
  	}

  	in >> temp;
  }
}

//Function description: This function writes data from the input file to the output file
//Funtion parameters Input: string out
//                  Output: 
//                  Input/Output: fstream &outFile 
//Returns:
void writeFile(const string &data, ofstream &out)
{
	out << data << endl;
}

//Function description This function closes an open input file
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ifstream &file - input stream variable
//Returns:
void closeFile(ifstream &file)
{
  file.close();
}

//Function description This function closes an open output file
//Funtion parameters Input:
//                  Output:
//                  Input/Output: ofstream &file - output stream variable
//Returns:
void closeFile(ofstream &file)
{
  file.close();
}
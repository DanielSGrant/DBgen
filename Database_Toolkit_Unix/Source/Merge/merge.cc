//This file reads locus and taxonomy data out of a trimmed genbank file and locus and sequence data
//out of a trimmed fasta file. Ensure you have run dbEdit and fastaEdit to get input files of the 
//proper format prior to running this program. This program takes the two input files and created a
//File consisting of taxonomy data and a coding sequence which can be used for assigning taxonomy
//to data from NGS
//Input: trimmed gendbank and fasta files
//Output: File consisting of taxonomy and coding sequence only
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
void mergeData(ifstream &, ifstream &, ofstream &);
void writeFile(const string &, ofstream &);


int main()
{
	ifstream inFile1, inFile2;
	ofstream outFile;

  //Open all 3 files
	openFile(inFile1);
  openFile(inFile2);
	openFile(outFile);
  cout << "Merging the two files" << endl;

  //Merge the data
  mergeData(inFile1, inFile2, outFile);

  //close all three files
	closeFile(inFile1);
  closeFile(inFile2);
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
void mergeData(ifstream &in1, ifstream &in2, ofstream &out)
{
  string db, fasta;

  in1 >> db;
  in2 >> fasta;
  while(!in2.eof())
  {
    in1.ignore(1, '\n');
    if(db == fasta)
    {
      getline(in1, db);
      out << ">" << db << endl;
      in2 >> fasta;
      out << fasta;

      while(fasta[0] != '>' && !in2.eof())
    {
      in2 >> fasta;
      if(fasta[0] != '>')
      {
        out << fasta;
      }
    }
      out << endl;
    }

    if(!in1.eof())
    {
      in1 >> db;  
    }
    
  }
}

//Function description: This function writes data from the input file to the output file
//Funtion parameters Input: string out
//                  Output: 
//                  Input/Output: fstream &outFile 
//Returns:
void writeFile(const string &data, ofstream &out)
{
	out << data;
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
//                  Input/Output: ifstream i - input stream variable
//Returns:
void closeFile(ofstream &file)
{
  file.close();
}
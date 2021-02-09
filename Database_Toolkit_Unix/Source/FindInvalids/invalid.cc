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
void validate(ifstream &, ofstream &, ofstream &);
void writeFile(const string &, ofstream &);


int main()
{
  ifstream inFile;
  ofstream valid, invalid;
  openFile(inFile);
  openFile(valid);
  openFile(invalid);
  validate(inFile, valid, invalid);
  closeFile(inFile);
  closeFile(valid);
  closeFile(invalid);
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

//Function description: This function checks for valid and invalid reads
//Funtion parameters Input:
//                  Output: int size -- actual array size, student array[] -- array of student type
//                  Input/Output: ifstream i -- input stream variable
//Returns:
void validate(ifstream &in, ofstream &valid, ofstream &invalid)
{
  string tax, sequence;
  int scount = 0;

  getline(in, tax);
  
  while(!in.eof())
  {
    getline(in, sequence);
    scount = 0;
    for(uint i = 0; i < tax.length(); i++)
    {
      if(tax[i] == ';')
      {
        scount++;
      }
    }
    if(scount > 8)
    {
      invalid << tax << endl << sequence << endl;
    }
    else
    {
      valid << tax << endl << sequence << endl;
    }
    getline(in, tax);
    
  }
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
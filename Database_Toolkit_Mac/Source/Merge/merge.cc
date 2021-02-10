//This file reads locus and taxonomy data out of a trimmed genbank file and locus and sequence data
//out of a trimmed fasta file. Ensure you have run dbEdit and fastaEdit to get input files of the 
//proper format prior to running this program. This program takes the two input files and creates a
//File consisting of taxonomy data and a coding sequence which can be used for assigning taxonomy
//to data from NGS
//Input: trimmed genbank and fasta files
//Output: File consisting of taxonomy and coding sequence only
//Author: Daniel Grant - d.grant@uleth.ca
//Date: Feb 6, 2021

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

const int ARRAY = 10000;

struct gene
{
  string locus;
  string tax = ""; 
  string sequence;
};

void openFile(ifstream &);
void closeFile(ifstream &);
void openFile(ofstream &);
void closeFile(ofstream &);
void readFasta(ifstream &, gene [], int &);
void readGB(ifstream &, gene [], const int &);
void writeDB(const gene [], const int &, ofstream &);
void mergeData(gene [], const int&, gene [], const int&, ofstream &, ofstream &);


int main()
{
  ifstream inFile1, inFile2;
  ofstream outFile1;
  gene array[ARRAY];
  int s = 0;

  cout << "Creating new database" << endl;
  //Open all 3 files
  openFile(inFile1);
  openFile(inFile2);
  openFile(outFile1);

  cout << "Files opened" << endl;
  readFasta(inFile1, array, s);
  cout << "Fasta read" << endl;
  readGB(inFile2, array, s);
  cout << "GB read" << endl;
  writeDB(array, s, outFile1);
  cout << "Wrote new DB" << endl;

  //close all three files
  closeFile(inFile1);
  closeFile(inFile2);
  closeFile(outFile1);
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


//Function description This function reads data from an opened file into an array
//Funtion parameters Input:
//                  Output:
//                  Input/Output: gene [], int &size
//Returns:
void readFasta(ifstream &in, gene arr[], int &size)
{
  string temp;

  in >> arr[size].locus;
  in >> temp;

  while(!in.eof())
  {
    if(temp[0] != '>')
    {
      while(temp[0] != '>' && !in.eof())
      {
        arr[size].sequence = arr[size].sequence + temp;
        in >> temp;
      }

    }
    size++;
    if(!in.eof())
    {
      arr[size].locus = temp;
    }

    in >> temp;
  }
}

//Function description This function reads data from an opened file into an array
//Funtion parameters Input:
//                  Output:
//                  Input/Output: gene [], int &size
//Returns:
void readGB(ifstream &in, gene arr[], const int &size)
{
  string locus, tax;

  in >> locus;
  in >> tax;
  while(!in.eof())
  {
    for(int i = 0; i < size; i++)
    {
      if(locus == arr[i].locus)
      {
        arr[i].tax = tax;
      }
    }
    in >> locus;
    in >> tax;
  }
}

//This function writes the taxonomy and sequence for any sequnence that was in both gb and fasta files to output
void writeDB(const gene arr[], const int &size, ofstream &out)
{
  for(int i = 0; i < size; i++)
  {
    if(arr[i].tax != "")
    {
      out << ">" << arr[i].tax << endl << arr[i].sequence << endl; 
    }
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
//                  Input/Output: ifstream i - input stream variable
//Returns:
void closeFile(ofstream &file)
{
  file.close();
}
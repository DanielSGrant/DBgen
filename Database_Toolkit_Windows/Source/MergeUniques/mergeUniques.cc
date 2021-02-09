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

const int ARRAY = 10000;

struct gene
{
  string tax;
  string sequence;
  bool unique = true;
};

void openFile(ifstream &);
void closeFile(ifstream &);
void openFile(ofstream &);
void closeFile(ofstream &);
void readArray(ifstream &, gene [], int &);
void mergeData(gene [], const int&, gene [], const int&, ofstream &, ofstream &);
void writeFile(const string &, ofstream &);




int main()
{
	ifstream inFile1, inFile2;
	ofstream merge, repeat;
  gene larger[ARRAY], smaller[ARRAY];
  int l = 0, s = 0;

  //Open all 3 files
  cout << "Open the first file" << endl;
	openFile(inFile1);
  cout << "Then open the second file" << endl;
  openFile(inFile2);
	merge.open(".././Merge_Database/Output/Uniques.fasta");
  repeat.open(".././Merge_Database/Output/Repeats.fasta");

  cout << "Merging files" << endl;
  readArray(inFile1, larger, l);
  readArray(inFile2, smaller, s);

  //Merge the data
  mergeData(larger, l, smaller, s, merge, repeat);

  //close all three files
	closeFile(inFile1);
  closeFile(inFile2);
	merge.close();
  repeat.close();
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
		cout << "Enter the filename for the input file: ";
		cin >> filename;
    filename = ".././Merge_Database/Input/" + filename;
		file.open(filename.c_str());
	}
	while (file.fail());
}


//Function description This function reads data from an opened file into an array
//Funtion parameters Input:
//                  Output:
//                  Input/Output: gene [], int &size
//Returns:
void readArray(ifstream &in, gene arr[], int &size)
{
  getline(in, arr[size].tax);
  getline(in, arr[size].sequence);
  while(!in.eof())
  {
    size++;
    getline(in, arr[size].tax);
    getline(in, arr[size].sequence);
  }
}

//Function description: This function reads in data from the opened file
//Funtion parameters Input:
//                  Output: int size -- actual array size, student array[] -- array of student type
//                  Input/Output: ifstream i -- input stream variable
//Returns:
void mergeData(gene larger[],  const int &l, gene smaller[], const int &s, ofstream &merge, ofstream &repeats)
{
  for(int i = 0; i < l; i++)
  {
    merge << larger[i].tax << endl << larger[i].sequence << endl;
    for(int j = 0; j < s; j++)
    {
      if(smaller[j].tax == larger[i].tax && smaller[j].sequence == larger[i].sequence)
      {
        smaller[j].unique = false;
      }
    }
  }
  for(int i = 0; i < s; i++)
  {
    if(smaller[i].unique)
    {
      merge << smaller[i].tax << endl << smaller[i].sequence << endl;
    }
    else
    {
      repeats << smaller[i].tax << endl << smaller[i].sequence << endl;
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
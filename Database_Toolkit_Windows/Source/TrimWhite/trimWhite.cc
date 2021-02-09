//This file trims whitespace out of a text file
//Input: textfile
//Output: textfile without whitespac
//Author: Daniel Grant - d.grant@uleth.ca
//Date: Feb 6, 2021

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void openFile(ifstream &, string &);
void closeFile(ifstream &);
void openFile(ofstream &);
void closeFile(ofstream &);
void trim(ifstream &, ofstream &);
void writeFile(const string &, ofstream &);


int main()
{
	ifstream inFile;
	string filename;
	ofstream outFile;
	openFile(inFile, filename);
	cout << "Trimming whitespace from file: " << filename << endl;
	openFile(outFile);
	trim(inFile, outFile);
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
void openFile(ifstream &file, string &filename)
{
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

//Function description: This function trims whitespace out of a file
//Funtion parameters Input:
//                  Output: 
//                  Input/Output: ifstream in -- input stream variable, ifstream &out
//Returns:
void trim(ifstream &in, ofstream &out)
{
  string temp;

  getline(in, temp);
  
  while(!in.eof())
  {
    //Check to see if the locus for the next read
  	if (temp.find_first_not_of(' ') != string::npos)
    {
      out << temp << endl;
    }
  	getline(in, temp);
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
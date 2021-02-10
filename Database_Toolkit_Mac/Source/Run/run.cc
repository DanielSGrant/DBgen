#include <cstdlib>
#include <iostream>

using namespace std;

int main ()
{
	int a, b;
	int selection, max = 3;
	//Ask user what they would like to do
	do
	{
		selection = 0;
		while(selection <= 0 || selection > max)
		{
			cout << "Please enter a number to select a task" << endl << "1: Create new database from .fasta and .gb files" << endl 
				<< "2: Merge two databases" << endl << "3: Exit" << endl;
			cin >> selection;
			cout << endl;
			if(selection <= 0 || selection > max)
			{
				cout << "Error, invalid selection. Please select a number from the provided list an hit enter" << endl;
			}
		}
		

		if(selection == 1)
		{
			a = system("./.Binaries/dbMaker");
			
		}
		else if(selection == 2)
		{
			b = system("./.Binaries/mergeUniques");
			if(!b)
			{
				system("clear");
				cout << "Merge successful" << endl << endl;
			}
			else
			{
				cout << "Unknown error has occured. Please ensure your files are in the 'Merger' directory and you have followed instructions correctly." << endl;
			}
		}
		
	}
	while(selection != max);


	if(!a)
	{
		cout << "Compilation successful" << endl;
	}


	return a;
}
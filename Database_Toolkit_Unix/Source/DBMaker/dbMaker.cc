#include <cstdlib>
#include <iostream>

using namespace std;

int main ()
{
	int a,b,c,d,e,f;
	char rmvar;
	a = system("./.Binaries/trimWhite <./.IOParameters/trimWhitef.txt");
	cout << endl;
	b = system("./.Binaries/trimWhite <./.IOParameters/trimWhiteg.txt");
	cout << endl;
	c = system("./.Binaries/gbEdit <./.IOParameters/gbEdit.txt");
	cout << endl;
	d = system("./.Binaries/fastaEdit <./.IOParameters/fastaEdit.txt");
	cout << endl;
	e = system("./.Binaries/merge <./.IOParameters/mergeDB.txt");
	cout << endl;
	f = system("./.Binaries/invalid <./.IOParameters/invalid.txt");

	system("clear");
	

	if(!a && !b && !c && !d && !e && !f)
	{
		cout << "Database creation successful" << endl;
		cout << endl << "Would you like to remove intermediate files? (y/n): ";
		cin >> rmvar;
		if(rmvar == 'y' || rmvar == 'Y')
		{
			system("rm -f ./Make_Database/Output/sequencenw.fasta ./Make_Database/Output/sequencenw.gb ./Make_Database/Output/trimmed.fasta ./Make_Database/Output/trimmed.gb");

		}

		cout << "Finished" << endl << endl;
	}
	else
	{
		cout << "Unknown error has occured. Please ensure your files are in the 'Make_Database' directory and you have followed instructions correctly." << endl << endl;
	}


	return 0;
}
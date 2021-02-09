#include <cstdlib>
#include <iostream>

using namespace std;

int main ()
{
	int a,b,c,d,e,f;
	char rmvar;
	a = system("cd ../.Binaries/ && trimWhite <../.IOParameters/trimWhitef.txt && cd ..");
	cout << endl;
	b = system("cd ../.Binaries/ && trimWhite <../.IOParameters/trimWhiteg.txt && cd ..");
	cout << endl;
	c = system("cd ../.Binaries/ && gbEdit <../.IOParameters/gbEdit.txt && cd ..");
	cout << endl;
	d = system("cd ../.Binaries/ && fastaEdit <../.IOParameters/fastaEdit.txt && cd ..");
	cout << endl;
	e = system("cd ../.Binaries/ && merge <../.IOParameters/mergeDB.txt && cd ..");
	cout << endl;
	f = system("cd ../.Binaries/ && invalid <../.IOParameters/invalid.txt && cd ..");

	system("cls");
	

	if(!a && !b && !c && !d && !e && !f)
	{
		cout << "Database creation successful" << endl;
		cout << endl << "Would you like to remove intermediate files? (y/n): ";
		cin >> rmvar;
		if(rmvar == 'y' || rmvar == 'Y')
		{
			system("cd ../Make_Database/Output/ && del -f sequencenw.fasta sequencenw.gb trimmed.fasta trimmed.gb");

		}

		cout << "Finished" << endl << endl;
	}
	else
	{
		cout << "Unknown error has occured. Please ensure your files are in the 'Make_Database' directory and you have followed instructions correctly." << endl << endl;
	}


	return 0;
}
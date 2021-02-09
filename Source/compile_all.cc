#include <cstdlib>
#include <iostream>

using namespace std;

int main ()
{
	int a,b,c,d,e,f, g;
	char rmvar;
	a = system("./Executables/trimWhite <./IOdata/trimWhitef.txt");
	b = system("./Executables/trimWhite <./IOdata/trimWhiteg.txt");
	c = system("./Executables/gbEdit <./IOdata/gbEdit.txt");
	d = system("./Executables/fastaEdit <./IOdata/fastaEdit.txt");
	e = system("./Executables/mergeDB <./IOdata/mergeDB.txt");
	f = system("./Executables/invalid <./IOdata/invalid.txt");

	system("clear");
	cout << "Would you like to remove intermediate files? (y/n): ";
	cin >> rmvar;
	if(rmvar == 'y' || rmvar == 'Y')
	{
		g = system("rm -f ./Files/sequencenw.fasta ./Files/sequencenw.gb ./Files/trimmed.fasta ./Files/trimmed.gb");
	}
	else
	{
		g = 0;
	}
	system("clear");

	if(!a && !b && !c && !d && !e && !f && !g)
	{
		cout << "Database creation successful" << endl;
	}


	return 0;
}
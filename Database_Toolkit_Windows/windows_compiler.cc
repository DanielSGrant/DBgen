#include <cstdlib>
#include <iostream>

using namespace std;

int main ()
{
	// int a,b,c,d,e,f, g;
	// char rmvar;
	int a, b, c, d, e, f, g;
	
	//Compile all binaries
	a = system("cd ./.Source/DBMaker && mingw32-make");
	b = system("cd ./.Source/FastaEditor && mingw32-make");
	c = system("cd ./.Source/FindInvalids && mingw32-make");
	d = system("cd ./.Source/GBEditor && mingw32-make");
	e = system("cd ./.Source/Merge && mingw32-make");
	f = system("cd ./.Source/MergeUniques && mingw32-make");
	g = system("cd ./.Source/TrimWhite && mingw32-make");
	g = system("cd ./.Source/Run && mingw32-make");

	//Display success for compilation
	if(!a && !b && !c && !d && !e && !f && !g)
	{
		system("cls");
		cout << "Compilation successful" << endl;
		return 0;
	}
	else
	{
		cout << "Unknown error has occured. Please ensure you have g++ installed on your system" << endl;
		return -1;
	}

	return 0;
}
#include <cstdlib>
#include <iostream>

using namespace std;

int main ()
{
	// int a,b,c,d,e,f, g;
	// char rmvar;
	int a, b, c, d, e, f, g, h;
	
	//Compile all binaries
	a = system("cd ./Source/DBMaker && make");
	b = system("cd ./Source/FastaEditor && make");
	c = system("cd ./Source/FindInvalids && make");
	d = system("cd ./Source/GBEditor && make");
	e = system("cd ./Source/Merge && make");
	f = system("cd ./Source/MergeUniques && make");
	g = system("cd ./Source/TrimWhite && make");
	h = system("cd ./Source/Run && make");

	//Display success for compilation
	if(!a && !b && !c && !d && !e && !f && !g && !h)
	{
		system("clear");
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
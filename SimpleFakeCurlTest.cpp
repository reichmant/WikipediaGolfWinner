//@author Thomas Reichman
//@version 2015.10.29
#include <string>
#include <iostream>
#include "SimpleFakeCurl.h"

using namespace std;

int main(int argc, char *argv[])
{
	SimpleFakeCurl httpGrabber(argv[1]);
	string doc = httpGrabber.getRetrievedDocument();
	cout << doc << endl;

	if (httpGrabber.getURL("http://www.cs.xu.edu/~lewandow") !=-1)
        	cout << httpGrabber.getRetrievedDocument() << endl;
	else
		cout << "Could not retrieve document" << endl;
}

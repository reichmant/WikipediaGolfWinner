/**
All code here adapted (modified as little as possible) from
www.luckyspin.org
Adaptation by Gary Lewandowski, 14 October 2007.

@author Thomas Reichman
@version 2015.10.29

	This class simply sets up main() and the method used to help
	convert the input strings to the ints we need.
	(See the methods for more in-depth comments)
Original header comments follow.
**/

/*
 * This is a very simple example of how to use libcurl from within
 * a C++  program. The basic idea is that you want to retrieve the
 * contents of a web page as a string. Obviously, you can replace
 * the buffer object with anything you want and adjust elsewhere
 * accordingly.
 *
 * Hope you find it useful..
 *
 * Todd Papaioannou
 */

#include <string>
#include <iostream>
#include <cctype>//?
#include <algorithm>
#include <vector>
//#include <atoi>
#include <sstream>
#include "SimpleCurl.h"
//#include "GrabUrls.h"
#include "URLGraph.h"
using namespace std;

//Credit to http://ubuntuforums.org/showthread.php?t=396479
//And Neal for finding it for me first.
int string2Int(string s) //used to convert char in argument variables to int for the level variable.
{
	stringstream ss(s);

	int i;

	ss >> i;
	return i;
}


int main(int argc, char *argv[])//takes in the three arguments required for BreadthFirstSearch to work.
{
	/** OLD DEFINITION: one way to use SimpleCurl: via a constuctor. Give a string and it
	  tries to retrieve the document.
	  **/
	//SimpleCurl httpGrabber(argv[1] != -1);
	SimpleCurl httpGrabber(argv[1]);
	string startingURL = argv[1];
	URLGraph g;
	int level = string2Int(argv[2]);
	string target = argv[3];
	g.BreadthFirstSearch(level, startingURL, target);




	  /*==================================
				PREVENT CRASHING
	  credit to https://stackoverflow.com/questions/22130158/terminate-called-after-throwing-an-instance-of-stdout-of-range-what-basic
	  ==================================*/
	      try
    {
        // do stuff
    }
    catch (std::exception const &exc)
    {
        std::cerr << "Exception caught " << exc.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught\n";
    }
	//SimpleCurl httpGrabber;
	////////////string doc = httpGrabber.getRetrievedDocument();
	//cout << doc << endl;

	/*vector<string> give_X_URLs = find_urls(doc);
	for (int i = 0; i < give_X_URLs.size(); i++) //iterates vector and prints URLs
	{
		cout << give_X_URLs[i] << endl;
	}*/

	/** Here is a second way -- the more likely way you'll use it.
	        After creating an httpGrabber, invoke the getURL method.
	        It returns -1 on failure.
	        **/

	/*
	if (httpGrabber.getURL("http://www.google.com") !=-1) //argv[1] instead of actual URL
	    	cout << httpGrabber.getRetrievedDocument() << endl;
	else
		cout << "Could not retrieve document. THIS LINK WAS BAD" << endl;

	*/
}
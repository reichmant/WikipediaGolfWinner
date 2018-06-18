/**
	Fake getting document at a URL.
	Given a URL, the code in this class simply strips off the
	protocol (e.g. "http://") and then treats the name as a file.

	@author Thomas Reichman
	@version 2015.10.29
**/


#include <string>
#include <iostream>
#include <fstream>
#include "SimpleFakeCurl.h"

using namespace std;

   SimpleFakeCurl::SimpleFakeCurl(string url)
   {
	if (getURL(url) == -1) exit(-1);
   }

   int SimpleFakeCurl::getURL(string url)
    {
	buffer = "";
	error="";
        int index = url.find_first_of("://");
	if (index == string::npos)
	{
		error = "url not in proper form.";
		return -1;
	}
 	 
	string filename = url.substr(index+3);

	if (filename[filename.length()-1] == '/')
	  filename += "index.html";
	ifstream theFile;
	theFile.open(filename.c_str());
	if (!theFile)
	{
		theFile.open((filename+"/index.html").c_str());
		if (!theFile) 
		{
			error="url did not refer to a file we can open.";
			return -1;
		}
	}

	char ch;
	while (theFile.get(ch))
		buffer += ch;
	theFile.close();
        return buffer.length();
       
     }

  string SimpleFakeCurl::getRetrievedDocument()
  { 
	return buffer;
  }


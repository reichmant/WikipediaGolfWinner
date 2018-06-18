/**
All code here adapted (modified as little as possible) from 
www.luckyspin.org
Adaptation by Gary Lewandowski, 14 October 2007.

@author Thomas Reichman
@version 2015.10.29

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
#ifndef SIMPLECURL_H
#define SIMPLECURL_H

#include <string>
#include <iostream>
#include <curl/curl.h>
#include <vector>//needed?
#include <cctype>

using namespace std;

class SimpleCurl
{
private:
// Write any errors in here
	char errorBuffer[CURL_ERROR_SIZE];

// Write all expected data in here
	string buffer;

// This is the writer call back function used by curl
	static int writer(char *data, size_t size, size_t nmemb,
				std::string *buffer);
private:
	CURL *curl;
	CURLcode result;
	

public:
	SimpleCurl() { }
	SimpleCurl(string url);

	/**
	Given the string of a url, retrieves the document if possible.
	returns -1 on error, the size of the document if the document was
	retrieved.
	**/
	int getURL(string url);
	string getRetrievedDocument();
	//int iter;
	//vector<string> find_urls(const string& s);
	//string::const_iterator url_end(string::const_iterator b, string::const_iterator e);
	//string::const_iterator url_beg(string::const_iterator b, string::const_iterator e);
};

#endif

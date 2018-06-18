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

#include <string>
#include <iostream>
#include <curl/curl.h>
#include "SimpleCurl.h"

using namespace std;

int SimpleCurl::writer(char *data, size_t size, size_t nmemb,
                       std::string *buffer)
{
	// What we will return
	int result = 0;
	//TESTING:cout << "Result set to " << result << "!" << endl;
	//TESTING:cout << "(Should be 0...)" << endl;

	// Is there anything in the buffer?
	if (buffer != NULL)
	{
		// Append the data to the buffer
		buffer->append(data, size * nmemb);
		//TESTING:cout << "Data appended to the buffer!" << endl;

		// How much did we write?
		result = size * nmemb;
		//TESTING:cout << result << " was written!" << endl;
	}

	return result;
}

SimpleCurl::SimpleCurl(string url)
{
	if (getURL(url) == -1) exit(-1);
}

int SimpleCurl::getURL(string url)
{
	buffer = "";
	//TESTING:cout << "Buffer set to empty string!" << endl;
	// Create our curl handle
	curl = curl_easy_init();

	if (curl)
	{
		// Now set up all of the curl options
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		//SSL AND HHTPS SUPPORT?
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "/MinGW/MSYS/1.0/local/bin/curl-ca-bundle.crt");
		//TESTING:cout << "curl options all set up!" << endl;

		// Attempt to retrieve the remote page
		result = curl_easy_perform(curl);
		//TESTING:cout << "Retrieving remote page!" << endl;
		// Always cleanup
		curl_easy_cleanup(curl);
		//TESTING:cout << "Cleaning up!" << endl;
		// Did we succeed?
		if (result != CURLE_OK)
		{
			cout << "Error: [" << result << "] - " << errorBuffer << endl;
			return -1;
		}
		return buffer.length();
	}
	return 0;
}

string SimpleCurl::getRetrievedDocument()
{
	//cout << "Returning buffer (" << buffer << ")!" << endl; //DON'T ACUALLY
	//OUTPUT THE BUFFER VARIABLE, IT SCREWS EVERYTHING UP
	//TESTING:cout << "Returning buffer!" << endl;
	return buffer;
}


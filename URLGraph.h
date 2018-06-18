	/**
**	* @author Thomas Reichman
**	* @version 2015.11.1
**	* 
**	* This is a sample text for 
**	* a C++  program. The basic idea is that things happen because. 
**	* Obviously, you can do things like replace this.
**	* You should add a couple more lines.
**	* Or 2.
	**/

#ifndef URLGRAPH_H
#define URLGRAPH_H

#include <string>
#include <iostream>
#include <curl/curl.h>
#include <vector>//needed?
#include <cctype>
#include <map>

using namespace std;

class URLGraph
{
private:
// 
	;

// 
	;

// This is the writer call back function used by curl
	
private:
	CURL *curl;//?
	CURLcode result;//?

	map <string, vector<string> > adjacencyList;
public:
	//string s;
	URLGraph();
	void BreadthFirstSearch(int level, string startingURL, string target);
	//int String2Int(string s);


};

#endif

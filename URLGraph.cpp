/**
**	* @author Thomas Reichman
**	* @version 2015.11.1
**	*
**	* This class contains the basic set up for the Graph used to hold URLs
**	* and the information associated with them, which is used for
**	* setting up the BreadthFirstSearch method.
**	* 
**	* This method searches through a website's linked pages to a certain level
**	* and stops once it has nothing left to search, or has found a specified target.
**/

#include <string>
#include <iostream>
#include <cctype>//?
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include "URLGraph.h"
#include "GrabUrls.h"
#include "SimpleCurl.h"
//#include "SimpleFakeCurl.h"//??????????

using namespace std;


//class URLGraph;

URLGraph::URLGraph()
{


	//::iterator i;
	//for (vector<string>::iterator i = vertexGraph.begin(); iterator <= vertexGraph.end(); i++)
	//	{
	//		vertexGraph.push_back(i);
	//	}
}

//void URLGraph::add(string v, vector<string> neighbors)
//{
//graph[v] = neighbors;
//}
void URLGraph::BreadthFirstSearch(int level, string startingURL, string target)
{

	//?vector<string> vertexGraph; //initialize the vector where we hold the neighbors (URLs).
	//?vertexGraph.push_back("");//Use empty string to clear out the initial vector.
	map <string, vector<string> > Graph;//eventually not needed since we pop the neighbors out of the queue
	/*=============================================================*\
	|Initialize the instance variables, AKA set up the three things	|
	|we want to hold info about each URL in the tree.				|
	\*=============================================================*/

	//Now, create the appropriate maps that hold each peice of information.

	/*==================================================*\
	|A node's color can be white, gray, or black. White  |
	|means a node has NOT been visited by BFS, gray means|
	|its in the process, and black means that it has been|
	|visited.											 |	
	|										   			 |
	|The parent stores which URL linked to this 	     |
	|particular node.							     	 |
	|										   			 |
	|The number of nodes away from the "root" of our     |
	|binary tree.								   		 |
	\*==================================================*/
	map <string, string> color;
	map <string, string> parent;//
	map <string, int> distance;//
	//vector <string> URLQueue;//The queue that stores the URLs we are going to be looking at.
	//URLQueue.push_back(s) // push_back is easier to spell than enqueue!

	/*===========================================
	~~~~~~~~~~~~~~~~~~~~TESTING~~~~~~~~~~~~~~~~~~
	It's silly to initialize the three of these
	because we don't know how many elements
	(THIS IS FOR TESTING C LEVEL)
	===========================================*/
	/*___________________________________________
	|for (string s)						|
	|there should be in each map to initialize.	|
	|C[color] = "white"; // unseen			|
	|P[parent] = NULL;						|
	|D[distance] = NULL;					|
	|D[distance] = 0;						|
	|____________________________________________|*/

	queue<string> Q;
	Q.push(startingURL);
	//TESTING:cout << s << endl;
	//map<string, string> color;
	/*=================================
	Set up properties of the first node
	=================================*/
	color[startingURL] = "gray";
	distance[startingURL] = 0;
	parent[startingURL] = "";

	SimpleCurl httpGrabber;
	string node;//node referred to as u by mathematicians. (More like graphmaticians, am I right?)
	//string vertice;//vertice referred to as v by mathematicians. //UNUSED?
	size_t pos;//Admittedly, I have trouble understanding the find method. By I'm pretty sure this has to be called pos.
	//string search; //not needed, since we are using target.
	bool found = false;
	int count = 0;
	int numLevels = 0;//track how many levels deep we searched.
	while (!Q.empty() && found == false && count <= level)
	{
		//cout << Q.size();
		node = Q.front();
		//TESTING:cout << u << endl;
		Q.pop();
		//cout << node << endl;
		if (node.substr(0, 1) == "/")
		{
			node = "en.wikipedia.org" + node; //Something Neal put in to help me find internal links.
		}
		if (httpGrabber.getURL(node) != -1)
		{
			string doc = httpGrabber.getRetrievedDocument();
			vector<string> neighbors = find_urls(doc);
			Graph[node] = neighbors; // add to graph

			//cout << doc << endl << endl;
			//cout << neighbors.end()-neighbors.begin() << endl;
			//for (std::vector<string>::iterator it = neighbors.begin(); it < neighbors.end(); it++){
			//	cout << *it << endl;
			//}



			//cout << "YOU ARE HERE" << endl;
			pos = doc.find(target);
			string currentURL = node;
			if (pos != std::string::npos)
			{
				found = true;
				cout << "FOUND AT URL: " << currentURL << endl;

				//int numLevels = 0;
				//Print the path of the URLs taken.
				while ( parent[currentURL] != "")//For every URL aside from the top-most one...
				{
					cout << "Here is the path of URLs, from page \"" << target << "\" was found at backwards to the beginning" << endl;
					//cout << count << endl;
					cout << parent[currentURL] << endl;//Print out the parent of the URL we're looking at.
					currentURL = parent[currentURL];//Set the currentURL to its parent so that the loop continues until it reaches the top.
					
				}
				if (numLevels > 0)
				{
					cout << "It took " << numLevels << " page(s) to find the word \"" << target << "\"." << endl;
					//break;
				}
			}
			//cout << "MADE ITTTTTT" << endl;
			//if (pos == std::string::npos)//AKA else
			if (found == false)
			{
				cout << "The keyword \"" << target << "\" was not found on " << currentURL << endl;
				cout << "We searched " << numLevels << " page(s) so far but couldn't find the word \"" << target << "\" anywhere." << endl;
			}


			//cout << neighbors.size() << endl;
			for (int i = 0; i < neighbors.size(); i++) //Goes through each neighbor and loops until it does all of them.
			{
				//count = distance[neighbors[i]]; //don't do this here!!!! Do it inside the if - see below.
				if (color.find(neighbors[i]) == color.end())// add neighbors to queue, set distance, etc. Set 
				{
					color[neighbors[i]] = "white";
					parent[neighbors[i]] = node;
					distance[neighbors[i]] = distance[node] + 1; //the first is the vertice, second is node?
					count = distance[neighbors[i]];//count how far down we are by using distance, as it measures the
					//how depth is, which is what must be <= level in the while loop anyways.
					if (!(neighbors[i].substr(0, 1) == "#"))//checks for malformed URLs
					{
						Q.push(neighbors[i]);
					}

					//
					numLevels++;//track how many levels deep we searched.
					//cout << neighbors[i] << endl;

				}
			}
		}
		color[startingURL] = "black";
	}
}
/*u = URLQueue.dequeue(); // pop
for ()//each vertex v in G.getNeighbors(u)
{
if (color[s] == "white")
{
color[s] = "gray";
parent[s] = u;
distance[s] = distance[s] + 1; //the first is v, second is u. Which array
Q.enqueue(v);
color[s] = "black";
}*/
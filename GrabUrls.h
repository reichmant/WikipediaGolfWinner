/**
**	* @author Thomas Reichman
**	* @version 2015.11.1
**	*
**	* This holds some methods we use to manipulate the retrieved 
**	* HTML document into separated URLs that can be put into other
**	* structures so that we can perform BreadthFirstSearch on them.
**	* 
**	* Credit to Accelerated C++ book provided on Canvas for these methods.
**	* Credit to Neal for the find_urls method I ended up using, his version
**	* helps with filtering out internal Wikipedia links.
**	* However, this may affect performance on websites that do not start within Wikipedia.
**/
#include "SimpleCurl.h"
#ifndef GRABURLS_H
#define GRABURLS_H

bool not_url_char(char c)
{
	// characters, in addition to alpha-numerics, that can
	// appear in a URL
	static string const url_ch = "~;/?:@=&$-_.+!*'(),";

	// see whether c can appear in a URL and return the negative
	return !(isalnum(c) ||
	         find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
	return find_if(b, e, not_url_char);
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
	static string const sep = "<a href=\"";//THIS WAS CHANGED TO DO ONLY INTERNAL WIKI LINKS, NOT TO PICS OR ANYTHING.

	typedef string::const_iterator iter;
	iter i = b;   // i marks where the separator was found //INT TYPE??
	while ((i = search(i, e, sep.begin(), sep.end())) != e) {

		if (i != b && i + sep.size() != e) {
			// make sure the separator isn't at the beginning
			//or end of the line
			iter beg = i; // beg marks the beginning of the protocol-name
			while (beg != b && isalpha(beg[-1]))
				--beg;

			if (beg != i && !not_url_char(i[sep.size()]))
				// is there at least one appropriate character
				// before and after the separator?
				return beg;
		}
		// the separator we found wasn't part of a URL advance i past this separator
		i += sep.size();
	}
	return e;
}



vector<string> find_urls(string HTML)//NEAL GAVE THIS METHOD TO FIX AN ERROR IN BFS.
{


	vector<string> list;
	while (HTML.find("href") != -1)
	{
		int start = HTML.find("href=\"/") + 6;
		int end = HTML.substr(start).find ("\">");
		list.push_back(HTML.substr(start, end));
		HTML = HTML.substr(end);
	}
	return list;

// WE REMOVED THIS IN PLACE OF SOME CODE NEAL WANTED ME TO TRY.
/*vector<string> find_urls(const string& s)
{
vector<string> ret;
typedef string::const_iterator iter;
iter b = s.begin(), e = s.end();

//look through the entire input
while (b != e) {

	//look for one or more letters followed by ://
	b = url_beg(b, e);

	// if we found it
	if (b != e) {
		// get the rest of the URL
		iter after = url_end(b, e);

		//remember the URL
		ret.push_back(string(b, after));

		//advance b and check for more URLs on this line
		b = after;
	}
}
return ret;*/
};

#endif

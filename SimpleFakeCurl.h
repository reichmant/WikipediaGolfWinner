//@author Thomas Reichman
//@version 2015.10.29
#include <string>
#include <iostream>

using namespace std;

class SimpleFakeCurl
{
private:
// Write any errors in here
   string error;

// Write all expected data in here
   string buffer;

public:
   SimpleFakeCurl() { }
   SimpleFakeCurl(string url);

   /**
     Given the string of a url, retrieves the document if possible.
     returns -1 on error, the size of the document if the document was
     retrieved.
   **/
   int getURL(string url);

    string getRetrievedDocument();
};


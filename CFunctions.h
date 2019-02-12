/**
* CFunctions.h
* Class containing various functions that might come in handy.
*/

#include <iostream>
#include <string>
#include <algorithm>

class CFunctions
{
public:

    /**
    * iequals: compare two string and ignore case.
    * @parameter string (string a)
    * @parameter string (string b)
    * @return bool (true if strings are equal, false if not)
    */
    bool iequals(std::string a, std::string b);

};


/**
* iequals: compare two string and ignore case.
* @parameter string (string a)
* @parameter string (string b)
* @return bool (true if strings are equal, false if not)
*/
bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

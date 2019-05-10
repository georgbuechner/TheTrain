#include "CFunctions.h"

/**
* iequals: compare two string and ignore case.
* @parameter string (string a)
* @parameter string (string b)
* @return bool (true if strings are equal, false if not)
*/
bool CFunctions::iequals(const char* chA, const char*  chB)
{
    unsigned int len = strlen(chB);
    if (strlen(chA) != len)
        return false;
    for (unsigned int i = 0; i < len; ++i)
        if (tolower(chA[i]) != tolower(chB[i]))
            return false;
    return true;
}

/*
* in: checks whether a string is in a vector of strings
* @parameter string
* @parameter vector<string> 
* @return bool
*/
bool CFunctions::in(std::string str, std::vector<std::string> vec)
{
    for(unsigned int i=0; i<vec.size(); i++)
    {
        if(iequals(str.c_str(), vec[i].c_str()) == true)
            return true;
    }

    return false;
}

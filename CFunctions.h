/**
* CFunctions.h
* Class containing various functions that might come in handy.
*/

#ifndef CFUNCTIONS_H
#define CFUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

class CFunctions
{
public:

    /**
    * iequals: compare two string and ignore case.
    * @param[in] string a
    * @param[in] string b
    * @return true if strings are equal, false if not
    */
    bool iequals(const char* a, const char* b);

    /*
    * in: checks whether a string is in a vector of strings
    * @parameter string
    * @parameter vector<string> 
    * @return bool
    */
    bool in(std::string str, std::vector<std::string>);

};





#endif

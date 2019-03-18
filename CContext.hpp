/**
* CContext.h
* A context can be the basic game context, but also quests or dialog have a context. 
*/

#ifndef CCONTEXT_h
#define CCONTEXT_h

#include <iostream>
#include <string>
#include "CEventmanager.hpp"

class CContext
{
private:

    //Atributes
    std::string m_sID;
    CEventmanager m_EM;

public:

    /**
    * Constructor
    */
    CContext();
};    
    

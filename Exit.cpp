#include "CExit.hpp"

/**
* Constructor
* @parameter string (name of the door)
* @parameter string (custom id)
* @parameter string (identifier for linked room)
* @parameter vector<string> (Array with accepted words)
* @parameter string (head-description)
* @parameter string (foot-description)
* @parameter string (alternative-description)
* @parameter string (function)
*/
CExit::CExit(std::string sName, std::string sID,  std::string sLinkedRoom, std::vector<std::string> vTake, std::string headDescription, std::string footDescription, std::string altDescription, std::string sFunction)
{
    //Assign attributes
    m_sName = sName;
    m_sID = sID;
    m_sLinkedRoom = sLinkedRoom;
    m_vTake = vTake;
    m_headDescription = headDescription;
    m_foorDescription = footDescription;
    m_altDescription = altDescription; 
    m_sFunction = sFunction;
}


// *** Functions *** //


//Initialize map of all exit-functions
std::map<std::string, void(CExit::*)()>CExit::m_mapExitFuncs = {};

/**
* initializeFunctions: adds all functions to map of exit-functions.
*/
void CExit::initializeFunctions() 
{
    m_mapExitFuncs["standard"] = &CExit::func_standard;
}

/**
* callExiteFunction: call function of given exit 
*/
void CExit::callExitFunction() {
    (this->*m_mapExitFuncs.at(m_sFunction))();
}

void CExit::func_standard() {}


#include "CQuest.hpp"


/**
* Constructor
* @parameter string (Quest's name)
* parameter string (Quest's description)
*/
CQuest::CQuest(std::string sID, std::string sName, std::string sDescription)
{
    m_sID = sID;
    m_sName = sName;
    m_sDescription = sDescription;
    m_bAchieved = false;
}


/**
* addStep: add a step to quest.
* parameter string (id of step)
* @return CQuestStep* (Pointer to quest step)
*/
void CQuest::addStep(CQuestStep* questStep)
{
    m_listSteps.push_back(questStep);
}

/**
* printQuest: print all achieved and all active quest steps
*/
void CQuest::printQuest()
{
    std::cout << m_sName << "\n";
    std::cout << m_sDescription << "\n";

    for(auto it=m_listSteps.begin(); it!=m_listSteps.end(); it++)
    {
        std::cout << "-- " << (*it)->getName() << "\n";
        std::cout << (*it)->getDescription() << "\n\n";
    }
    
    std::cout << "\n\n";
}

#include "CQuest.hpp"


/**
* Constructor
* @parameter string (Quest's name)
* parameter string (Quest's description)
*/
CQuest::CQuest(std::string sID, std::string sName, std::string sDesc, std::list<CQuestStep*> steps)
{
    //Assign attributes
    m_sID = sID;
    m_sName = sName;
    m_sDescription = sDesc;
    m_bAchieved = false;
    m_listSteps = steps;
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
    //Print name and description of quest
    std::cout << "\n";
    std::cout << m_sName << "\n";
    std::cout << m_sDescription << "\n";

    //Iterate over alls steps and print name and description
    for(auto it=m_listSteps.begin(); it!=m_listSteps.end(); it++)
    {
        if((*it)->getActive() == false)
            break;
        else if((*it)->getAchieved() == false)
            std::cout << "-- (aktive): ";
        else 
            std::cout << "-- (gelöst): ";
        
        std::cout << (*it)->getName() << "\n";
        std::cout << (*it)->getDescription() << "\n";
    }
    
    std::cout << "\n";
}

#include "CQuest.hpp"


/**
* Constructor
* @parameter string (Quest's name)
* parameter string (Quest's description)
*/
CQuest::CQuest(std::string sID, std::string sName, std::string sDesc, std::map<std::string, CQuestStep*> steps)
{
    //Assign attributes
    m_sID = sID;
    m_sName = sName;
    m_sDescription = sDesc;
    m_bAchieved = false;
    m_mapSteps = steps;
}


/**
* addStep: add a step to quest.
* parameter string (id of step)
* @return CQuestStep* (Pointer to quest step)
*/
void CQuest::addStep(CQuestStep* questStep)
{
    m_mapSteps.insert(std::pair<std::string, CQuestStep*>(questStep->getID(), questStep));
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
    for(auto it=m_mapSteps.begin(); it!=m_mapSteps.end(); it++)
    {
        if(it->second->getActive() == false)
            continue;
        else if(it->second->getAchieved() == false)
            std::cout << "-- (aktive): ";
        else 
            std::cout << "-- (gelöst): ";
        
        std::cout << it->second->getName() << "\n";
        std::cout << it->second->getDescription() << "\n";
    }
    
    std::cout << "\n";
}

/**
* CQuest.hpp
* Every quest object has a map of queststeps. And an eventmanager. 
*/

#ifndef CQUEST_H
#define CQUEST_H

#include <iostream>
#include <string>
#include <map>
#include "CQuestStep.hpp"

//Forward declarations
class CQuestStep;

class CQuest
{
private:
    
    //Attributes
    std::string m_sID;          //Custom id of quest
    std::string m_sName;        //Name of the quest
    std::string m_sDescription; //Quest's description
    bool        m_bAchieved;    //Boolean indicating whether quest is achieved

    std::map<std::string, CQuestStep*> m_mapSteps;     //List of all queststeps

public:
    /**
    * Constructor
    * @parameter string (Quest's custom id)
    * @parameter string (Quest's name)
    * @parameter string (Quest's description)
    */
    CQuest(std::string sID, std::string sName, std::string sDescription, std::map<std::string, CQuestStep*> steps);


    // ** getter ** //
    
    /**
    * getID: get quest's custom id.
    * @return string (quest's custom id)
    */
    std::string getID() {
        return m_sID;
    }

    /**
    * getName: get quest's name.
    * @return string (quest's name)
    */
    std::string getName() {
        return m_sName;
    }

    /**
    * getAchieved: get info whether quest is achieved.
    * @return bool 
    */
    bool getAchieved() {
        return m_bAchieved;
    }

    /**
    * getSteps: get map with all quest steps.
    * @return list<CQuestStep*> (List with all queststeps)
    */
    std::map<std::string, CQuestStep*> getSteps() {
        return m_mapSteps;
    }

    

    /**
    * addStep: add a step to quest.
    * @parameter string (id of step)
    * @return CQuestStep* (Pointer to quest step)
    */
    void addStep(CQuestStep* questStep);

    /**
    * printQuest: print all achieved and all active quest steps
    */
    void printQuest();
};
    

#endif

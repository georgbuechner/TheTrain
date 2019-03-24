/**
* CQuestStep.hpp
* Step contains a name, a description of what to do and an int indication:
* 0: Quest not active yet.
* 1: Quest active not achieved
* 2: Quest achieved
*/

#ifndef CQUESTSTEP_H
#define CQUESTSTEP_H

#include <iostream>
#include <string>
#include <map>
#include "CEvent.hpp"

class CQuestStep
{
private: 

    //Attributes
    std::string m_sID;              //Queststep's id
    std::string m_sName;            //Queststep's name
    std::string m_sDescription;     //Queststep's description
    bool m_achieved;                //Indicating whether step is already solved or not
    bool m_active;                  //Indicating whether step is already active or not
    
    void(CQuestStep::*m_func)(CEvent* event);    //Function pointer to queststep-function 

    static std::map<std::string, void(CQuestStep::*)(CEvent*)> mapQuestfuncs; 

public:
    
    /**
    * Constructor
    * @parameter string (step's name)
    * @parameter string (step's description)
    * @parameter int (achieved)
    */
    CQuestStep(std::string id, std::string sName, std::string sDescription, bool achieved, 
                                                  bool active, std::string sFuncID);

    static void initializeFunctions();

    // ** getter ** //

    /**
    * getID: get step's id .
    * @return string (step's id)
    */
    std::string getID() {
        return m_sID;
    }
    /**
    * getName: get step's name.
    * @return string (step's name)
    */
    std::string getName() {
        return m_sName;
    }

    /**
    * getDescription: get stept's description.
    * @return string (step's description)
    */
    std::string getDescription() {
        return m_sDescription;
    }

    /**
    * getAchieved: get info whether step is solved or not
    * @return bool
    */
    bool getAchieved() {
        return m_achieved;
    }
    
    /**
    * getActive: get info whether step is active or not
    * @return bool 
    */
    bool getActive() {
        return m_active;
    }

    
    // ** setter ** // 

    /**
    * setAchieved: change status of quest: achieved/ not-achieved
    * @parameter bool (achieved)
    */
    void setAchieved(bool achieved) {
        m_achieved = achieved;
    }
    
    /**
    * setActive: change status of quest: active/ not-active
    * @parameter bool (active)
    */
    void setActive(bool active) {
        m_active= active;
    }


    /** 
    * callQuestFunction: call function of this quest step 
    * @parameter string (Idetifier telling more about the event)
    */
    void callQuestFunction(CEvent* event) {
        (this->*m_func)(event);
    }



    /** functions **/
    void standard(CEvent* event);
 
    //Quest: talk to jay
    void talk_to_jay_Find(CEvent* event);
    void talk_to_jay_Talk(CEvent* event);
    void talk_to_jay_Parsen(CEvent* event);
    void talk_to_jay_givePresent(CEvent* event);
    void talk_to_jay_dontPresent(CEvent* event);

};


#endif

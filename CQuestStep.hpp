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

class CQuestStep
{
private: 

    //Attributes
    std::string m_sName;            //Queststep's name
    std::string m_sDescription;     //Queststep's description
    bool m_achieved;                //Indicating whether step is already solved or not
    bool m_active;                  //Indicating whether step is already active or not

public:
    
    /**
    * Constructor
    * @parameter string (step's name)
    * @parameter string (step's description)
    * @parameter int (achieved)
    */
    CQuestStep(std::string sName, std::string sDescription, bool achieved, bool active) {

        //Assign attributes
        m_sName = sName;
        m_sDescription = sDescription;
        m_achieved = achieved;
        m_active = active;
    }


    // ** getter ** //
    
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

};


#endif

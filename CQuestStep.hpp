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
    int m_achieved;                 //0: Step not active yet, 1: Step not achieved, 2: Step achieved

public:
    
    /**
    * Constructor
    * @parameter string (step's name)
    * @parameter string (step's description)
    * @parameter int (achieved)
    */
    CQuestStep(std::string sName, std::string sDescription, int achieved) {

        //Assign attributes
        m_sName = sName;
        m_sDescription = sDescription;
        m_achieved = achieved;
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
    * getAchieved: get info whether step is 0: not active yet, 1: not achieved, 2: achieved.
    * @return int
    */
    int getAchieved() {
        return m_achieved;
    }
};


#endif

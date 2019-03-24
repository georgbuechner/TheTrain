/**
* CDialogOptionState.h
* Option States or states owmed by each state of the dialog. They Contain the options each state 
* has after the dialog partner said something. The id is a custom indicator for the OptionState,
* "text" is the text the player answers and "targetState" is the state this option state links to.
*/

#ifndef CDIALOGOPTIONSTATE_H
#define CDIALOGOPTIONSTATE_H

#include <iostream>
#include <string>

class CDialogOptionState
{
private:
    size_t m_keyword;           //Keyword
    std::string m_sText;        //Text
    std::string m_sTargetState; //State this state is linking to
    bool m_bActive;             //Indicating whether this options is already active

public:
    /**
    * Constructor
    * @parameter size_t (keyword)
    * @parameter string (text player can say)
    * @parameter string (id linking to next state)
    * @parameter bool (active yes/no)
    */
    CDialogOptionState(size_t keyword, std::string sText, std::string sTargetState, bool active) {

        //Assign attributes
        m_keyword = keyword;
        m_sText = sText;
        m_sTargetState = sTargetState;
        m_bActive = active;
    }

    // *** getter *** //
    
    /**
    * getKeyword: get optionstate's keyword.
    * @return size_t (state's keyword)
    */
    size_t getKeyword() {
        return m_keyword;
    }

    /**
    * getText: get text the player can say
    * @return string (text player can say)
    */
    std::string getText() {
        return m_sText;
    }

    /**
    * getTargetState: get string linking to target-state)
    * @return string (id linking to target state)
    */
    std::string getTargetState() {
        return m_sTargetState;
    }

    /**
    * getActive: get boolean indicating whether this state is already active
    * @return bool (active yes/no)
    */
    bool getActive() {
        return m_bActive;
    }

    // *** setter *** //
    
    /**
    * setActive: change status of option state
    * @parameter bool 
    */
    void setActive(bool active) {
        m_bActive = active;
    }
};

#endif 

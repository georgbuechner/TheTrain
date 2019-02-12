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
    size_t m_id;                //ID
    std::string m_sText;        //Text
    std::string m_sTargetState; //State this state is linking to

public:
    /**
    * Constructor
    * @parameter size_t (custom id)
    * @parameter string (text player can say)
    * @parameter string (id linking to next state)
    */
    CDialogOptionState(size_t id, std::string sText, std::string sTargetState) {

        //Assign attributes
        m_id = id;
        m_sText = sText;
        m_sTargetState = sTargetState;
    }

    // *** getter *** //
    
    /**
    * getID: get optionstate's id.
    * @return size_t (state's custom id)
    */
    size_t getID() {
        return m_id;
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
};

#endif 

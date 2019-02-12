/**
* CDialogState.h
* Class contains a state of the dialog. Each state has a custom id (also key of the map of states owned
* by the class CDialog.h. Each state has a speaker and a text taht is spoken. A boolean indicating 
* wheather state is the last state and a string "m_sDialogEnd" with custom message when dialig has 
* ended.
*/

#ifndef CDIALOGSTATE_H
#define CDIALOGSTATE_H

#include <iostream>
#include <map>
#include <string>
#include "CDialogOptionState.hpp"

//Forward declarations
class CDialogOptionState;

class CDialogState
{
private:
    std::string m_sID;          //Id
    std::string m_sText;        //Text
    std::string m_sSpeaker;     //String of person who is speaking
    std::string m_sDialogEnd;   //Text to print in case this is last state
   
    std::map<size_t, CDialogOptionState*> m_playerOptions;   //Player options

    bool m_end;             //Dialog ended?

public:
    /**
    * Constructor 
    * @parameter string (state-id)
    * @parameter string (state-text)
    * @parameter string (speaker)
    * @parameter string (custom text printed at end of dialog)
    * @parameter map<size_t, CDialogOptionState*> (map with options the player has)
    * @parameter bool (boolean indicating whether dialog hast enden)
    */
    CDialogState(std::string sID, std::string sText, std::string sSpeaker, std::string sDialogEnd, 
            std::map<size_t, CDialogOptionState*> playerOptions, bool end) {

        //Assign attributes
        m_sID = sID;
        m_sText = sText;
        m_sSpeaker = sSpeaker;
        m_sDialogEnd = sDialogEnd;
        m_playerOptions = playerOptions;
        m_end = end;
    }

    // *** getter *** //
    
    /**
    * getID: get state's id.
    * @return string (state's id)
    */
    std::string getID() {
        return m_sID;
    }

    /**
    * getText: get state's text.
    * @return string (state's text)
    */
    std::string getText() {
        return m_sText;
    }

    /**
    * getSpeaker: get speaker of state's text
    * @return string (speaker)
    */ 
    std::string getSpeaker() {
        return m_sSpeaker;
    }

    /**
    * getDialogEnd: get custom string printed when dialog ends
    * @return string (custom output when dialog has ended)
    */
    std::string getDialogEnd() {
        return m_sDialogEnd;
    }

    /**
    * getPlayerOptions: get map of option-states (options the player has)
    * @return map<size_t, CDialogOptionState*> (map of option-states)
    */
    std::map<size_t, CDialogOptionState*>& getPlayerOptions() {
        return m_playerOptions;
    }

    /**
    * getEnd: get boolean indicating whether dialog has ended or not.
    * @return bool (true = last state; false = not last state.)
    */
    bool getEnd() {
        return m_end;
    }
};

#endif


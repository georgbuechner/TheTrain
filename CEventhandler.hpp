/**
* CEventhandler.hpp
* Eventhandler react when an event is thrown, if they are of the same event type. reacting means
* they call their specific function. This means, when several handlers listens to the eventtype
* "talkTo" (f.e.), several things can happend, when you start talking to sb. 1. the basic handler
* for talkin to sb. calls the dialog. Then extra handlers could f.e. mark a quest as accomplished
* that urged to talk to that person. It could later become important to a a hierachy to the handlers
* calling handlers with higher priority first. At the moment they are called in the order they have 
* been added to the eventmanager. 
* Eventhandlers also have a custom id. At the moment the id is only used to finde the element in case
* the element hast to be removed from the eventmanager.
* @Author Jan van Dick
*/

#ifndef CEVENTHANDLER_H
#define CEVENTHANDLER_H

#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include "CGame.hpp"
#include "CEvent.hpp"

//Forward declarations
class CEvent;

class CEventhandler
{
    //Attributes
    std::string m_sID;                              //Custom id, used to remove handler from eventmanager
    void(CEventhandler::*m_func)(CEvent* event);    //Function called when handler reacts

public:
    /**
    * Constructor
    * @parameter string (eventhandler's custom id)
    * @parameter (CEventhandler::*m_func)(CEvent*) (function pointer of type "CEventhandler" taking an
    *                                               event from type CEvent* as parameter)
    */
    CEventhandler(std::string sID, void(CEventhandler::*func)(CEvent* event)) {

        //Assign attributes
        m_sID = sID;
        m_func = func;
    }


    // *** getter *** //
    
    /**
    * getID: get eventhanlder's custom id
    * @return string (ID)
    */
    std::string getID() {
        return m_sID;
    } 

    /** 
    * callHandlerFunction: call function of event handler 
    * @parameter CEvent* (poimnter to event that has been thrown)
    */
    void callHandlerFunction(CEvent* event) {
        (this->*m_func)(event);
    }

    // **** ****  handlers **** **** //

    // ** basic handlers ** // 
    void echo_showExits(CEvent* event);         //showing all exits         (ET: "showExits")
    void echo_changeRoom(CEvent* event);        //change room               (ET: "changeRoom")
    void echo_showChars(CEvent* event);         //show all chars            (ET: "showChars")
    void echo_talkTo(CEvent* event);            //start conversation        (ET: "talkTO")
    void echo_showActiveQuests(CEvent* event);  //show active quests        (ET: "showActiveQuests")
    void echo_showSolvedQuests(CEvent* event);  //show solved quests        (ET: "showSolvedQuests")
    void echo_endGame(CEvent* event);           //ending the game           (ET: "endGame")
    void echo_endGameDirectly(CEvent* event);   //ending game directly      (ET: "endGameDirectly")
    void echo_falseInput(CEvent* event);        //printing error message    (ET: "falseInput")


    // ** dialog handlers ** //

    //factory/parsenDialog.json"
    void echo_parsenDialogAnna(CEvent* event);
};

#endif

/**
* CEventmanager.h
* Class handling eventhandlers and event. An object of eventmanager basically merely contains a
* dictionary with eventhandlers. An basic functions to add a "listener" (eventhandler), to remove a 
* listener from the dictionary and to throw an event. When an event is trown all listeners from the 
* same event type react to the event. 
* @Author Jan van Dick
*/

#ifndef CEVENTMANAGER_H
#define CEVENTMANAGER_H

//Forward declarations 
class CEventhandler;
class CGame;

#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include "CEventhandler.hpp"
#include "CEvent.hpp"

class CEventmanager
{
private:
   
    //Attributes
    std::map<std::string, std::list<CEventhandler*>*> m_mapHandlers;   //Map with eventhandlers
    CGame* m_game;

public:
    /**
    * Constructor
    */
    CEventmanager(CGame* game) {
        m_game = game;
    }

    /** 
    * add_listener: add "listener" (eventhandler) to eventmanager.
    * @parameter string (event type)
    * @parameter CEventhandler* (Pointer to new eventhandler)
    */
    void add_listener(std::string sEventType, CEventhandler* eventhandler);

    /**
    * throw_event: call listeners for event.
    * @parameter CEvent* (Pointer to event thrown)
    */
    void throw_event(CEvent* event);

    /**
    * remove_listener: remove eventhandler from eventmanager.
    * @parameter string (event type)
    * @parameter string (eventhandler ID)
    */
    void remove_listener(std::string sEventType, std::string eventhandlerID);
};



#endif


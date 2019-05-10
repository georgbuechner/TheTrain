/**
* CEventmanager.h
* Class handling eventhandlers and event. An object of eventmanager basically merely contains a
* dictionary with eventhandlers. An basic functions to add a "listener" (eventhandler), to remove a 
* listener from the dictionary and to throw an event. When an event is trown all listeners from the 
* same event type react to the event. 
* @Author Jan van Dick
*/

#ifndef C_EVENTMANAGER_H
#define C_EVENTMANAGER_H

//Forward declarations 
#include <iostream>
#include <functional>
#include <string>
#include <string.h>
#include <map>
#include "CEvent.hpp"

class CEventManager
{
private:
   
    //Attributes
    std::map<std::string, std::list< std::function<void(CEvent*)>>> m_mapHandlers;

public:

    /** 
    * add_listener: add "listener" (eventhandler) to eventmanager.
    * @parameter string (event type)
    * @parameter CEventhandler* (Pointer to new eventhandler)
    */
    void add_listener(std::string sEventType, std::function<void(CEvent*)> func);

    /**
    * throw_event: call listeners for event.
    * @parameter CEvent* (Pointer to event thrown)
    */
    void throw_event(CEvent* event);
};

#endif


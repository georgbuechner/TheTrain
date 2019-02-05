//Eventmanager
// @Author Jan van Dick

#ifndef CEVENTMANAGER_H
#define CEVENTMANAGER_H


#include <iostream>
#include <string>
#include <list>
#include "CEventHandler.h"
#include "CEvent.h"

class CEventManager
{
private:
   std::map<std::string, std::list<CEventHandler*>*>* m_mapHandlers;

public:
    //Constructor
    CEventManager() {
        m_mapHandlers = new std::map<std::string, std::list<CEventHandler*>*>;
    }

    /** 
    * add_listener: add listener to event manager
    * @parameter string (event type)
    * @parameter CEventHandler (handler for new listener)
    */
    void add_listener(std::string sEventType, CEventHandler* eventHandler);

    /**
    * Throw event: call listeners for event
    * @parameter string (event type)
    */
    void throw_event(CEvent* event);

    /**
    * Remove eventHandler: remove eventhandler from eventmanager
    * @parameter string (event type)
    * @parameter string (eventhandler ID)
    */
    void delete_event(std::string sEventType, std::string eventHandlerID);
};


// *** CEventManager *** //

/** 
* add_listener: add listener to event manager
* @parameter string (event type)
* @parameter CEventHandler (handler for new listener)
*/
void CEventManager::add_listener(std::string sEventType, CEventHandler* handler) 
{
    //Add new entry to eventmanager
    if(m_mapHandlers->count(sEventType) == 0)
    {
        //Create empty list of event handelers
        std::list<CEventHandler*>* listEventHandlers = new std::list<CEventHandler*>;
        
        //Add event to list  
        listEventHandlers->push_back(handler);
        
        //Add  
        m_mapHandlers->insert(std::pair<std::string, std::list<CEventHandler*>*>
                                                    (sEventType, listEventHandlers));
    }

    //Add event to existing entry
    else
        m_mapHandlers->at(sEventType)->push_back(handler);
}

/**
* Remove eventHandler: remove eventhandler from eventmanager
* @parameter string (event type)
* @parameter string (eventhandler ID)
*/
void CEventManager::delete_event(std::string sEventType, std::string eventHandlerID)
{
    //Get list with all handlers of an event type
    std::list<CEventHandler*>* listEventHandlers = m_mapHandlers->at(sEventType);

    //Iterate over list of handlers and delete handler when found
    for(auto it=listEventHandlers->begin(); it!=listEventHandlers->end(); it++)
    {
        if(eventHandlerID.compare((*it)->getID()) == true)
        {
            listEventHandlers->erase(it); 
            break;
        }
    }
}

/**
* Throw event: call listeners for event
* @parameter string (event type)
*/
void CEventManager::throw_event(CEvent* event)
{
    //Get list with all handlers of an event type
    std::list<CEventHandler*>* listEventHandlers = m_mapHandlers->at(event->getEventType());

    //Iterate over list of handlers and delete handler when found
    for(auto it=listEventHandlers->begin(); it!=listEventHandlers->end(); it++)
        (*it)->callHandlerFunction(event);
}


#endif


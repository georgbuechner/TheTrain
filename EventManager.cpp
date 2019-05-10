// *** CEventmanager *** //

#include "CEventManager.hpp"

/** 
* add_listener: add "listener" (eventhandler) to event manager.
* @parameter string (event type)
* @parameter CEventhandler* (handler for new listener)
*/
void CEventManager::add_listener(std::string sEventType, std::function<void(std::string)>func) 
{
    //Add new entry to eventmanager
    if(m_mapHandlers.count(sEventType) == 0)
    {
        //Create empty map of event handelers
        std::list<std::function<void(std::string)>> lHandlers;
        
        //Add event to map 
        lHandlers.push_back(func);
        
        //Add  
        m_mapHandlers[sEventType] = lHandlers;
    }

    //Add event to existing entry
    else
        m_mapHandlers[sEventType].push_back(func);
}

/**
* Throw event: call listeners for event
* @parameter string (event type)
*/
void CEventManager::throw_event(std::string sEventType, std::string sEvent)
{
    //Get list with all handlers of an event type
    if(m_mapHandlers.count(sEventType) == 0)
        return;

    std::list<std::function<void(std::string)>> listHandlers = m_mapHandlers[sEventType];
    
    //Iterate over list of handlers and delete handler when found
    for(auto it=listHandlers.begin(); it!=listHandlers.end(); it++)
        (*it)(sEvent);
}

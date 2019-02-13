// *** CEventmanager *** //

#include "CEventmanager.hpp"

/** 
* add_listener: add "listener" (eventhandler) to event manager.
* @parameter string (event type)
* @parameter CEventhandler* (handler for new listener)
*/
void CEventmanager::add_listener(std::string sEventType, CEventhandler* handler) 
{
    //Add new entry to eventmanager
    if(m_mapHandlers.count(sEventType) == 0)
    {
        //Create empty list of event handelers
        std::list<CEventhandler*>* listEventhandlers = new std::list<CEventhandler*>;
        
        //Add event to list  
        listEventhandlers->push_back(handler);
        
        //Add  
        m_mapHandlers.insert(std::pair<std::string, std::list<CEventhandler*>*>
                                                    (sEventType, listEventhandlers));
    }

    //Add event to existing entry
    else
        m_mapHandlers.at(sEventType)->push_back(handler);
}

/**
* remove_listener: remove eventhandler from eventmanager
* @parameter string (event type)
* @parameter string (eventhandler ID)
*/
void CEventmanager::remove_listener(std::string sEventType, std::string eventHandlerID)
{
    //Get list with all handlers of an event type
    std::list<CEventhandler*>* listEventhandlers = m_mapHandlers.at(sEventType);

    //Iterate over list of handlers and delete handler when found
    for(auto it=listEventhandlers->begin(); it!=listEventhandlers->end(); it++)
    {
        if(strcmp(eventHandlerID.c_str(), (*it)->getID().c_str()) == 0)
        {
            listEventhandlers->erase(it); 
            return;
        }
    }

    std::cout << "Tried to remove " << eventHandlerID << " but could not be found!\n";
}

/**
* Throw event: call listeners for event
* @parameter string (event type)
*/
void CEventmanager::throw_event(CEvent* event)
{
    //Get list with all handlers of an event type
    if(m_mapHandlers.count(event->getEventType()) == 0)
        return;
    std::list<CEventhandler*>* listEventhandlers = m_mapHandlers.at(event->getEventType());

    //Add pointer of game to event
    event->setGame(m_game);

    //Iterate over list of handlers and delete handler when found
    for(auto it=listEventhandlers->begin(); it!=listEventhandlers->end(); it++)
        (*it)->callHandlerFunction(event);
}



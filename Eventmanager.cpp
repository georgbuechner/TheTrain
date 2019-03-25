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
        m_mapHandlers[sEventType] = listEventhandlers;
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


//Initialize map of all eventmanagers
std::map<std::string, CEventmanager*>CEventmanager::m_mapEMs = {};

/**
* initializeFunctions
* initialize all eventmanagers
*/
void CEventmanager::initializeManagers(CGame* game)
{
    // ***** Standard ***** //
    CEventmanager* em = new CEventmanager(game);
    m_mapEMs["standard"] = em;

    // ***** Dialog ***** //

    // --- factory/Dialogs/parsenDialog.json --- //
    CEventmanager* em1 = new CEventmanager(game);
    
    //Handlers
    CEventhandler* h_anna = new CEventhandler("quest_jay", &CEventhandler::echo_parsenDialogAnna);
    em1->add_listener("anna", h_anna);

    //Add to list
    m_mapEMs["factory/Dialogs/parsenDialog.json"] = em1;


    // ***** Quests ***** //

    
    // --- talk_to_Jay --- //
    CEventmanager* em2 = new CEventmanager(game); 

    //Handler: "findJay"
    CQuesthandler* h_findJay = new CQuesthandler("findJay", "talk_to_jay", "find_jay");
    em2->add_listener("showChars", h_findJay);

    //Handler: "talkToJay"
    CQuesthandler* h_talkToJay = new CQuesthandler("talkToJay", "talk_to_jay", "talk_to_jay");
    em2->add_listener("geschenk-geben", h_talkToJay);

    //Handler: talkToParsen
    CQuesthandler* h_talkToParsen = new CQuesthandler("talkToParsen", "talk_to_jay", "talk_to_parsen");
    em2->add_listener("jays_vorwurf", h_talkToParsen);

    /*/Step: "gibGeschenk"
    CEventhandler* h_geschenkGeben = new CEventhandler("gibGeschenk", &CEventhandler::echo_gibGeschenk);
    em->add_listener("gibGechenk", h_geschenkGeben);

    //Step: "gibGeschenkNicht"
    CEventhandler* h_geschenkNichtGeben = new CEventhandler("gibGeschenkNicht", 
                                                                &CEventhandler::echo_gibGeschenkNicht);
    em->add_listener("gibGeschenkNicht", h_geschenkNichtGeben); */

    m_mapEMs["talk_to_jay"] = em2;
}



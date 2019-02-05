//EventHandler
// @Author Jan van Dick

#ifndef CEVENTHANDLER_H
#define CEVENTHANDLER_H

#include <iostream>
#include <map>
#include <string>
#include "CGame.h"
#include "CEvent.h"

class CEventHandler
{
private:
    std::string m_sID;
    void(CEventHandler::*m_func)(CEvent* event);

public:
    CEventHandler(std::string sID, void(CEventHandler::*func)(CEvent* event)) {
        m_sID = sID;
        m_func = func;
    }

    // *** getter *** //
    
    /**
    * get ID
    * @return string (ID)
    */
    std::string getID() {
        return m_sID;
    } 

    /** 
    * callHandlerFunction: call function of event handler 
    */
    void callHandlerFunction(CEvent* event) {
        (this->*m_func)(event);
    }

    //*** events ***//
    void echo_showDoors(CEvent* event);
    void echo_changeRoom(CEvent* event);
    void echo_showPeople(CEvent* event);
    void echo_talkTo(CEvent* event);
};


// *** handlers *** //

/**
* handler_showDoors: show all doors in a room
*/
void CEventHandler::echo_showDoors(CEvent* event)
{
    size_t counter = 1;

     std::cout << "Doors: \n";
     std::map<size_t, CDoor*>* mapDoors = event->getPlayer()->getCurRoom()->getMapDoors();
     for(auto it=mapDoors->begin(); it!=mapDoors->end(); it++)
     {
        std::cout << counter << ": " << it->second->getName() << ".\n";
        counter++;
     }
     std::cout << "\n";
}

/**
* handler_changeRoom
*/
void CEventHandler::echo_changeRoom(CEvent* event)
{
    size_t counter = 0;
    std::string sWahl;
    size_t wahl;

    std::cout << "Doors: \n";
    std::map<size_t, CDoor*>* mapDoors = event->getPlayer()->getCurRoom()->getMapDoors();
    for(auto it=mapDoors->begin(); it!=mapDoors->end(); it++)
    {
        counter++;
        std::cout << counter << ": " << it->second->getName() << ".\n";
    }
    std::cout << "> "; 
    
    getline(cin, sWahl);
    wahl = std::stoi(sWahl);

    if(wahl <= counter)
    {
        CDoor* door = mapDoors->at(wahl-1);
        CRoom* room = event->getRooms()->at(door->getLinkedRoom());
        event->getPlayer()->setCurRoom(room);
            
        //Print description
        if(door->getAltDesc().length() > 0)
            std::cout << door->getAltDesc() << "\n";
        else 
        {
            std::cout << door->getHeadDesc()    << "\n";
            std::cout << room->getDescription() << "\n";
            std::cout << door->getFootDesc()    << "\n";
        }
    }

    else
        std::cout << "Wrong Input! Door does not exist. Please try again.\n\n";
}

/**
* handler_showPeople
*/
void CEventHandler::echo_showPeople(CEvent* event)
{
    size_t counter = 0;
            
    std::cout << "People in the room: \n";
    std::map<std::string, CCharacter*>* mapChars = event->getPlayer()->getCurRoom()->getMapChars();
    for(auto it=mapChars->begin(); it!=mapChars->end(); it++)
    {
        counter++;
        std::cout << counter << ": " << it->second->getName() << ".\n";
    }
    std::cout << "\n";
}
   

/**
* handler_talkTo
*/
void CEventHandler::echo_talkTo(CEvent* event)
{
    size_t counter = 0;
    std::string sChoice;
    size_t choice;
            
    std::cout << "People in the room: \n";
    std::map<std::string, CCharacter*>* mapChars = event->getPlayer()->getCurRoom()->getMapChars();
    for(auto it=mapChars->begin(); it!=mapChars->end(); it++)
    {
        counter++;
        std::cout << counter << ": " << it->second->getName() << ".\n";
    }
    std::cout << ">"; 

    getline(cin, sChoice);
    choice = std::stoi(sChoice);

    counter = 0;
    bool found = false;
    for(auto it=mapChars->begin(); it!=mapChars->end(); it++)
    {
        counter++;
        if(choice == counter)
        {
            it->second->getDialog()->startDialog();
            found = true;
        }
    }

    if(found == false)
        std::cout << "Character not found.\n";

    std::cout << "\n";
}



#endif

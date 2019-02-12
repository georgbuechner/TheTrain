/**
* CEvent.hpp
* An event is created when something happens. An event has an eventtype (f.e. "takeItem") and an 
* identifier, mostly used to indticate f.e. which item has been taken. So if the player picks up
* a book. An event will be created with eventtype "takeItem" and identifier "book" (probably specific
* name of the book). The event also owns a pointer to the game (later maybe the current context). The
* game/ context is needed, so the eventhandler the event is passend on to can acces certain objects.
* It is probable that an eventhandler will always need to acces the player (f.e. to add the book to the 
* player's inventory.) Other, more specific eventhandlers, might need to access other characters in the 
* game or items etc. The game/ context provoides access to most objects in the game. 
* @Author Jan van Dick
*/

#ifndef CEVENT_H
#define CEVENT_H

#include <iostream>
#include <map>
#include <string>
#include "CGame.hpp"

//Forward declarations
class CGame;

class CEvent
{
private:

    //Attribiutes
    std::string m_sEventType;   //Indicating event type. F.e. "takeItem", "changeRoom"
    std::string m_sIdentifier;  //Identifier adding information to the event type, f.e. which item has
                                //been taken or which room does the player want to change to.

    CGame* m_game;              //Pointer to the game/ context

public:
    /**
    * Constructor
    * @parameter string (Event type)
    * @parameter string (identifier)
    */
    CEvent(std::string sEventType, std::string sIdentifier) {

        //Assign attributes
        m_sEventType = sEventType;
        m_sIdentifier = sIdentifier;
    }

    
    // ** getter ** //

    /**
    * getEventType: get event type.
    * @return string (event type)
    */
    std::string getEventType() {
        return m_sEventType;
    }

    /**
    * getIdentifier: get identifier with extra information about what happend.
    * @return string (identifier)
    */
    std::string getIdentifier() {
        return m_sIdentifier;
    }

    /**
    * getGame: get pointer to the game/ context.
    * @return CGame* (Pointer to the game/ context)
    */
    CGame* getGame() {
        return m_game;
    }

    
    // ** setter ** //

    /**
    * setGame: set game/ current context.
    * @parameter Cgame* (pointer to game/ context) 
    */
    void setGame(CGame* game) {
        m_game = game;
    }


};

#endif

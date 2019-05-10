#include "CEvent.hpp"

/**
* Constructor
* @parameter string (Event type)
* @parameter string (identifier)
*/
CEvent::CEvent(std::string sEventType, std::string sIdentifier) {

    //Assign attributes
    m_sEventType = sEventType;
    m_sIdentifier = sIdentifier;
}


// ** getter ** //

/**
* getEventType: get event type.
* @return string (event type)
*/
std::string CEvent::getEventType() {
    return m_sEventType;
}

/**
* getIdentifier: get identifier with extra information about what happend.
* @return string (identifier)
*/
std::string CEvent::getIdentifier() {
    return m_sIdentifier;
}

/**
* getGame: get pointer to the game/ context.
* @return CGame* (Pointer to the game/ context)
*/
CGame* CEvent::getGame() {
    return m_game;
}


// ** setter ** //

/**
* setGame: set game/ current context.
* @parameter Cgame* (pointer to game/ context) 
*/
void CEvent::setGame(CGame* game) {
    m_game = game;
}



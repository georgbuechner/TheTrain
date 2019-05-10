#include "CPlayer.hpp"


/** 
* Constructor: initialising player with name and current room
*/
CPlayer::CPlayer(std::string sName, CRoom* curRoom) {
    m_sName.assign(sName);
    m_curRoom = curRoom;
}

// ** Getter ** //

/**
* getName: return player's name
* @return string (player's name)
*/
std::string  CPlayer::getName() {
    return m_sName;
}

/**
* getCurRoom: return player's current room
* @return CRoom* (player's current room)
*/
CRoom* CPlayer::getCurRoom() {
    return m_curRoom;
}

/**
* getQuests: return player's quests 
* @return list<Quests*> (List of player's quests)
*/
std::list<CQuest*>& CPlayer::getQuests() {
    return m_listQuests;
}

/**
* getEventmanagers: return player's eventmanagers 
* @return map<CEventmanager*> (List of player's eventmanagers)
*/
std::map<std::string, CEventmanager*>& CPlayer::getEventmanagers() {
    return m_mapEventmanagers;
}

//Setter

/** 
* setName: set name of player
* @parameter string (name of player)
*/
void CPlayer::setName(std::string sName) {
    m_sName = sName;
}

/**
* setCurRoom: set player's current room
*/ 
void CPlayer::setCurRoom(CRoom* newRoom) {
    m_curRoom = newRoom;
}

void CPlayer::showExits(std::string sEvent) {
    m_curRoom->showExits();
}

void CPlayer::changeRoom(std::map<std::string, CRoom*> mapRooms, std::string sEvent)
{
    CRoom* newRoom = m_curRoom->changeRoom(sEvent, mapRooms);
    if(newRoom)
        m_curRoom = newRoom;

    else
        std::cout << "Wrong Input! Exit " << sEvent << " does not exist. Please try again.\n\n";
}


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


// *** player function *** //

/**
* handler: showExits: show all exits in a room.
* Eventtype: "showExits"
* @parameter string (Identifier of event thrown)
*/
void CPlayer::showExits(std::string sEvent) {
    m_curRoom->showExits();
}

/**
* handler: changeRoom: change room to selected room.
* Eventtype: "changeRoom"
* @parameter string (Identifier of event thrown: selected exit)
*/
void CPlayer::changeRoom(std::map<std::string, CRoom*> mapRooms, std::string sEvent)
{
    CRoom* newRoom = m_curRoom->changeRoom(sEvent, mapRooms);
    if(newRoom)
        m_curRoom = newRoom;

    else
        std::cout << "Wrong Input! Exit " << sEvent << " does not exist. Please try again.\n\n";
}

/**
* handler: showChars: print all characters in current room
* Eventtype: "showChars"
* @parameter string (Identifier of event thrown)
*/
void CPlayer::showChars(std::string sEvent) {
    m_curRoom->showChars();
}

/**
* handler: talkTo: call dialog of selected character
* Eventtype: "talkTo"
* @parameter sting (Identifier of event thrown: selected character)
*/
void CPlayer::talkTo(std::map<std::string, CCharacter*> mapChars, std::string sEvent)
{
    CCharacter* selectedChar = m_curRoom->getChar(sEvent, mapChars);
    if(selectedChar)
        selectedChar->getDialog()->startDialog();

    else
        std::cout << "Character not found. \n";
} 

/**
* handler: showQuests: show all quests.
* EventType: "showQuests"
* @parameter string (Identifier of the event thrown)
*/
void CPlayer::showQuests(std::string sEvent)
{
    size_t counter = 1;

    //Print all active quests
    std::cout << "\nQuests: (Anzahl Quests: " << m_listQuests.size() << ") \n";
    for(auto it=m_listQuests.begin(); it!=m_listQuests.end(); it++)
    {
        if((*it)->getAchieved() == false)
            std::cout << counter << ": " << (*it)->getName() << " (active) \n";
        else
            std::cout << counter << ": " << (*it)->getName() << " (solved) \n";
        counter++;
    }

    //Return if there are no active quests
    if(counter == 1)
        return;

    //Select quest for further information
    std::cout << "Wähle Quest (Nummer): ";

    //Player input and convert string to int
    std::string sChoose;
    size_t choose;
    getline(cin, sChoose);
    choose = std::stoi(sChoose);

    //check whether input is correct
    if(choose < 1 || choose > counter)
    {
        std::cout << "Falsche EIngabe!\n";
        return;
    }

    //Print quest information
    auto it = m_listQuests.begin();
    advance(it, choose-1);
    (*it)->printQuest();
}

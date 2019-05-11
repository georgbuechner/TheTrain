//Header CPlayer
// @Author = Jan van Dick

#ifndef CPLAYER_H
#define CPLAYER_H

#include <string>
#include <list>
#include "CRoom.hpp"
#include "CQuest.hpp"
#include "CEventmanager.hpp"

using namespace std;

class CPlayer
{
private:

    //Attributes 
    std::string m_sName;    //Name of Player (can be chosen at the beginning of the game)
    CRoom* m_curRoom;       //The room the player is currently in
    std::list<CQuest*> m_listQuests;    //List of all the players quests

    std::map<std::string, CEventmanager*> m_mapEventmanagers;      //List of all eventmanagers

public:

    /** 
    * Constructor: initialising player with name and current room
    */
    CPlayer(std::string sName, CRoom* curRoom);

    // ** Getter ** //

    /**
    * getName: return player's name
    * @return string (player's name)
    */
    std::string  getName(); 

    /**
    * getCurRoom: return player's current room
    * @return CRoom* (player's current room)
    */
    CRoom* getCurRoom();

    /**
    * getQuests: return player's quests 
    * @return list<Quests*> (List of player's quests)
    */
    std::list<CQuest*>& getQuests();

    /**
    * getEventmanagers: return player's eventmanagers 
    * @return map<CEventmanager*> (List of player's eventmanagers)
    */
    std::map<std::string, CEventmanager*>& getEventmanagers();

    //Setter

    /** 
    * setName: set name of player
    * @parameter string (name of player)
    */
    void setName(std::string sName);

    /**
    * setCurRoom: set player's current room
    */ 
    void setCurRoom(CRoom* newRoom);


    // *** player function *** //

    /**
    * handler: showExits: show all exits in a room.
    * Eventtype: "showExits"
    * @parameter string (Identifier of event thrown)
    */
    void showExits(std::string sEvent);

    /**
    * handler: changeRoom: change room to selected room.
    * Eventtype: "changeRoom"
    * @parameter string (Identifier of event thrown: selected exit)
    */
    void changeRoom(std::map<std::string, CRoom*> mapRooms, std::string sEvent);

    /**
    * handler: showChars: print all characters in current room
    * Eventtype: "showChars"
    * @parameter string (Identifier of event thrown)
    */
    void showChars(std::string sEvent);

    /**
    * handler: talkTo: call dialog of selected character
    * Eventtype: "talkTo"
    * @parameter sting (Identifier of event thrown: selected character)
    */
    void talkTo(std::map<std::string, CCharacter*> mapChars, std::string sEvent);

    /**
    * handler: showActiveQuests: show all active quests.
    * EventType: "showActiveQuests"
    * @parameter CEvent* (pointer to event thrown)
    */
    void showQuests(std::string sEvent);
};

#endif


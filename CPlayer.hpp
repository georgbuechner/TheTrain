//Header CPlayer
// @Author = Jan van Dick

#ifndef CPLAYER_H
#define CPLAYER_H

class CEvent;

#include <iostream>
#include <string>
#include <list>
#include "CRoom.hpp"
#include "CQuest.hpp"
#include "CEvent.hpp"

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

    void showExits(CEvent* event);

    void changeRoom(std::map<std::string, CRoom*> mapRooms, CEvent* event);
    
};

#endif


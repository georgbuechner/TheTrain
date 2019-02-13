//Header CPlayer
// @Author = Jan van Dick

#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <string>
#include <list>
#include "CRoom.hpp"
#include "CQuest.hpp"

using namespace std;


class CPlayer
{
private:

    //Attributes 
    std::string m_sName;    //Name of Player (can be chosen at the beginning of the game)
    CRoom* m_curRoom;       //The room the player is currently in
    std::list<CQuest*> m_listQuests;    //List of all the players quests

public:

    /** 
    * Constructor: initialising player with name and current room
    */
    CPlayer(std::string sName, CRoom* curRoom) {
        m_sName.assign(sName);
        m_curRoom = curRoom;
    }

    // ** Getter ** //

    /**
    * getName: return player's name
    * @return string (player#s name)
    */
    std::string  getName() {
        return m_sName;
    }

    /**
    * getCurRoom: return player's current room
    * @return CRoom* (player's current room)
    */
    CRoom* getCurRoom() {
        return m_curRoom;
    }

    /**
    * getQuests: return player's quests 
    * @return list<Quests*> (List of player's quests)
    */
    std::list<CQuest*> getQuests() {
        return m_listQuests;
    }



    //Setter

    /** 
    * setName: set name of player
    * @parameter string (name of player)
    */
    void setName(std::string sName) {
        m_sName = sName;
    }

    /**
    * setCurRoom: set player's current room
    */ 
    void setCurRoom(CRoom* newRoom) {
        m_curRoom = newRoom;
    }
};

#endif


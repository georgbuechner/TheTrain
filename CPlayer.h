//Header CPlayer
// @Author = Jan van Dick

#ifndef CPLAYER_H
#define CPLAYER_H

#include <map>
#include "CRoom.h"

using namespace std;


class CPlayer
{
private:

    //Attributes 
    std::string m_sName;    //Name of Player (can be chosen at the beginning of the game)

    CRoom* m_curRoom;       //The room the player is currently in

public:
    //Constructor
    CPlayer(std::string sName, CRoom* curRoom) {
        m_sName.assign(sName);
        m_curRoom = curRoom;
    }

    //Getter

    //Get player's name
    std::string  getName() {
        return m_sName;
    }

    //Get player's curren room
    CRoom* getCurRoom() {
        return m_curRoom;
    }

    //Setter

    //Set Room
    void setCurRoom(CRoom* newRoom) {
        m_curRoom = newRoom;
    }

};

#endif


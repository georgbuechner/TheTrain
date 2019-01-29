//CGame.h

#ifndef CGAME_H
#define CGAME_H

#include <iostream>
#include <list>
#include <map>
#include "CDoor.h"
#include "CRoom.h"
#include "CPlayer.h"
#include "json.hpp"

class CGame
{
private:
    CPlayer* m_Player;
    std::map<size_t, CDoor*>* m_mapAllDoors;    //Dictionary of all doors in the game.
    std::map<size_t, CRoom*>* m_mapAllRooms;    //Dictionary of all doors in the game.

public:
    //Constructor
    CGame() {
        m_mapAllDoors = new std::map<size_t, CDoor*>;
        m_mapAllRooms = new std::map<size_t, CRoom*>;
    }

    //Word factory and factorys
    void worldFactory();
    void roomFactory(std::string sPath);
    void doorFactory(std::string sPath);


    void play();    
};
   
#endif
    

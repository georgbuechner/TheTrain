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
    std::map<std::string, CRoom*>* m_mapAllRooms;    //Dictionary of all doors in the game.

public:
    //Constructor
    CGame() {
        m_mapAllRooms = new std::map<std::string, CRoom*>;
    }

    //Word factory and factorys
    void worldFactory();
    void roomFactory(std::string sPath);
    std::map<size_t, CDoor*>* doorFactory(nlohmann::json j_listDoors);


    void play();    
};
   
#endif
    

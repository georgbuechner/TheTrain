//CGame.h

#ifndef CGAME_H
#define CGAME_H

#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include "CDoor.h"
#include "CRoom.h"
#include "CPlayer.h"
#include "CDialog.h"
#include "CEventManager.h"
#include "CEvent.h"
#include "CEventHandler.h"
#include "CCommandParser.h"
#include "json.hpp"

class CGame
{
private:
    CPlayer* m_Player;      //Player
    std::map<std::string, CRoom*>* m_mapAllRooms;    //Dictionary of all doors in the game.

public:
    //Constructor
    CGame() {
        m_mapAllRooms = new std::map<std::string, CRoom*>;
    }

    // ** getter ** //

    /**
    * getPlayer: return player
    * @return CPlayer* (player)
    */
    CPlayer* getPlayer() {
        return m_Player;
    }

    /**
    * getMapRooms: return map of all rooms
    * @return map<string, CRoom*>* (map of all rooms in the game)
    */
    std::map<std::string, CRoom*>* getMapRooms() {
        return m_mapAllRooms;
    }

    //Word factory and factorys
    void worldFactory();
    std::map<std::string, CRoom*>*      roomFactory(std::string sPath);
    std::map<size_t, CDoor*>*           doorFactory(nlohmann::json j_listDoors);
    std::map<std::string, CCharacter*>* characterFactory(nlohmann::json j_listCharacters);   
    CDialog*                            dialogFactory(std::string sPath);

    void play();    
};
   
#endif
    

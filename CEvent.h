//Event
// @Author Jan van Dick

#ifndef CEVENT_H
#define CEVENT_H

#include <iostream>
#include <map>
#include <string>
#include "CGame.h"

class CEvent
{
private:
    std::string m_sEventType;

    //Value that might come in handy
    CPlayer* m_player;
    std::map<std::string, CRoom*>* m_mapRooms;

public:
    //Constructor
    CEvent(std::string sEventType) 
    {
        m_sEventType = sEventType;
        m_player = NULL;
        m_mapRooms = NULL;
    }

    CEvent(std::string sEventType, CPlayer* player)
    {
        m_sEventType = sEventType;
        m_player = player;
        m_mapRooms = NULL;
    }

    CEvent(std::string sEventType, std::map<std::string, CRoom*>* rooms)
    {
        m_sEventType = sEventType;
        m_player = NULL;
        m_mapRooms = rooms;
    }

    CEvent(std::string sEventType, CPlayer* player, std::map<std::string, CRoom*>* rooms)
    {
        m_sEventType = sEventType;
        m_player = player;
        m_mapRooms = rooms;
    }
    std::string getEventType() {
        return m_sEventType;
    }

    CPlayer* getPlayer() {

        return m_player;
    }
    std::map<std::string, CRoom*>* getRooms() {
        return m_mapRooms;
    }
};

#endif

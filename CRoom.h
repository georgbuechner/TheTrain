//Header CRoom.h
// @Author = Georg Buechner 

#ifndef CROOM_H
#define CROOM_H

#include <string>
#include <map>
#include "CDoor.h"

//Forward declarations:
class CPerson;

//Class for object: room
class CRoom 
{
private:
    std::string m_sName;           //Name of the room
    std::map<size_t, CDoor*>* m_mapOfDoors;  //List of doors leading out of this room 

public:
    //Constructor
    CRoom(std::string sName, std::map<size_t, CDoor*> *mapDoors) {
        m_sName.assign(sName);
        m_mapOfDoors = mapDoors;
    }

    //Getter
    
    //Get the rooms name
    std::string getName() {
        return m_sName;
    }

    //Get list of all doors leading out off this room
    std::map<size_t, CDoor*>* getDoors() {
        return m_mapOfDoors;
    }

};

#endif


//Header CRoom.h
// @Author = Georg Buechner 

#ifndef CROOM_H
#define CROOM_H

#include <string>
#include <map>
#include "CDoor.h"
#include "CCharacter.h"

//Forward declarations:
class CCharacter;

//Class for object: room
class CRoom 
{
private:
    std::string m_sName;                            //Name of the room
    std::string m_sDescription;                     //Room description

    std::map<size_t, CDoor*>*        m_mapOfDoors;  //List of doors leading out of this room 
    std::map<std::string, CCharacter*>* m_mapOfCharacters; //List of people in the room

public:
    //Constructor
    CRoom(std::string sName, std::string sDescription,  std::map<size_t, CDoor*>* mapDoors, 
          std::map<std::string, CCharacter*>* mapCharacters) {

        m_sName         = sName;
        m_sDescription  = sDescription;
        m_mapOfDoors    = mapDoors;
        m_mapOfCharacters = mapCharacters;
    }

    //Getter
    
    //Get the rooms name
    std::string getName() {
        return m_sName;
    }

    //Get description of room
    std::string getDescription() {
        return m_sDescription;
    }

    //Get list of all doors leading out off this room
    std::map<size_t, CDoor*>* getMapDoors() {
        return m_mapOfDoors;
    }

    //Get list of all people in the room
    std::map<std::string, CCharacter*>* getMapChars() {
        return m_mapOfCharacters;
    }

};

#endif


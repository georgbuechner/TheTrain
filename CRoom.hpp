/**
* CRoom.h
* Class for room objects. A room contains items and exits. It also has a custom description
* which is printed in addition to specific door-descriptions. (head, foot, alternative) This
* might be changed later to a jinger script handling the descriptions.
* @Author = fux
*/

#ifndef CROOM_H
#define CROOM_H

#include <string>
#include <map>
#include "CExit.hpp"
#include "CCharacter.hpp"

//Forward declarations:
class CCharacter;

class CRoom 
{
private:
    std::string m_sName;                            //Name of the room
    std::string m_sDescription;                     //Room description

    std::map<size_t, CExit*> m_mapOfExits;                  //List of exits leading out of this room 
    std::map<std::string, std::string> m_mapOfCharacters;   //List of people in the room

public:
    /**
    * Constructor
    * @parameter string (room's name)
    * @parameter string (room's custom description)
    * @parameter map<size_t, CExit*>        (map with all exits)
    * @parameter map<string, CCharacter*>   (map with all characters)
    */
    CRoom(std::string sName, std::string sDescription,  std::map<size_t, CExit*> mapExits, 
          std::map<std::string, std::string> mapCharacters) {

        m_sName         = sName;
        m_sDescription  = sDescription;
        m_mapOfExits    = mapExits;
        m_mapOfCharacters = mapCharacters;
    }

    // ** Getter ** //
    
    /**
    * getName: get the room's name.
    * @return string (room's name)
    */
    std::string getName() {
        return m_sName;
    }

    /**
    * getDescription: get room's custom description
    * @return string (room's custim description)
    */
    std::string getDescription() {
        return m_sDescription;
    }

    /**
    * getMapExits: get map of all exits leading out off this room
    * @return map<size_t, CExit*> (map of all the room's exits)
    */
    std::map<size_t, CExit*>& getMapExits() {
        return m_mapOfExits;
    }

    /**
    * getMapChars: get map of all people in the room.
    * @return map<string, CCharacter*> (map of all the room's characters)
    */
    std::map<std::string, std::string>& getMapChars() {
        return m_mapOfCharacters;
    }
};

#endif
 

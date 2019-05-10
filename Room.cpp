#include "CRoom.hpp"

/**
* Constructor
* @parameter string (room's name)
* @parameter string (room's custom description)
* @parameter map<size_t, CExit*>        (map with all exits)
* @parameter map<string, CCharacter*>   (map with all characters)
*/
CRoom::CRoom(std::string sName, std::string sDescription,  std::map<size_t, CExit*> mapExits, 
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
std::string CRoom::getName() {
    return m_sName;
}

/**
* getDescription: get room's custom description
* @return string (room's custim description)
*/
std::string CRoom::getDescription() {
    return m_sDescription;
}

/**
* getMapExits: get map of all exits leading out off this room
* @return map<size_t, CExit*> (map of all the room's exits)
*/
std::map<size_t, CExit*>& CRoom::getMapExits() {
    return m_mapOfExits;
}

/**
* getMapChars: get map of all people in the room.
* @return map<string, CCharacter*> (map of all the room's characters)
*/
std::map<std::string, std::string>& CRoom::getMapChars() {
    return m_mapOfCharacters;
}

void CRoom::printDescription(CExit* exit)
{
    //Check whether exit has an alternative description
    if(exit->getAltDesc().length() > 0)
        std::cout << exit->getAltDesc() << "\n";

    //Print secriptions in normal order
    else 
    {
        std::cout << exit->getHeadDesc(); //Header description
        std::cout << getDescription();    //Room description
        std::cout << exit->getFootDesc(); //Footer description
        std::cout << "\n";
    }

    std::cout << "\n";
}

void CRoom::showExits() {
    //Attributes
    size_t counter = 1;

    
    //Iterate over map of exits in room and print name. Add a number infront of exit
    std::cout << "Exits: \n";
    for(auto it=m_mapOfExits.begin(); it!=m_mapOfExits.end(); it++)
    {
        std::cout << counter << ": " << it->second->getName() << ".\n";
        counter++;
    }

    std::cout << "\n";
}

CRoom* CRoom::changeRoom(std::string sRoom, std::map<std::string, CRoom*> mapRooms)
{
    CFunctions function;
    for(auto it=m_mapOfExits.begin(); it!=m_mapOfExits.end(); it++)
    {
        if(function.in(sRoom, it->second->getTake()) == true)
        {
            printDescription(it->second);
            return mapRooms[it->second->getLinkedRoom()];
        }
    }

    return NULL;
}



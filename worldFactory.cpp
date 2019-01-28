//wordFactory -> memberfunction of CGame.h

#include "CGame.h"

void CGame::worldFactory()
{
    //***** Create Rooms *****//
    CRoom* Abteil   = roomFactory("Abteil", 0);
    CRoom* Flur     = roomFactory("Flur", 1);
    CRoom* Johannes = roomFactory("Johannes", 2);
    CRoom* Anna = roomFactory("Anna", 3);


    //***** Create doors *****//

    //Door: Abteil -> Flur
    std::vector<std::string> sDescription = {"Abteil-Flur1.txt"};
    doorFactory("Abteil-Flur", Abteil, Flur, sDescription, &CDoor::DescCall_Standard, 0);

    //Door: Flur -> Abteil
    sDescription = {"Flur-Abteil1.txt"};
    doorFactory("Flur-Abteil", Flur, Abteil, sDescription, &CDoor::DescCall_Standard, 1);

    //Door: Abteil -> Johannes
    sDescription = {"Abteil-Johannes.txt"};
    doorFactory("Abteil-Johannes", Abteil, Johannes, sDescription, &CDoor::DescCall_Standard, 2);

    //Door: Abteil -> Johannes
    sDescription = {"Johannes-Anna1.txt"};
    doorFactory("Johannes-Anna", Johannes, Anna, sDescription, &CDoor::DescCall_Standard, 2);

    //***** Create Player *****//
    m_Player = new CPlayer("Nikolaija", Abteil); 
}

void CGame::doorFactory(std::string sName, CRoom* fromRoom, CRoom* toRoom, 
            std::vector<std::string> sDescription, void(CDoor::*callDescription)(), size_t num)
{
    //Create door
    CDoor* door = new CDoor(sName, toRoom, sDescription, callDescription);

    //Add door to list of doors 
    m_mapAllDoors->insert(std::pair<size_t, CDoor*> (num, door));

    //Add Door to list of doors from "fromRoom"
    fromRoom->getDoors()->insert(std::pair<size_t, CDoor*> (fromRoom->getDoors()->size(), door));
}

CRoom* CGame::roomFactory(std::string sName, size_t num)
{
    //Create empty map of doors
    std::map<size_t, CDoor*>* mapDoors = new std::map<size_t, CDoor*>;

    //Create room
    CRoom* room = new CRoom(sName, mapDoors);

    //Add room to map of all rooms
    m_mapAllRooms->insert(std::pair<size_t, CRoom*> (num, room));

    return room;   
}
    

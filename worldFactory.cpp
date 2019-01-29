//wordFactory -> memberfunction of CGame.h

#include "CGame.h"

void CGame::worldFactory()
{
    //***** Create Rooms *****//


    roomFactory("factory/rooms.json");

    //***** Create doors *****//
    doorFactory("factory/doors.json");
    
    //***** Create Player *****//
    m_Player = new CPlayer("Nikolaija", m_mapAllRooms->at(0)); 
}

void CGame::doorFactory(std::string sPath)
{
    //Read json creating all rooms
    std::ifstream read(sPath);

    //Check wether json could be opened
    if(!read)
    {
        std::cout << "Error reading " << sPath << ".\n";
        return;
    }

    //Load data into a json
    nlohmann::json j_listDoors;
    read >> j_listDoors;
    read.close();
    
    //Create a vector of all json objects (all doors)
    std::vector<nlohmann::json> listDoors = j_listDoors;

    //Iterate over all doors and create each door 
    for(size_t it = 0; it < listDoors.size(); it++)
    {
        //Create a new json for current room
        nlohmann::json j_door=listDoors[it];

        //Create door 
        std::string sName   = j_door["name"];
        std::cout << sName << "\n";
        size_t toRoom       = j_door["to"];
        std::cout << toRoom << "\n";
        std::vector<std::string> sDescriptions = j_door["descriptions"];
        std::cout << sDescriptions[0] << "\n";
        CDoor* door = new CDoor(sName, m_mapAllRooms->at(toRoom), sDescriptions, &CDoor::DescCall_Standard); 

        std::cout << "3\n";
        //Add door to list of doors 
        m_mapAllDoors->insert(std::pair<size_t, CDoor*> (it, door));

        std::cout << "4\n";
        //Add Door to list of doors from "fromRoom"
        CRoom* fRoom = m_mapAllRooms->at(j_door["from"]);
        fRoom->getDoors()->insert(std::pair<size_t, CDoor*> (fRoom->getDoors()->size(), door));
    }
}

void CGame::roomFactory(std::string sPath)
{
    //Read json creating all rooms
    std::ifstream read(sPath);

    //Check wether json could be opened
    if(!read)
    {
        std::cout << "Error reading " << sPath << ".\n";
        return;
    }

    //Load data into a json
    nlohmann::json j_listRooms;
    read >> j_listRooms;
    read.close();
    
    //Create a vector of all json objects (all rooms)
    std::vector<nlohmann::json> listRooms = j_listRooms;

    //Iterate over all rooms and create each room
    for(size_t it = 0; it < listRooms.size(); it++)
    {
        //Create a new json for current room
        nlohmann::json j_room=listRooms[it];

        //Create empty map of doors 
        std::map<size_t, CDoor*>* mapDoors = new std::map<size_t, CDoor*>;
    
        //Create room
        CRoom* room = new CRoom(j_room["name"], mapDoors);

        //Add room to map of all rooms
        m_mapAllRooms->insert(std::pair<size_t, CRoom*>(it, room));
    }
}
        
    
    

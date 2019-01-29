//wordFactory -> memberfunction of CGame.h

#include "CGame.h"

void CGame::worldFactory()
{
    //***** Create Rooms *****//
    m_mapAllRooms = roomFactory("factory/rooms.json");

    std::cout << "Parsing complete! \n";

    //***** Create Player *****//
    m_Player = new CPlayer("Nikolaija", m_mapAllRooms->at("abteil_c")); 
}

std::map<size_t, CDoor*>* CGame::doorFactory(nlohmann::json j_listDoors)
{
    //Create empty map of doors
    std::map<size_t, CDoor*>* mapDoors = new std::map<size_t, CDoor*>;

    //Iterate over all doors and create each door 
    for(size_t it = 0; it < j_listDoors.size(); it++)
    {
        //Create a new json for current room
        nlohmann::json j_door=j_listDoors[it];

        //Create door 
        std::string sName   = j_door["name"];
        std::string sToRoom = j_door["to"];
        std::vector<std::string> sDescriptions = j_door["descriptions"];
        CDoor* door = new CDoor(sName, sToRoom, sDescriptions, &CDoor::DescCall_Standard); 

        mapDoors->insert(std::pair<size_t, CDoor*>(it, door)); 
    }

    return mapDoors;
}

//Parse room and return map of all parsed rooms
std::map<std::string, CRoom*>* CGame::roomFactory(std::string sPath)
{
    //Read json creating all rooms
    std::ifstream read(sPath);

    //Check wether json could be opened
    if(!read)
    {
        std::cout << "Error reading " << sPath << ".\n";
        return NULL;
    }

    //Load data into a json
    nlohmann::json j_listRooms;
    read >> j_listRooms;
    read.close();
    
    //Create a vector of all json objects (all rooms)
    std::vector<nlohmann::json> listRooms = j_listRooms;

    //Create empty map of rooms
    std::map<std::string, CRoom*>* mapRooms = new std::map<std::string, CRoom*>;

    //Iterate over all rooms and create each room
    for(size_t it = 0; it < listRooms.size(); it++)
    {
        //Create a new json for current room
        nlohmann::json j_room=listRooms[it];

        std::vector<nlohmann::json> j_listDoors = j_room["exits"];

        //Create empty map of doors 
        std::map<size_t, CDoor*>* mapDoors = doorFactory(j_listDoors);
    
        //Create room
        CRoom* room = new CRoom(j_room["name"], mapDoors);

        //Add room to map of all rooms
        mapRooms->insert(std::pair<std::string, CRoom*>(j_room["id"], room));

        std::cout << j_room["name"] << " parsed successfully! \n";
    }

    return mapRooms;
}
        
    
    

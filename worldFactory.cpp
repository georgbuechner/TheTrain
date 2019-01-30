//wordFactory -> memberfunction of CGame.h

#include "CGame.h"

void CGame::worldFactory()
{

    dialogFactory("factory/dialogs.json");

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

std::map<std::string, CCharacter*>* CGame::characterFactory(nlohmann::json j_listCharacters)
{
    //Create empty map of doors
    std::map<std::string, CCharacter*>* mapCharacters= new std::map<std::string, CCharacter*>;

    //Iterate over all doors and create each person
    for(size_t it = 0; it<j_listCharacters.size(); it++)
    {
        //Create a new json for current person
        nlohmann::json j_Character= j_listCharacters[it];

        //Create person
        std::string sName   = j_Character["name"];
        std::string sID     = j_Character["id"];
        CCharacter* character = new CCharacter(sName, sID);

        mapCharacters->insert(std::pair<std::string, CCharacter*>(sID, character));
    }

    return mapCharacters;
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


        //Create all doors and store in map of doors
        std::vector<nlohmann::json> j_listDoors = j_room["exits"];
        std::map<size_t, CDoor*>* mapDoors = doorFactory(j_listDoors);

        //Create all people and store in map of people
        std::vector<nlohmann::json> j_listCharacters= j_room["characters"];
        std::map<std::string, CCharacter*>* mapCharacters= characterFactory(j_listCharacters);
    
        //Create room
        CRoom* room = new CRoom(j_room["name"], mapDoors, mapCharacters);

        //Add room to map of all rooms
        mapRooms->insert(std::pair<std::string, CRoom*>(j_room["id"], room));

        std::cout << j_room["name"] << " parsed successfully! \n";
    }

    return mapRooms;
}

void CGame::dialogFactory(std::string sPath)
{
    std::ifstream read(sPath);
    
    if(!read)
    {
        std::cout << "Opening " << sPath << "failed. \n";
        return;
    }

    //Load data into json
    nlohmann::json j_dialog;
    read >> j_dialog;
    read.close();

    //Create vector with all states of dialog.
    std::vector<nlohmann::json> v_states = j_dialog;
    
    //Create map
    std::map<size_t, nlohmann::json> mapStates;
    for(size_t it=0; it<v_states; it++)
    {
        nlohmann::json fooState = v_states[it];
        mapStates.insert(std::pair<size_t, nlohmann::json>(fooState["id"], fooState));
    }

    size_t wahl = 0;
    size_t index = 0;
    for(;;)
    {
        nlohmann::json j_state = mapStates.at(index);

        std::cout << j_state["speaker"] << "  " << j_state["text"] << "\n";
        if(j_state["option"] == 1)
        {
            std::vector<size_t> v_stateOptions = j_state["link"];
            for(size_t it=0; it<v_stateOptions.size(); it++)
            {
                nlohmann::json j_fooState = v_states[v_stateOptions[it]];
                std::cout << it+1 << ": " << j_fooState["text"] << "\n";
            }
            std::cout << ">"; cin>>wahl; 

            if(wahl<v_stateOptions.size())
                index = v_stateOptions[wahl];
            else
                std::cout << "Wrong input!\n";
        }
        
        else
            index = j_state["link"];
    }
}
            
         
    
        

    

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


/**  doorFactory
* Function parsing doors of a room from json
* @parameter nlohmann::json     (json from which to create map of door 
* @return map<size_t, CDoor*>   (map of parsed doors) 
*/
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

        std::string sHeadDesc = j_door.value("headDescription", "");
        std::string sFootDesc = j_door.value("footDescription", "");
        std::string sAltDesc  = j_door.value("altDescription", "");
        
        CDoor* door = new CDoor(sName, sToRoom, sHeadDesc, sFootDesc, sAltDesc);

        mapDoors->insert(std::pair<size_t, CDoor*>(it, door)); 
    }

    return mapDoors;
}

/**  characterFactory
* Function parsing characters of a room from json
* @parameter nlohmann::json     (json from which to create map of characters 
* @return map<size_t, CCharacter*>   (map of parsed characters) 
*/
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
        CDialog* dialog     = dialogFactory(j_Character.value("dialog", "factory/defaultDialog.json"));

        CCharacter* character = new CCharacter(sName, sID, dialog);

        mapCharacters->insert(std::pair<std::string, CCharacter*>(sID, character));
    }

    return mapCharacters;
}

/** roomFactory
* Function parsing all rooms (including door, characters etc. in this room) from a json
* @parameter nlohmann::json     (json from which to create map of rooms 
* @return map<size_t, CRoom*>   (map of parsed rooms) 
*/
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
        CRoom* room = new CRoom(j_room["name"], j_room["description"], mapDoors, mapCharacters);

        //Add room to map of all rooms
        mapRooms->insert(std::pair<std::string, CRoom*>(j_room["id"], room));

        std::cout << j_room["name"] << " parsed successfully! \n";
    }

    return mapRooms;
}

/** dialogFactory
* Function parsing a dialog of a character (called in "characterFactory")
* @parameter string             (path to json from which to create dialog)
* @return CDialog* (map of parsed rooms) 
*/
CDialog* CGame::dialogFactory(std::string sPath)
{
    std::ifstream read(sPath);
    
    if(!read)
    {
        std::cout << "Opening " << sPath << "failed. \n";
        return NULL;
    }

    //Load data into json
    nlohmann::json j_dialog;
    read >> j_dialog;
    read.close();

    //Create vector with all states of dialog.
    std::vector<nlohmann::json> v_states = j_dialog;
    
    //Create map of states
    std::map<std::string, CState*>* mapStates = new std::map<std::string, CState*>; 
    for(size_t it=0; it<v_states.size(); it++)
    {
        //Create json of current state
        nlohmann::json j_state = v_states[it];

        //Create map of option states
        std::vector<nlohmann::json> v_optStates = j_state["playerOptions"];
        std::map<size_t, COptionState*>* mapOptStates = new std::map<size_t, COptionState*>;
        for(size_t yt=0; yt<v_optStates.size(); yt++)
        {
            //Create json of current option state
            nlohmann::json j_optState = v_optStates[yt];

            //Create option state
            COptionState* optState = new COptionState(j_optState["keyWord"], j_optState["text"], j_optState["targetState"]);
            //Insert option state into map of option states
            mapOptStates->insert(std::pair<size_t, COptionState*>(j_optState["keyWord"], optState));
        }

        //Create state
        CState* state = new CState(j_state["id"], j_state["text"], j_state["speaker"], 
                            j_state.value("dialogEnd", ""), mapOptStates, j_state["end"]);
        //Add state to list of states
        mapStates->insert(std::pair<std::string, CState*>(j_state["id"], state));
    }

    //Create dialog
    CDialog* dialog = new CDialog(mapStates);

    //Return dialog
    return dialog;
}
            
         
    
        

    

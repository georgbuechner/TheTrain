/** 
* wordfactory
* Create all rooms, doors, characters, dialogs and quests
* Here everything is created by parsing jsons
*/ 

#include "CGame.hpp"


// *** Factorys *** // (Factorys create objects, like characters, rooms, exits and further more)

/**
* worldFactory: calls als other factorys and initializes player. Thus creates the hole game world.
*/
void CGame::worldFactory()
{
    //***** Create Eventmanagers ****** //
    m_EM = new CEventmanager(this);
    CEventmanager::initializeManagers(this);

    //***** Create quests *****//
    m_mapQuests = questFactory("factory/quests.json");

    //***** Create Rooms *****//
    m_mapAllRooms = roomFactory("factory/rooms.json");

    std::cout << "Parsing complete! \n\n";

    //***** Create Player *****//
    m_Player.setName("Nikolaija");
    m_Player.setCurRoom(m_mapAllRooms.at("abteil_c"));
}

/**
* roomFactory: Creates all rooms out of a json (single file)  and calls, the other Factory 
* for each object in a room. This might be changes later, that one room is one json then 
* roomFactory would still create all rooms but load different json-files. Another option is
* to add a level "Area". In this case roomFactory would only create all rooms in a area. An
* "areaFactory" would be needed areafactory <-> roomFactory corresponds like roomFactory <->
* characterFactory.
* @parameter string (path to the json file with all rooms)
* @return map<string, CRoom*> (map with all rooms in the game)
*/
std::map<std::string, CRoom*> CGame::roomFactory(std::string sPath)
{
    //Read json creating all rooms
    std::ifstream read(sPath);

    //Create empty map of rooms
    std::map<std::string, CRoom*> mapRooms;

    //Check wether json could be opened
    if(!read)
    {
        std::cout << "Error reading " << sPath << ".\n";
        return mapRooms;
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


        //Create all exits and store in map of exits 
        std::vector<nlohmann::json> j_listExits= j_room["exits"];
        std::map<size_t, CExit*> mapExits = exitFactory(j_listExits);

        //Create all people and store in map of people
        std::vector<nlohmann::json> j_listCharacters= j_room["characters"];
        std::map<std::string, CCharacter*> mapCharacters = characterFactory(j_listCharacters);
    
        //Create room
        CRoom* room = new CRoom(j_room["name"], j_room["description"], mapExits, mapCharacters);

        //Add room to map of all rooms
        mapRooms.insert(std::pair<std::string, CRoom*>(j_room["id"], room));

        std::cout << j_room["name"] << " parsed successfully! \n";
    }

    return mapRooms;
}
/**
* exitFactory: gets called by roomFactory. Creates all exits from a room.
* @parameter nlohmann::json (a json with a list of json-objects (each object is one exit)
* @return map<size_t, CExit*> (map of all exits created)
*/
std::map<size_t, CExit*> CGame::exitFactory(nlohmann::json j_listExits)
{
    //Create empty map of exits 
    std::map<size_t, CExit*> mapExits;

    //Iterate over all exits and create each exit 
    for(size_t it = 0; it < j_listExits.size(); it++)
    {
        //Create a new json for current room
        nlohmann::json j_exit=j_listExits[it];

        // ** Create exit ** //

        //Parse attributes
        std::string sName   = j_exit["name"];
        std::string sID     = j_exit["id"];
        std::string sToRoom = j_exit["to"];
        std::vector<std::string> vTake = j_exit["take"];
        std::string sHeadDesc = j_exit.value("headDescription", "");
        std::string sFootDesc = j_exit.value("footDescription", "");
        std::string sAltDesc  = j_exit.value("altDescription", "");
        
        //Create exit
        CExit* exit = new CExit(sName, sID, sToRoom, vTake, sHeadDesc, sFootDesc, sAltDesc);

        //Insert exit into dictionary of exits in a room
        mapExits.insert(std::pair<size_t, CExit*>(it, exit)); 
    }

    return mapExits;
}

/**
* characterFactory: gets called by roomFactory. Creates all characters in a room.
* @parameter nlohmann::json (a json with a list of json-objects (each object is one character)
* @return map<string, CCharacter*> (map of all characters created)
*/
std::map<std::string, CCharacter*> CGame::characterFactory(nlohmann::json j_listCharacters)
{
    //Create empty map of exits 
    std::map<std::string, CCharacter*> mapCharacters;

    //Iterate over all exits and create each person
    for(size_t it = 0; it<j_listCharacters.size(); it++)
    {
        //Create a new json for current person
        nlohmann::json j_Character= j_listCharacters[it];

        // ** Create person ** //

        //Parse attributes
        std::string sName   = j_Character["name"];
        std::string sID     = j_Character["id"];
        std::vector<std::string> vTake = j_Character["take"];
        std::string sPath   = "factory/Dialogs/" + j_Character.value("dialog", "defaultDialog.json");
        CDialog* dialog     = dialogFactory(sPath);

        //Create character
        CCharacter* character = new CCharacter(sName, sID, vTake, dialog);

        //Insert character into dictionary of characters in a room
        mapCharacters.insert(std::pair<std::string, CCharacter*>(sID, character));
    }

    return mapCharacters;
}

/**
* dialoGFactory: gets called by characterFactory. Parses a given dialog (.json-file) into 
* an object of CDialog. Each dialog is owned by a character.
* @parameter string (Path to the json)
* @return CDialog* (Parsed dialog)
*/
CDialog* CGame::dialogFactory(std::string sPath)
{
    //Load path to json with dialog
    std::ifstream read(sPath);
    
    //Check whether json could be opend
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
    std::map<std::string, CDialogState*> mapStates;
    for(size_t it=0; it<v_states.size(); it++)
    {
        //Create json of current state
        nlohmann::json j_state = v_states[it];

        //Create map of option states
        std::vector<nlohmann::json> v_optStates = j_state["playerOptions"];
        std::map<size_t, CDialogOptionState*> mapOptStates;
        for(size_t yt=0; yt<v_optStates.size(); yt++)
        {
            //Create json of current option state
            nlohmann::json j_optState = v_optStates[yt];

            //Create option state
            CDialogOptionState* optState = new CDialogOptionState(j_optState["keyWord"], 
                                                    j_optState["text"], j_optState["targetState"]);
            //Insert option state into map of option states
            mapOptStates.insert(std::pair<size_t, CDialogOptionState*>(j_optState["keyWord"], 
                                                                                        optState));
        }

        //Create state
        CDialogState* state = new CDialogState(j_state["id"], j_state["text"], j_state["speaker"], 
                            j_state.value("dialogEnd", ""), mapOptStates, j_state["end"]);
        //Add state to list of states
        mapStates.insert(std::pair<std::string, CDialogState*>(j_state["id"], state));
    }

    //Create dialog
    CDialog* dialog = new CDialog(mapStates, sPath);

    //Return dialog
    return dialog;
}
 

/**
* questFactory: creates all quests in game.
*/
std::map<std::string, CQuest*> CGame::questFactory(std::string sPath)
{
    //Initialize function pointers
    CQuestStep::initializeFunctions();

    //Create map of quests
    std::map<std::string, CQuest*> mapQuests;

    //Read json with all quests
    std::ifstream read(sPath);
    
    //Check whether json could be loaded
    if(!read)
    {
        std::cout << "Path to quest-json not found.\n";
        return mapQuests;
    }

    //Create json with all quests
    nlohmann::json j_listQuests;
    read >> j_listQuests;
    read.close();
    
    //Create a vector of all json objects (all quests)
    std::vector<nlohmann::json> v_Quests = j_listQuests;
      
    //Iterate over all quests and create each quest.
    for(size_t it = 0; it < v_Quests.size(); it++)
    {
        //Create a new json for the current quest.
        nlohmann::json j_quest = v_Quests[it];
        
        //Parse attributes
        std::string sID = j_quest["id"];
        std::string sName = j_quest["name"];
        std::string sDescription = j_quest["description"];
        std::map<std::string, CQuestStep*> questSteps = questStepFactory(j_quest["steps"]);
    
        //Create quest
        CQuest* quest = new CQuest(sID, sName, sDescription, questSteps);

        //Add quest to map of alle quests
        mapQuests.insert(std::pair<std::string, CQuest*> (sID, quest));

        //Add eventmanager to list of eventmanagers
        if(m_EM->getManagers().count(sID) != 0)
            m_eventmanagers.push_back(m_EM->getManagers().at(sID));

    }

    return mapQuests;
} 

/**
* questStepFactory: create all steps of a quest.
* @parameter vector<nlohmann::json> (vecor with all steps of a quest)
* @return list<CQuestStep*> (list with all quest-steps)
*/
std::map<std::string, CQuestStep*> CGame::questStepFactory(std::vector<nlohmann::json> v_steps)
{
    //Create list of quest-steps
    std::map<std::string, CQuestStep*> mapSteps;
    
    //Iterate over all quest-steps and create each step.
    for(size_t it=0; it<v_steps.size(); it++)
    {
        //Create new json for the current step
        nlohmann::json j_step = v_steps[it];
        std::string sID   = j_step["id"];
        std::string sName = j_step["name"];
        std::string sDesc = j_step["description"];
        bool achieved     = j_step["achieved"];
        bool active       = j_step["active"];
        std::string sFunc = j_step.value("funcID", "standard");

        //Create step
        CQuestStep* step = new CQuestStep(sID, sName, sDesc, achieved, active, sFunc);

        //Add step to list of steps
        mapSteps.insert(std::pair<std::string, CQuestStep*>(sID, step));
    }

    return mapSteps;
} 


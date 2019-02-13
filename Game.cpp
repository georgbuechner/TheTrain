// *** CGame *** //

#include "CGame.hpp"

/**
* play: function with main loop. Also creates all eventhandlers
*/
void CGame::play()
{

    //Call word factory create all rooms, characters... 
    worldFactory();

    std::cout << "Map quests size: " << m_mapQuests.size() << "\n";

    //Create command parser 
    CCommandParser parser;

    //Create event manager and basic eventhandlers
    m_EM = new CEventmanager(this);

    //Create event handlers 
    CEventhandler* h_exits  = new CEventhandler("basic_showExits", &CEventhandler::echo_showExits);
    CEventhandler* h_change = new CEventhandler("basic_changeRoom", &CEventhandler::echo_changeRoom);
    CEventhandler* h_chars  = new CEventhandler("basic_showChars", &CEventhandler::echo_showChars);
    CEventhandler* h_talk   = new CEventhandler("basic_talkTo", &CEventhandler::echo_talkTo);
    CEventhandler* h_showActive = new CEventhandler("basic_showActive", &CEventhandler::echo_showActiveQuests);
    CEventhandler* h_showSolved = new CEventhandler("basic_showSolved", &CEventhandler::echo_showSolvedQuests);
    CEventhandler* h_endGame= new CEventhandler("basic_end", &CEventhandler::echo_endGame);
    CEventhandler* h_falseInput = new CEventhandler("basic_falseInput", &CEventhandler::echo_falseInput);
    CEventhandler* h_foo = new CEventhandler("foo", &CEventhandler::echo_foo);

    //Add listeners to eventmanager
    m_EM->add_listener("showExits", h_exits);
    m_EM->add_listener("changeRoom", h_change);
    m_EM->add_listener("showChars", h_chars);
    m_EM->add_listener("talkTo", h_talk);
    m_EM->add_listener("showActiveQuests", h_showActive);
    m_EM->add_listener("showSolvedQuests", h_showSolved);
    m_EM->add_listener("endGame", h_endGame);
    m_EM->add_listener("falseInput", h_falseInput);


    //Print player name and current room of player
    std::cout << m_Player.getName() << " befindet sich in " << m_Player.getCurRoom()->getName() << ".\n";

    //Main loop: here player can talk to characters, change room and so on
    std::string sInput;
    do
    {
        //Get player command
        std::cout << "> ";
        getline(cin, sInput);
         

        //Parse command into event
        CEvent* event = parser.parseCommand(sInput); 
        
        //Pass pointer to current context (CGame) to event
        event->setGame(this);

        //Throw event
        m_EM->throw_event(event);

        //Delete event
        delete event;

    }while(m_gameEnd == false);

}


// *** Factorys *** // (Factorys create objects, like characters, rooms, exits and further more)

/**
* worldFactory: calls als other factorys and initializes player. Thus creates the hole game world.
*/
void CGame::worldFactory()
{
    //***** Create Eventmanagers ****** //

    //Create eventmanagers from all dialogs
    m_dialogEvents = emDialogsFactory();

    
    //***** Create quests *****//
    m_mapQuests = questFactory();

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
        CDialog* dialog     = dialogFactory(j_Character.value("dialog", "factory/defaultDialog.json"));

        //Create character
        CCharacter* character = new CCharacter(sName, sID, vTake, dialog);

        //Insert character into dictionary of characters in a room
        mapCharacters.insert(std::pair<std::string, CCharacter*>(sID, character));
    }

    return mapCharacters;
}

/** 
* emDialogsFactory: create all dialog eventmanagers.
*/
std::map<std::string, CEventmanager*> CGame::emDialogsFactory()
{
    //Create map of eventmanagers
    std::map<std::string, CEventmanager*> mapEMs; 

    // *** factory/parsenDialog.json *** //
    CEventmanager* eventmanager = new CEventmanager(this);
    CEventhandler* h_anna = new CEventhandler("quest_jay", &CEventhandler::echo_parsenDialogAnna);
    eventmanager->add_listener("anna", h_anna);
    mapEMs.insert(std::pair<std::string, CEventmanager*> 
                                        ("factory/parsenDialog.json", eventmanager));

    return mapEMs;
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

    //Create dialog eventmanager if exists
    CEventmanager* em = new CEventmanager(this);
    if(m_dialogEvents.count(sPath) > 0)
        em = m_dialogEvents.at(sPath);

    //Create dialog
    CDialog* dialog = new CDialog(mapStates, em);

    //Return dialog
    return dialog;
}
 

/**
* questFactory: creates all quests in game.
*/
std::map<std::string, CQuest*> CGame::questFactory()
{
    //Create map of quests
    std::map<std::string, CQuest*> mapQuests;

    //Quest: Talk to Jay
    CQuest* quest = new CQuest("talk_to_jay", "Talk to Jay", "Parsen told you to talk to Jay.");

    //Create steps
    CQuestStep* questStep1 = new CQuestStep("Find Jay", "Find Jay and talk to her.", 0);
    quest->addStep(questStep1);

    //Add quest to map of alle quests
    mapQuests.insert(std::pair<std::string, CQuest*> ("talk_to_jay", quest));

    return mapQuests;
} 


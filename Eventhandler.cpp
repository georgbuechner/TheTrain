// *** handlers *** //

#include "CEventhandler.hpp"

/**
* handler_showExits: show all exits in a room.
* Eventtype: "showExits"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_showExits(CEvent* event)
{
    //Attributes
    size_t counter = 1;

    
    //Iterate over map of exits in room and print name. Add a number infront of exit
    std::cout << "Exits: \n";
    std::map<size_t, CExit*> mapExits = event->getGame()->getPlayer().getCurRoom()->getMapExits();
    for(auto it=mapExits.begin(); it!=mapExits.end(); it++)
    {
        std::cout << counter << ": " << it->second->getName() << ".\n";
        counter++;
    }

    std::cout << "\n";
}

/**
* handler_changeRoom: change room to selected room.
* Eventtype: "changeRoom"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_changeRoom(CEvent* event)
{
    //Get map of exits in current room
    std::map<size_t, CExit*> mapExits= event->getGame()->getPlayer().getCurRoom()->getMapExits();

    //Iterate over exits and find selected exit, print descriptions and change players room
    for(auto it=mapExits.begin(); it!=mapExits.end(); it++)
    {
        //Get vector with all accepted words
        std::vector<std::string> vTakes = it->second->getTake();

        //Iterate over all accepted words and check if they match with identifier.
        for(size_t yt = 0; yt < vTakes.size(); yt++)
        {
            //Check whether exit is selected exit (use strcmp and const char*)
            if(strcmp(event->getIdentifier().c_str(), vTakes[yt].c_str()) == 0)
            {
                //get linked room and change players room
                CRoom* room = event->getGame()->getMapRooms().at(it->second->getLinkedRoom());
                event->getGame()->getPlayer().setCurRoom(room);
            
                // ** Print descriptions ** //

                //Check whether exit has an alternative description
                if(it->second->getAltDesc().length() > 0)
                    std::cout << it->second->getAltDesc() << "\n";

                //Print secriptions in normal order
                else 
                {
                    std::cout << it->second->getHeadDesc(); //Header description
                    std::cout << room->getDescription();    //Room description
                    std::cout << it->second->getFootDesc(); //Footer description
                    std::cout << "\n";
                }

                return;
            }
        } 
    }

    //Error message in case exit could not be found
    std::cout << "Wrong Input! Exit " << event->getIdentifier() 
                                                << " does not exist. Please try again.\n\n";
}

/**
* handler_showPeople: print all people in current room
* Eventtype: "showChars"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_showChars(CEvent* event)
{
    //Attributes
    size_t counter = 0;
            
    //Iterate over map of characters in room and print name. Add a number infront of each character 
    std::cout << "People in the room: \n";
    std::map<std::string, CCharacter*> mapChars = event->getGame()->getPlayer().getCurRoom()
                                                                                    ->getMapChars();
    for(auto it=mapChars.begin(); it!=mapChars.end(); it++)
    {
        counter++;
        std::cout << counter << ": " << it->second->getName() << ".\n";
    }

    std::cout << "\n";
}
   

/**
* handler_talkTo: call dialog of selected character
* Eventtype: "talkTo"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_talkTo(CEvent* event)
{
    //Get map of characters in room
    std::map<std::string, CCharacter*> mapChars = event->getGame()->getPlayer().getCurRoom()
                                                                                    ->getMapChars();

    //Iterate over map of characters and call dialog
    for(auto it=mapChars.begin(); it!=mapChars.end(); it++)
    {
        
        //Get array of all accepted words.
        std::vector<std::string> vTake = it->second->getTake();

        //Iterate over accepted words and check whether they match with identifier.
        for(size_t yt = 0; yt < vTake.size(); yt++)
        {
            //Check whether current player is selected player (use strcmp and const char*)
            if(strcmp(event->getIdentifier().c_str(), vTake[yt].c_str()) == 0) 
            {
                //Call dialog of selected character
                it->second->getDialog()->startDialog();
                return;
            }
        }
    }
    
    std::cout << "Character not found.\n";
}

/**
* handler_showActiveQuests: show all active quests.
* EventType: "showActiveQuests"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_showActiveQuests(CEvent* event)
{
    size_t counter = 1;

    //Get list of players quests
    std::list<CQuest*> listQuests = event->getGame()->getPlayer().getQuests();

    //Print all active quests
    std::cout << "Aktive Quests: (Anzahl Quests: " << listQuests.size() << ") \n";
    for(auto it=listQuests.begin(); it!=listQuests.end(); it++)
    {
        if((*it)->getAchieved() == false)
            std::cout << counter << ": " << (*it)->getName() << "\n";
    }


    //Select quest for further information
    std::cout << "Wähle Quest (Nummer): ";

    //Player input and convert string to int
    std::string sChoose;
    size_t choose;
    getline(cin, sChoose);
    choose = std::stoi(sChoose);

    //check whether input is correct
    if(choose < 1 || choose > counter)
    {
        std::cout << "Falsche EIngabe!\n";
        return;
    }

    //Print quest information
    counter = 1;
    auto it = listQuests.begin();
    advance(it, counter-1);
    (*it)->printQuest();
}

/**
* handler_showSolvedQuests: show all solved quests.
* EventType: "showSolvedQuests"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_showSolvedQuests(CEvent* event)
{
    //Get list of players quests
    std::list<CQuest*> listQuests = event->getGame()->getPlayer().getQuests();

    //Print all active quests
    size_t counter = 1;
    std::cout << "Gelöste Quests: \n";
    for(auto it=listQuests.begin(); it!=listQuests.end(); it++)
    {
        if((*it)->getAchieved() == true)
            std::cout << counter << ": " << (*it)->getName() << "\n";
    }

    //Select quest for further information
    std::cout << "Wähle Quest (Nummer): ";

    //Player input and convert string to int
    std::string sChoose;
    size_t choose;
    getline(cin, sChoose);
    choose = std::stoi(sChoose);

    //check whether input is correct
    if(choose < 1 || choose > counter)
    {
        std::cout << "Falsche EIngabe!\n";
        return;
    }

    //Print quest information
    counter = 1;
    auto it = listQuests.begin();
    advance(it, counter-1);
    (*it)->printQuest();
}


/**
* handler_endGame: Print message for end of game (this might better be moved into CGame::play() )
* and set CGame::m_gameEnd to true (this causes main loop in CGame::play() function to break)
* Eventtype: "endGame"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_endGame(CEvent* event)
{
    std::cout << "Willst du wirklich das Spiel verlassen?\n";
    std::cout << "> ";
    
    std::string sInput;
    getline(cin, sInput);
    std::regex ja("(j|((J|j)a))");
    if(regex_match(sInput, ja))
    { 
        std::cout << "Thank you for playing!\n";

        //set CGame::m_gameEnd to true 
        event->getGame()->setEndGame(true);
    }

    else
        std::cout << "Dann noch viel Spaß!\n\n";
}

/**
* handler_endGameDirectly: End game without asking
* Eventtype: "endGameDirectly"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_endGameDirectly(CEvent* event)
{
    std::cout << "Thank you for playing!\n";

    //set CGame::m_gameEnd to true 
    event->getGame()->setEndGame(true);
}


/**
* handler_falseInput: print error message
* Eventtype: "falseInput"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_falseInput(CEvent* event)
{
    //Print error message
    std::cout << "Eventtype: \"" << event->getEventType() << "\" called. Please retry!\n";
}



// **** **** dialog handlers **** **** //


// **** factory/parsenDialog.json **** //
void CEventhandler::echo_parsenDialogAnna(CEvent* event)
{
    if(event->getGame()->getQuests().count("talk_to_jay") == 0)
    {
        std::cout << "Quest not found.\n";
        return;
    }

    CQuest* quest = event->getGame()->getQuests().at("talk_to_jay");

    std::cout << "Quest \"" << quest->getName() << "\" angenommen.\n";

    //Add quests tp players list of quests
    event->getGame()->getPlayer().getQuests().push_back(quest);
}


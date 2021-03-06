// *** handlers *** //

#include "CEventhandler.hpp"

/**
* handler_showExits: show all exits in a room.
* Eventtype: "showExits"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_showExits(CEvent* event)
{
    /*
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
    */
}

/**
* handler_changeRoom: change room to selected room.
* Eventtype: "changeRoom"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_changeRoom(CEvent* event)
{
    /*
    CFunctions function;

    //Get map of exits in current room
    std::map<size_t, CExit*> mapExits= event->getGame()->getPlayer().getCurRoom()->getMapExits();

    //Iterate over exits and find selected exit, print descriptions and change players room
    for(auto it=mapExits.begin(); it!=mapExits.end(); it++)
    {
        if(function.in(event->getIdentifier(), it->second->getTake()) == true)
        {
            //Call exits custim function
            it->second->callExitFunction();

            //get linked room and change players room
            CRoom* room = event->getGame()->getMapRooms().at(it->second->getLinkedRoom());
            event->getGame()->getPlayer().setCurRoom(room);
        
            // ** Print descriptions ** //
            room->printDescription(it->second);

            return;
        }
    }

    //Error message in case exit could not be found
    std::cout << "Wrong Input! Exit " << event->getIdentifier() 
                                                << " does not exist. Please try again.\n\n";
    */
}

/**
* handler_showPeople: print all people in current room
* Eventtype: "showChars"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_showChars(CEvent* event)
{
    /*
    //Attributes
    size_t counter = 0;
            
    //Iterate over map of characters in room and print name. Add a number infront of each character 
    std::cout << "People in the room: \n";
    std::map<std::string, std::string> mapChars = event->getGame()->getPlayer().getCurRoom()
                                                                                    ->getMapChars();
    for(auto it=mapChars.begin(); it!=mapChars.end(); it++)
    {
        counter++;
        std::cout << counter << ": " << it->second << ".\n";
    }

    std::cout << "\n";
    */
}
   

/**
* handler_talkTo: call dialog of selected character
* Eventtype: "talkTo"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_talkTo(CEvent* event)
{
    /*
    //Get Game
    CGame* game = event->getGame();

    //Get map of characters in room
    std::map<std::string, std::string> mapChars = game->getPlayer().getCurRoom()->getMapChars();

    //Iterate over map of characters and call dialog
    for(auto it=mapChars.begin(); it!=mapChars.end(); it++)
    {
        //Get array of all accepted words.
        std::vector<std::string> vTake = game->getMapChars().at(it->first)->getTake();

        //Iterate over accepted words and check whether they match with identifier.
        for(size_t yt = 0; yt < vTake.size(); yt++)
        {
            //Check whether current player is selected player (use strcmp and const char*)
            if(strcmp(event->getIdentifier().c_str(), vTake[yt].c_str()) == 0) 
            {
                //Call dialog of selected character
                game->getMapChars().at(it->first)->getDialog()->startDialog(game->getPlayer());
                return;
            }
        }
    }
    
    std::cout << "Character not found.\n";
    */
}

/**
* handler_showActiveQuests: show all active quests.
* EventType: "showActiveQuests"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_showActiveQuests(CEvent* event)
{
    /*
    size_t counter = 1;

    //Get list of players quests
    std::list<CQuest*> listQuests = event->getGame()->getPlayer().getQuests();

    //Print all active quests
    std::cout << "\nAktive Quests: (Anzahl Quests: " << listQuests.size() << ") \n";
    for(auto it=listQuests.begin(); it!=listQuests.end(); it++)
    {
        if((*it)->getAchieved() == false)
            std::cout << counter << ": " << (*it)->getName() << "\n";
        counter++;
    }

    //Return if there are no active quests
    if(counter == 1)
        return;

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
    auto it = listQuests.begin();
    advance(it, choose-1);
    (*it)->printQuest();
    */
}

/**
* handler_showSolvedQuests: show all solved quests.
* EventType: "showSolvedQuests"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_showSolvedQuests(CEvent* event)
{
    /*
    //Get list of players quests
    std::list<CQuest*> listQuests = event->getGame()->getPlayer().getQuests();

    //Print all active quests
    size_t counter = 1;
    std::cout << "Gelöste Quests: \n";
    for(auto it=listQuests.begin(); it!=listQuests.end(); it++)
    {
        if((*it)->getAchieved() == true)
            std::cout << counter << ": " << (*it)->getName() << "\n";
        counter++;
    }


    //Return if there are no active quests
    if(counter == 1)
        return;

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
    auto it = listQuests.begin();
    advance(it, choose-1);
    (*it)->printQuest();
    */
}


/**
* handler_endGame: Print message for end of game (this might better be moved into CGame::play() )
* and set CGame::m_gameEnd to true (this causes main loop in CGame::play() function to break)
* Eventtype: "endGame"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_endGame(CEvent* event)
{
    /*
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
    */
}

/**
* handler_endGameDirectly: End game without asking
* Eventtype: "endGameDirectly"
* @parameter CEvent* (pointer to event thrown)
*/
void CEventhandler::echo_endGameDirectly(CEvent* event)
{
    /*
    std::cout << "Thank you for playing!\n";

    //set CGame::m_gameEnd to true 
    event->getGame()->setEndGame(true);
    */
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
    /*
    CGame* game = event->getGame();

    //Add quests to players list of quests
    std::cout << "Quest \"" << game->getQuests().at("talk_to_jay")->getName() << "\" angenommen.\n";
    game->getPlayer().getQuests().push_back(game->getQuests().at("talk_to_jay"));

    //Change dialog of Jay.
    game->getMapChars().at("jay")->setDialog(game->dialogFactory("factory/Dialogs/jayDialog.json"));
    */
}

    


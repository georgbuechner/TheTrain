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
* handler_falseInput: print error message
* Eventtype: "falseInput"
* @parameter CEvent* (Pointer to event thrown)
*/
void CEventhandler::echo_falseInput(CEvent* event)
{
    //Print error message
    std::cout << "Eventtype: \"" << event->getEventType() << "\" called. Please retry!\n";
}


/**
* handler_foo
*/
void CEventhandler::echo_foo(CEvent* event)
{
    std::cout << event->getEventType() << " hahaha, I'm a foo\n";
}




// **** **** dialog handlers **** **** //


// **** factory/parsenDialog.json **** //
void CEventhandler::echo_parsenDialogAnna(CEvent* event)
{
    std::cout << "Quest: Bringe Jay das Packet wurde angenommen! \n";
    
}


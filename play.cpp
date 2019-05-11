// *** CGame *** //

#include "CGame.hpp"

/**
* play: function with main loop. Also creates all eventhandlers
*/
void CGame::play()
{

    //Call word factory create all rooms, characters... 
    worldFactory();

    //Create command parser 
    CCommandParser parser;

    //Create event manager and basic eventhandlers

    //Create event handlers 
    CEventhandler* h_exits  = new CEventhandler("basic_showExits", &CEventhandler::echo_showExits);
    CEventhandler* h_change = new CEventhandler("basic_changeRoom", &CEventhandler::echo_changeRoom);
    CEventhandler* h_chars  = new CEventhandler("basic_showChars", &CEventhandler::echo_showChars);
    CEventhandler* h_talk   = new CEventhandler("basic_talkTo", &CEventhandler::echo_talkTo);
    CEventhandler* h_showActive = new CEventhandler("basic_showActive", &CEventhandler::echo_showActiveQuests);
    CEventhandler* h_showSolved = new CEventhandler("basic_showSolved", &CEventhandler::echo_showSolvedQuests);
    CEventhandler* h_endGame= new CEventhandler("basic_end", &CEventhandler::echo_endGame);
    CEventhandler* h_endGameDirectly= new CEventhandler("basic_endDirectly", &CEventhandler::echo_endGameDirectly);
    CEventhandler* h_falseInput = new CEventhandler("basic_falseInput", &CEventhandler::echo_falseInput);

    //Add listeners to eventmanager
    m_EM->add_listener("showExits", h_exits);
    //m_EM->add_listener("changeRoom", h_change);
    m_EM->add_listener("showChars", h_chars);
    m_EM->add_listener("talkTo", h_talk);
    m_EM->add_listener("showActiveQuests", h_showActive);
    m_EM->add_listener("showSolvedQuests", h_showSolved);
    m_EM->add_listener("endGame", h_endGame);
    m_EM->add_listener("endGameDirectly", h_endGameDirectly);
    m_EM->add_listener("falseInput", h_falseInput);

    m_Player.getEventmanagers()["functions"] = m_EM;


    //Print player name and current room of player
    std::cout << m_Player.getName() << " befindet sich in " << m_Player.getCurRoom()->getName() << ".\n";

    CEventManager eventmanager;
    using namespace std::placeholders; 
    eventmanager.add_listener("showExits", bind(&CPlayer::showExits, &m_Player, _1));
    eventmanager.add_listener("changeRoom", bind(&CPlayer::changeRoom, &m_Player, m_mapAllRooms, _1));
    eventmanager.add_listener("showChars", bind(&CPlayer::showChars, &m_Player, _1));
    eventmanager.add_listener("talkTo", bind(&CPlayer::talkTo, &m_Player, m_mapAllChars, _1));
    eventmanager.add_listener("showQuests", bind(&CPlayer::showQuests, &m_Player, _1));
    eventmanager.add_listener("endGame", bind(&CGame::endGame, this, _1));
    eventmanager.add_listener("endGameDirectly", bind(&CGame::endGameDirectly, this, _1));

    //Main loop: here player can talk to characters, change room and so on
    std::string sInput;
    do
    {
        //Get player command
        std::cout << "> ";
        getline(cin, sInput);
         

        //Parse command into event
        CEvent* event = parser.parseCommand(sInput); 

        eventmanager.throw_event(event->getEventType(), event->getIdentifier());
        
        //Throw event
        for(auto it=m_Player.getEventmanagers().begin(); it!=m_Player.getEventmanagers().end(); it++)
            it->second->throw_event(event);

        //Delete event
        delete event;

    }while(m_gameEnd == false);

    std::cout << "Thank you for playing!\n";
}


/**
* handler: endGame: Print message for end of game (this might better be moved into CGame::play() )
* and set CGame::m_gameEnd to true (this causes main loop in CGame::play() function to break)
* Eventtype: "endGame"
* @parameter string (Identifier of event thrown)
*/
void CGame::endGame(std::string sEvent)
{
    std::cout << "Willst du wirklich das Spiel verlassen?\n";
    std::cout << "> ";
    
    std::string sInput;
    getline(cin, sInput);
    std::regex ja("(j|((J|j)a))");
    if(regex_match(sInput, ja))
    { 

        m_gameEnd = true; 
    }

    else
        std::cout << "Dann noch viel Spaß!\n\n";
}

/**
* handler: endGameDirectly: End game without asking
* Eventtype: "endGameDirectly"
* @parameter CEvent* (pointer to event thrown)
*/
void CGame::endGameDirectly(std::string sEvent) {
    m_gameEnd = true;
}


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
    m_EM->add_listener("changeRoom", h_change);
    m_EM->add_listener("showChars", h_chars);
    m_EM->add_listener("talkTo", h_talk);
    m_EM->add_listener("showActiveQuests", h_showActive);
    m_EM->add_listener("showSolvedQuests", h_showSolved);
    m_EM->add_listener("endGame", h_endGame);
    m_EM->add_listener("endGameDirectly", h_endGameDirectly);
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
        
        //Throw event
        m_EM->throw_event(event);

        for(auto it=m_eventmanagers.begin(); it!=m_eventmanagers.end(); it++)
            (*it)->throw_event(event);

        //Delete event
        delete event;

    }while(m_gameEnd == false);

}



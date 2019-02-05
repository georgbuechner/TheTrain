//Play -> memberfunction of CGame.h

#include "CGame.h"

void CGame::play()
{
    //Variables

    worldFactory();

    std::cout << m_Player->getName() << " befindet sich in " << m_Player->getCurRoom()->getName()<< ".\n";

    //Create event manager
    CEventManager* em = new CEventManager;

    CEventHandler* h_doors  = new CEventHandler("basic_showDoors", &CEventHandler::echo_showDoors);
    CEventHandler* h_change = new CEventHandler("basic_changeRoom", &CEventHandler::echo_changeRoom);
    CEventHandler* h_people = new CEventHandler("basic_showPeople", &CEventHandler::echo_showPeople);
    CEventHandler* h_talk   = new CEventHandler("basic_talkTo", &CEventHandler::echo_talkTo);
    em->add_listener("showDoors", h_doors);
    em->add_listener("changeRoom", h_change);
    em->add_listener("showPeople", h_people);
    em->add_listener("talkTo", h_talk);

    CCommandParser parser;
    std::string sInput;
    int option;

    do
    {
        std::cout << "> ";
        getline(cin, sInput);
         

        option = parser.parseCommand(sInput); 
        switch(option)
        {
            //Show all doors in room
            case(1):
            {
                CEvent* event = new CEvent("showDoors", m_Player);
                em->throw_event(event);
                delete event;
            }break;

            //Change room
            case(2):
            {
                CEvent* event = new CEvent("changeRoom", m_Player, m_mapAllRooms);
                em->throw_event(event);
                delete event;
            }break;

            //Show people
            case(3):
            {
                CEvent* event = new CEvent("showPeople", m_Player);
                em->throw_event(event);
                delete event;
            }break;

            //Talk to
            case(4):
            {
                CEvent* event = new CEvent("talkTo", m_Player);
                em->throw_event(event);
                delete event;
            }break;


            //Leave game
            case(5):
            {
                std::cout << "Thanks for playing.\n\n";
            }break;

            //Wrong input
            default:
            {
                std::cout << "Wrong input! Please try again! \n\n";
            }
        }

    }while(option != 5);

}

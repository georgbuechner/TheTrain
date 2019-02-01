//Play -> memberfunction of CGame.h

#include "CGame.h"

void CGame::play()
{
    //Variables
    int wahl;

    worldFactory();

    std::cout << m_Player->getName() << " befindet sich in " << m_Player->getCurRoom()->getName()<< ".\n";


    do
    {
        std::cout << "Choose your action:   \n";
        std::cout << "1: Show doors.        \n";
        std::cout << "2: Change room.       \n";
        std::cout << "3: Show people.       \n";
        std::cout << "4: Talk to.           \n";
        std::cout << "5: Quit game.         \n";
        std::cout << "> "; cin >> wahl; 

        switch(wahl)
        {
            //Show all doors in room
            case(1):
            {
                size_t counter = 1;

                std::cout << "Doors: \n";
                std::map<size_t, CDoor*>* mapDoors = m_Player->getCurRoom()->getMapDoors();
                for(auto it=mapDoors->begin(); it!=mapDoors->end(); it++)
                {
                    std::cout << counter << ": " << it->second->getName() << ".\n";
                    counter++;
                }
                std::cout << "\n";
            }break;

            //Change room
            case(2):
            {
                size_t counter = 0;
                size_t wahl;

                std::cout << "Doors: \n";
                std::map<size_t, CDoor*>* mapDoors = m_Player->getCurRoom()->getMapDoors();
                for(auto it=mapDoors->begin(); it!=mapDoors->end(); it++)
                {
                    counter++;
                    std::cout << counter << ": " << it->second->getName() << ".\n";
                }
                std::cout << "> "; cin >> wahl;

                if(wahl <= counter)
                {
                    CDoor* door = mapDoors->at(wahl-1);
                    CRoom* room = m_mapAllRooms->at(door->getLinkedRoom());
                    m_Player->setCurRoom(room);
            
                    //Print description
                    if(door->getAltDesc().length() > 0)
                        std::cout << door->getAltDesc() << "\n";
                    else 
                    {
                        std::cout << door->getHeadDesc()    << "\n";
                        std::cout << room->getDescription() << "\n";
                        std::cout << door->getFootDesc()    << "\n";
                    }
                }

                else
                    std::cout << "Wrong Input! Door does not exist. Please try again.\n\n";

            }break;

            //Show people
            case(3):
            {
                size_t counter = 0;
            
                std::cout << "People in the room: \n";
                std::map<std::string, CCharacter*>* mapChars = m_Player->getCurRoom()->getMapChars();
                for(auto it=mapChars->begin(); it!=mapChars->end(); it++)
                {
                    counter++;
                    std::cout << counter << ": " << it->second->getName() << ".\n";
                }
                std::cout << "\n";
            }break;

            //Talk to
            case(4):
            {
                size_t counter = 0;
                size_t choice;
            
                std::cout << "People in the room: \n";
                std::map<std::string, CCharacter*>* mapChars = m_Player->getCurRoom()->getMapChars();
                for(auto it=mapChars->begin(); it!=mapChars->end(); it++)
                {
                    counter++;
                    std::cout << counter << ": " << it->second->getName() << ".\n";
                }
                std::cout << ">"; cin >>choice;

                counter = 0;
                bool found = false;
                for(auto it=mapChars->begin(); it!=mapChars->end(); it++)
                {
                    counter++;
                    if(choice == counter)
                    {
                        it->second->getDialog()->startDialog();
                        found = true;
                    }
                }

                if(found == false)
                    std::cout << "Character not found.\n";

                std::cout << "\n";
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

    }while(wahl != 5);

}

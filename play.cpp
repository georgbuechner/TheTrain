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
        std::cout << "3: Quit game.         \n";
        std::cout << "> "; cin >> wahl; 

        switch(wahl)
        {
            //Show all doors in room
            case(1):
            {
                size_t counter = 1;

                std::cout << "Doors: \n";
                std::map<size_t, CDoor*>* mapDoors = m_Player->getCurRoom()->getDoors();
                for(auto it=mapDoors->begin(); it!=mapDoors->end(); it++)
                {
                    std::cout << counter << ": " << it->second->getName() << ".\n";
                    counter++;
                }
            }break;

            //Change room
            case(2):
            {
                size_t counter = 0;
                size_t wahl;

                std::cout << "Doors: \n";
                std::map<size_t, CDoor*>* mapDoors = m_Player->getCurRoom()->getDoors();
                for(auto it=mapDoors->begin(); it!=mapDoors->end(); it++)
                {
                    counter++;
                    std::cout << counter << ": " << it->second->getName() << ".\n";
                }
                std::cout << "> "; cin >> wahl;

                if(wahl <= counter)
                {
                    CDoor* door = mapDoors->at(wahl-1);
                    m_Player->setCurRoom(m_mapAllRooms->at(door->getLinkedRoom()));
                    door->callDesc();
                }

                else
                    std::cout << "Wrong Input! Door does not exist. Please try again.\n\n";

            }break;

            //Leave game
            case(3):
            {
                std::cout << "Thanks for playing.\n\n";
            }break;

            //Wrong input
            default:
            {
                std::cout << "Wrong input! Please try again! \n\n";
            }
        }

    }while(wahl != 3);

}

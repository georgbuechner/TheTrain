//*** Class CDialog ***//

#include "CDialog.hpp"

//startDialog
void CDialog::startDialog()
{
    //Attributes:
    std::string sIndex = "START";   //Index points to the next state to be calles. First state
                                    //Always has the id "START"


    //Loop running till end of dialog is reached
    for(;;)
    {
        //Create current state
        CDialogState* curState = m_mapStates.at(sIndex);

        //print text
        std::cout << curState->getSpeaker() << "  " << curState->getText() << "\n";

        std::cout << sIndex << std::endl;
        CEvent* event = new CEvent(sIndex, "");
        m_EM->throw_event(event);
        delete event;

        //Check wether end is reached
        if(curState->getEnd() == true)
        {
            std::cout << curState->getDialogEnd() << "\n";
            return;
        }

        //Print options
        std::map<size_t, CDialogOptionState*> mapPlayerOptions = curState->getPlayerOptions();
        for(auto it=mapPlayerOptions.begin(); it!=mapPlayerOptions.end(); it++)
            std::cout << it->second->getID() << ": " << it->second->getText() << "\n";
        
        //Player option
        std::string sChoice;
        size_t choice;
        std::cout << ">"; 
        
        getline(std::cin, sChoice);
        choice = std::stoi(sChoice);
        
        //If choice is within range, print player's text, then change index to target state
        if(choice <= mapPlayerOptions.size())
        {
            std::cout << "PLAYER  " << mapPlayerOptions.at(choice)->getText() << "\n";
            sIndex.assign(mapPlayerOptions.at(choice)->getTargetState());
        }
     }
}
 

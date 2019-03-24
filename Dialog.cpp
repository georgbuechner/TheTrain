//*** Class CDialog ***//

#include "CDialog.hpp"


/**
* Constructor
* @parameter map<string, CDialogState*> (dictionary of dialog-states)
*/
CDialog::CDialog(std::map<std::string, CDialogState*> mapStates, std::string sEventmanager) {

    //Assign attributes
    m_mapStates = mapStates;
    if(m_EM->getManagers().count(sEventmanager) != 0)
        m_EM = m_EM->getManagers().at(sEventmanager);
    else
        m_EM = m_EM->getManagers().at("standard");
}

//startDialog
void CDialog::startDialog()
{
    //Attributes:
    std::string sIndex = "START";   //Index points to the next state to be calles. First state
                                    //Always has the id "START"

    //Loop running till end of dialog is reached
    for(;;)
    {
        //Get current state
        CDialogState* curState = m_mapStates.at(sIndex);

        //Call state function
        callStateFunction(curState);
        
        //Throw event "dialogstate [index] started"
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
        std::list<CDialogOptionState*> listPlayerOptions = curState->getPlayerOptions();
        for(auto it=listPlayerOptions.begin(); it!=listPlayerOptions.end(); it++)
        {
            if((*it)->getActive() == true)
                std::cout << (*it)->getKeyword() << ": " << (*it)->getText() << "\n";
        }
        
        bool input = false;
        while(input == false)
        {
            //Player option
            std::string sChoice;
            size_t choice;
            std::cout << ">"; 
            
            getline(std::cin, sChoice);

            //Convert to int
            if(is_number(sChoice) == false)
            {
                std::cout << "Wrong input! Enter a number.\n";
                continue;
            }
            choice = std::stoi(sChoice);

            //If choice is within range, print player's text, then change index to target state
            CDialogOptionState* optState = curState->getOptState(choice, true);

            //Check whether state exists
            if(!optState)
            {
                std::cout << "Wrong input! Enter a number.\n";
                continue;
            }

            //Print players text and change index to target state
            std::cout << "PLAYER  " << curState->getOptState(choice, true)->getText() << "\n";
            sIndex.assign(curState->getOptState(choice, true)->getTargetState());
            input = true;
        }
     }
}
 
bool CDialog::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}


// *** Functions *** //


//Initialize map of all dialog-state-functions
std::map<std::string, void(CDialog::*)(CDialogState*)>CDialog::mapDialogFuncs = {};
/**
* initializeFunctions: adds all functions to map of dialog-state-functions.
*/
void CDialog::initializeFunctions()
{
    // *** Add dialog-state-function to map *** // 
    mapDialogFuncs["standard"] = &CDialog::func_standard;
}


/**
* func_standard: standard function for calling dialog state
* @parameter CDialogState* (Dialog state which was called.
*/
void CDialog::func_standard(CDialogState* state)
{
    //Print text
    std::cout << state->getSpeaker() << "  " << state->getText() << "\n";
}

 

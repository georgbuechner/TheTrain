#include "CQuestStep.hpp"

/**
* Constructor
* @parameter string (step's name)
* @parameter string (step's description)
* @parameter int (achieved)
*/
CQuestStep::CQuestStep(std::string id, std::string sName, std::string sDescription, bool achieved, bool active, std::string sFuncID) {

    //Assign attributes
    m_sID = id;
    m_sName = sName;
    m_sDescription = sDescription;
    m_achieved = achieved;
    m_active = active;
    m_func = mapQuestfuncs.at(sFuncID);
}


//Initialize map of all quest functions
std::map<std::string, void(CQuestStep::*)(CEvent*)>CQuestStep::mapQuestfuncs = {};

/**
* initializeFunctions
* Adds all function pointers to map of pointers
*/
void CQuestStep::initializeFunctions()
{

    // **** Add quests to map **** //

    //Quest: talk to jay
    mapQuestfuncs.insert(std::pair<std::string, void(CQuestStep::*)(CEvent*)>
                                    ("standard", &CQuestStep::standard));
    mapQuestfuncs.insert(std::pair<std::string, void(CQuestStep::*)(CEvent*)> 
                                    ("talk_to_jay_Find", &CQuestStep::talk_to_jay_Find));
    mapQuestfuncs.insert(std::pair<std::string, void(CQuestStep::*)(CEvent*)> 
                                    ("talk_to_jay_Talk", &CQuestStep::talk_to_jay_Talk));
    mapQuestfuncs.insert(std::pair<std::string, void(CQuestStep::*)(CEvent*)>
                                    ("talk_to_jay_Parsen", &CQuestStep::talk_to_jay_Parsen));
    mapQuestfuncs.insert(std::pair<std::string, void(CQuestStep::*)(CEvent*)> 
                                    ("talk_to_jay_givePresent", &CQuestStep::talk_to_jay_givePresent));
    mapQuestfuncs.insert(std::pair<std::string, void(CQuestStep::*)(CEvent*)> 
                                    ("talk_to_jay_dontPresent", &CQuestStep::talk_to_jay_dontPresent));
}


/** functions **/

/**
* standard
* Standard quest-step-function: merely set status to achieved
*/
void CQuestStep::standard(CEvent*) {
    m_achieved = true;

    if(m_achieved == true)
        std::cout << "Teil quest \"" << m_sName << "\" erflogreich!\n";
}

// **** Quest: talk to jay **** //

/**
* talk_to_jay_Find
* Check whether player searched for characters and found jay
* @parameter CEvent* (pointer to event)
*/
void CQuestStep::talk_to_jay_Find(CEvent* event) 
{
    //Get map of all chars in current room
    std::map<std::string, CCharacter*> mapChars = event->getGame()->getPlayer().getCurRoom()
                                                                                    ->getMapChars();
    //Check whether jay is in this room
    if(mapChars.count("jay") == 1)
    {
        //Change "achieved" to true
        m_achieved = true;

        if(m_active == false || m_achieved == false)
                return

        //Step status of next step to true
        event->getGame()->getQuests().at("talk_to_jay")->getSteps().at("talk_to_jay")->setActive(true);

        //If quest is already active print success
        std::cout << "Quest step \"" << m_sName << "\" succsessfull.\n";
    }
}

void CQuestStep::talk_to_jay_Talk(CEvent* event) 
{
    //Get map of all characters in the room
    std::map<std::string, CCharacter*> mapChars = event->getGame()->getPlayer().getCurRoom()
                                                                                    ->getMapChars(); 

    //Check whether jay is in this room
    if(mapChars.count("jay") == 0)
        return;

    //Get array of all accepted words.
    std::vector<std::string> vTake = mapChars.at("jay")->getTake();

    for(size_t it = 0; it<vTake.size(); it++)
    {
        //Check whether current player is selected player (use strcmp and const char*)
        if(strcmp(event->getIdentifier().c_str(), vTake[it].c_str()) == 0) 
        {
            m_achieved = true;

            if(m_active == false || m_achieved == false)
                return

            //Print that quest has been succsessfull
            std::cout << "Quest step \"" << m_sName << "\" succsessfull.\n";

            //Step status of next step to true
            event->getGame()->getQuests().at("talk_to_jay")
                                    ->getSteps().at("talk_to_parsen")->setActive(true);

            //Change parsens dialog:
            CDialog* dialog = event->getGame()->getMapRooms().at("abteil_c")
                                                    ->getMapChars().at("parsen_rogochin")->getDialog();
            dialog->getStates().at("wegen_geschenk")->getPlayerOptions().erase(3);
            CDialogOptionState* optState = new CDialogOptionState(3, "Jay sagte mir, dass du sie bedrängst und sie es deshalb nicht annehmen wird.", "jays_vorwurf");
            dialog->getStates().at("wegen_geschenk")->getPlayerOptions().insert(std::pair<size_t, 
                                                        CDialogOptionState*>(3, optState));
        }
    }
}

void CQuestStep::talk_to_jay_Parsen(CEvent* event) {

    m_achieved = true;
    std::cout << "Quest step: \"" << m_sName << "\" succsessfull.\n"; 
}

void CQuestStep::talk_to_jay_givePresent(CEvent* event) {}
void CQuestStep::talk_to_jay_dontPresent(CEvent* event) {}



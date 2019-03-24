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
    std::map<std::string, std::string> mapChars = event->getGame()->getPlayer().getCurRoom()->getMapChars();

    //Check whether jay is in this room
    if(mapChars.count("jay") == 1)
    {
        if(m_active == false || m_achieved == true)
            return;

        //Step status of next step to true
        event->getGame()->getQuests().at("talk_to_jay")->getSteps().at("talk_to_jay")->setActive(true);

        //If quest is already active print success
        std::cout << "Quest step \"" << m_sName << "\" succsessfull.\n";

        //Change "achieved" to true
        m_achieved = true;
    }
}

void CQuestStep::talk_to_jay_Talk(CEvent* event) 
{
    //Get map of queststeps
    std::map<std::string, CQuestStep*> map_steps = event->getGame()
                                                        ->getQuests().at("talk_to_jay")->getSteps(); 

    //Get map of all characters in the room
    std::map<std::string, std::string> mapCharsRoom = event->getGame()->getPlayer().getCurRoom()->getMapChars(); 
    //Get map of all characters
    std::map<std::string, CCharacter*> mapChars = event->getGame()->getMapChars();

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
            if(m_achieved == true)
                return;

            CQuestStep* findJay = map_steps.at("find_jay");
            if(findJay->getAchieved() == false)
            {
                findJay->setAchieved(true);
                std::cout << "Quest step \"" << findJay->getName() << "\" succsessfull.\n";
                m_active = true;
            }

            //Print that quest has been succsessfull
            std::cout << "Quest step \"" << m_sName << "\" succsessfull.\n";

            //Step status of next step to true
            map_steps.at("talk_to_parsen")->setActive(true);

            //Change parsens dialog:
            CDialog* dialog = mapChars.at("parsen_rogochin")->getDialog();
            dialog->getStates().at("wegen_geschenk")->getOptState(3, false)->setActive(true);

            //Change Jays dialog
            event->getGame()->getMapChars().at("jay")->setDialog(event->getGame()->dialogFactory("factory/Dialogs/defaultDialog.json"));

            //Change "achieved" to true 
            m_achieved = true;
        }
    }
}

void CQuestStep::talk_to_jay_Parsen(CEvent* event) {

    m_achieved = true;
    std::cout << "Quest step: \"" << m_sName << "\" succsessfull.\n"; 
}

void CQuestStep::talk_to_jay_givePresent(CEvent* event) {}
void CQuestStep::talk_to_jay_dontPresent(CEvent* event) {}



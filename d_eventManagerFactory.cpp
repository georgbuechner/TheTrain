/**
* As each dialog has a custom eventmanager, handling everything happening in a dialog
* here all eventmanagers for dialogs are created. 
* This factory is located in an extra .cpp file to assure good overview. The most other factorys
* function with parsing .jsons, this way there is one function to create evry character, room etc.
* here every eventmanager created is a custom eventmanager. 
*/

#include "CGame.hpp"


/** 
* emDialogsFactory: create all dialog eventmanagers.
*/
std::map<std::string, CEventmanager*> CGame::emDialogsFactory()
{
    //Create map of eventmanagers
    std::map<std::string, CEventmanager*> mapEMs; 

    // *** factory/parsenDialog.json *** //
    CEventmanager* eventmanager = new CEventmanager(this);
    CEventhandler* h_anna = new CEventhandler("quest_jay", &CEventhandler::echo_parsenDialogAnna);
    eventmanager->add_listener("anna", h_anna);
    mapEMs.insert(std::pair<std::string, CEventmanager*> 
                                        ("factory/parsenDialog.json", eventmanager));

    return mapEMs;
}



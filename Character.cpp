#include "CCharacter.hpp"

/**
* Constructor 
* @parameter string (character's name)
* @parameter string (character's custom id)
* @parameter vector <string> (words accepted)
* @parameter CDialog* (pointer to character's dialog)
*/
CCharacter::CCharacter(std::string sName, std::string sID, std::vector<std::string> vTake, CDialog* dialog) {

    //Assign attriubutes
    m_sName = sName;
    m_sID = sID;
    m_vTake = vTake;
    m_dialog = dialog;
}


// ** Getter ** //

/**
* getName: get character's name.
* @return string (character's name)
*/
std::string CCharacter::getName() {
    return m_sName;
}

/**
* getID: get character's id.
* @return string (character's custom id)
*/
std::string CCharacter::getID() {
    return m_sID;
}

/**
* getTake: get vector with all accepted words.
* @return vector<string> (array with all accepted words)
*/
std::vector<std::string> CCharacter::getTake() {
    return m_vTake;
}

/**
* getDialog: get pointer to dialog.
* @return CDialog* (pointer to dialog)
*/ 
CDialog* CCharacter::getDialog() {
    return m_dialog;
}


// ** setter ** //

/**
* setDialog: setaracter's dialog.
* @parameter CDialog* (pointer to dialog)
*/
void CCharacter::setDialog(CDialog* dialog) {
    m_dialog = dialog;
}


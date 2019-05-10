/**
* CCharacter.h
* Class for character-objects. A character has a name, a custom id and a dialog. Later a character
* will also own a inventory. Things a character can do, f.e. showing his inventory giving the player
* a quest or else are all happening during the dialog. The eventmanager is used for this. 
* @Author = Jan van Dick
*/

#ifndef CPERSON_H
#define CPERSON_H

#include <iostream>
#include <string>
#include "CDialog.hpp"

class CCharacter
{
private:

    //Attributes
    std::string m_sName;                //Name of the character 
    std::string m_sID;                  //ID of the character
    std::vector<std::string> m_vTake;   //Words acceppted when talkTo
    CDialog* m_dialog;                  //Characters dialog
    
public:
    /**
    * Constructor 
    * @parameter string (character's name)
    * @parameter string (character's custom id)
    * @parameter vector <string> (words accepted)
    * @parameter CDialog* (pointer to character's dialog)
    */
    CCharacter(std::string sName, std::string sID, std::vector<std::string> vTake, CDialog* dialog);
    
    // ** Getter ** //
    
    /**
    * getName: get character's name.
    * @return string (character's name)
    */
    std::string getName();

    /**
    * getID: get character's id.
    * @return string (character's custom id)
    */
    std::string getID();

    /**
    * getTake: get vector with all accepted words.
    * @return vector<string> (array with all accepted words)
    */
    std::vector<std::string> getTake();

    /**
    * getDialog: get pointer to dialog.
    * @return CDialog* (pointer to dialog)
    */ 
    CDialog* getDialog();

    
    // ** setter ** //

    /**
    * setDialog: setaracter's dialog.
    * @parameter CDialog* (pointer to dialog)
    */
    void setDialog(CDialog* dialog);

};

#endif

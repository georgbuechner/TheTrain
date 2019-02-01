//Header CPerson
// @Author = Jan van Dick

#ifndef CPERSON_H
#define CPERSON_H

#include <iostream>
#include <string>
#include "CDialog.h"

class CCharacter
{
private:
    std::string m_sName;    //Name of the character 
    std::string m_sID;      //ID of the character

    CDialog* m_dialog;      //Characters dialog
    
public:
    //Constructor
    CCharacter(std::string sName, std::string sID, CDialog* dialog) {
        m_sName = sName;
        m_sID = sID;
        
        m_dialog = dialog;
    }

    
    //Getter
    
    //Get name
    std::string getName() {
        return m_sName;
    }

    //Get ID
    std::string getID() {
        return m_sID;
    }

    //Get dialog
    CDialog* getDialog() {
        return m_dialog;
    }

};

#endif

//Header CPerson
// @Author = Jan van Dick

#ifndef CPERSON_H
#define CPERSON_H

#include <iostream>
#include <string>

class CCharacter
{
private:
    std::string m_sName;    //Name of the character 
    std::string m_sID;      //ID of the character
    
public:
    //Constructor
    CCharacter(std::string sName, std::string sID) {
        m_sName = sName;
        m_sID = sID;
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

};

#endif

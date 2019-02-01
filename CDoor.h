//Header CDoor
// @Author = Jan van Dick

#ifndef CDOOR_H
#define CDOOR_H

#include <iostream>
#include <string>
#include <vector>

class CDoor
{
private:
    std::string m_sName;    //Name of the Door (can be changed during the game)
    std::string m_sLinkedRoom;      //ID from room the door is leading to

    std::string m_headDescription;
    std::string m_foorDescription;
    std::string m_altDescription;

    void(CDoor::*m_callDescription)();      //Points on a function to call description of the next
                                            //room and gives various other possibilities
public:
    //Constructor
    CDoor(std::string sName, std::string linkedRoom, std::string headDescription, 
            std::string footDescription, std::string altDescription);

    //Getter
    
    //Get name of the door
    std::string getName() {
        return m_sName;
    }

    //Get ID of the room the door is leading to
    std::string getLinkedRoom() {
        return m_sLinkedRoom;
    }

    //Get header description of door
    std::string getHeadDesc() {
        return m_headDescription;
    }

    //Get footer description of door
    std::string getFootDesc() {
        return m_foorDescription;
    }

    //Get alternative description of door
    std::string getAltDesc() {
        return m_altDescription;
    }

    //Setter

    //Set door-name
    void setName(std::string sName) {
        m_sName = sName;
    }

};

//Constructor: 
//chName (name of he door), linkedRoom (Room this door is leading to), 
//localID (ID to clearly identify all doors in a room), ID (ID to clearly identify this door out of all doors)
CDoor::CDoor(std::string sName, std::string sLinkedRoom, std::string headDescription, 
            std::string footDescription, std::string altDescription)
{
    m_sName = sName;
    m_sLinkedRoom = sLinkedRoom;

    m_headDescription = headDescription;
    m_foorDescription = footDescription;
    m_altDescription = altDescription; 
}

#endif   

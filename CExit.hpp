/**
* CExit.h
* Class exit. Exits or objects owned by a room. An exit describs the exit from one room to
* another. An exit can contain alternative room descriptions.
* @author = Jan van Dick
*/ 

#ifndef CDOOR_H
#define CDOOR_H

#include <iostream>
#include <string>
#include <vector>

class CExit
{
private:

    //Attributes
    std::string m_sName;            //Name of the exit (can be changed during the game).
    std::string m_sID;              //Custom id of exit
    std::string m_sLinkedRoom;      //ID from room the exit is leading to.

    std::vector<std::string> m_vTake;   //Array which accept using exit

    std::string m_headDescription;  //Description placed before the room-description.
    std::string m_foorDescription;  //Description placed after the room-description.
    std::string m_altDescription;   //Alternative description. (No room-description is printed)

public:
    /**
    * Constructor
    * @parameter string (name of the door)
    * @parameter string (custom id)
    * @parameter string (identifier for linked room)
    * @parameter vector<string> (Array with accepted words)
    * @parameter string (head-description)
    * @parameter string (foot-description)
    * @parameter string (alternative-description)
    */
    CExit(std::string sName, std::string sID,  std::string sLinkedRoom, std::vector<std::string> vTake, 
                std::string headDescription, std::string footDescription, std::string altDescription)
    {
        //Assign attributes
        m_sName = sName;
        m_sID = sID;
        m_sLinkedRoom = sLinkedRoom;
        m_vTake = vTake;
        m_headDescription = headDescription;
        m_foorDescription = footDescription;
        m_altDescription = altDescription; 
    }

    // ** Getter ** //
    
    /**
    * getName: return exit's name.
    * @return string (exit's name)
    */
    std::string getName() {
        return m_sName;
    }

    /**
    * getID: get exit's custom id.
    * @return string (custom id)
    */
    std::string getID() {
        return m_sID;
    }

    /**
    * getLinkedRoom: return identifier for room exit is following to
    * @return string (identifier to linked room)
    */ 
    std::string getLinkedRoom() {
        return m_sLinkedRoom;
    }

    /**
    * getTake: return vector of words accepted.
    * @return vector<string> (array of words accepted)
    */
    std::vector<std::string> getTake() {
        return m_vTake;
    }

    /**
    * getHeadDesc: return description placed before room-description.
    * @return string (head-description)
    */
    std::string getHeadDesc() {
        return m_headDescription;
    }

    /**
    * getFootDesc: return description placed after room-description
    * @return string (foot-description)
    */
    std::string getFootDesc() {
        return m_foorDescription;
    }

    /**
    * getAltDesc: return description printed instead of room-description
    * @return string (alternative-description)
    */
    std::string getAltDesc() {
        return m_altDescription;
    }

    // ** Setter ** //

    /**
    * setName: set exit's name
    * @parameter string (exit's name)
    */
    void setName(std::string sName) {
        m_sName = sName;
    }

};

#endif   

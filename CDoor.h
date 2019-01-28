//Header CDoor
// @Author = Jan van Dick

#ifndef CDOOR_H
#define CDOOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//Forward declarations:
class CRoom;

class CDoor
{
private:
    std::string m_sName;    //Name of the Door (can be changed during the game)
    CRoom* m_linkedRoom;    //Room the door is leading to

    int m_curDescription;                       //Marks current discription 
    std::vector<std::string> m_sDescriptions;   //String array of all descriptions
                                                //of the room this door is leading to

    void(CDoor::*m_callDescription)();      //Points on a function to call description of the next
                                            //room and gives various other possibilities
public:
    //Constructor
    CDoor(std::string sName, CRoom* linkedRoom, std::vector<std::string> sDescription, 
            void(CDoor::*callDescription)());

    //Getter
    
    //Get name of the door
    std::string getName() {
        return m_sName;
    }

    //Get the room the door is leading to
    CRoom* getLinkedRoom() {
        return m_linkedRoom;
    }

    
    //Setter

    //Set door-name
    void setName(std::string sName) {
        m_sName = sName;
    }

    //Set currentDiscription 
    void setCurrentDescription(int Index) {
        m_curDescription = Index;
    }

    //Set callDescription
    void setCallDescription(void(CDoor::*callDescription)()) {
        m_callDescription = callDescription;
    }

    //Print Description
    void printDescription();

    //Call "m_callDescription
    void callDesc();

    //Descriptions
    void DescCall_Standard();
    void DescCall_Increase1CurDesc();
    void DescCallLeninsTomb();
};

//Constructor: 
//chName (name of he door), linkedRoom (Room this door is leading to), 
//localID (ID to clearly identify all doors in a room), ID (ID to clearly identify this door out of all doors)
CDoor::CDoor(std::string sName, CRoom* linkedRoom, std::vector<std::string> sDescriptions, 
                void(CDoor::*callDescription)())
{
    m_sName = sName;
    m_linkedRoom = linkedRoom;
    
    m_curDescription = 0;
    for(unsigned int i=0; i<sDescriptions.size(); i++)
        m_sDescriptions.push_back(sDescriptions[i]); 
    
    m_callDescription = callDescription;
}


//PrintDescription:
//Load current description, then print current description
void CDoor::printDescription()
{
    //Vaiables
    std::string sDescription;    //String containing description
    std::string sDescName = "DoorDescriptions/";
    sDescName.append(m_sDescriptions[m_curDescription]);

    //Read description-file
    std::ifstream read(sDescName);
    
    //Check, whether file has been open
    if (!read)
        std::cout << "File: \"" << sDescName << "\"  could not be opended! \n\n";

    //Load description form file "into sDescription"
    else
    {
        std::string sBuffer;
        while(!read.eof())
        {
            getline(read, sBuffer);
            std::cout << sBuffer;    
        }
    }
        //sDescription.assign((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    //close file
    read.close();

    //Print description
    std::cout << sDescription << "\n";
}

//callDesc
//Calls m_callDescription which is a pointer to the wanted function
void CDoor::callDesc()
{
   (this->*m_callDescription)();
}


//****************Description Calls *******************//

//DescCall_Standard: 
//Simply calls the current description
void CDoor::DescCall_Standard()
{
    //Print description
    this->printDescription();
}

//DescCall_IncreaseCurDesc()
//Prints current description and increases current description
void CDoor::DescCall_Increase1CurDesc()
{
    this->printDescription();   //Print description
    this->m_curDescription++;   //Increase curDescription by 1
    this->setCallDescription(&CDoor::DescCall_Standard); //Change DescCall to standard
}

#endif   

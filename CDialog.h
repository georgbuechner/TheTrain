//CDialog
// @Author Jan van Dick

#ifndef CDIALOG_H
#define CDIALOG_H

#include <iostream>
#include <string>
#include <map>

class CState;
class COptionState;

// *** Class: CDialog *** //
class CDialog
{
private:
    std::map<std::string, CState*>* m_mapStates;    //Map containing all states of dialog

public:
    //Constructor
    CDialog(std::map<std::string, CState*>* mapStates) {
        m_mapStates = mapStates;
    }

    //Function handling dialog
    void startDialog();
};


// *** Class: CState *** //
class CState
{
private:
    std::string m_sID;          //Id
    std::string m_sText;        //Text
    std::string m_sSpeaker;     //String of person who is speaking
    std::string m_sDialogEnd;   //Text to print in case this is last state
   
    std::map<size_t, COptionState*>* m_playerOptions;   //Player options

    bool m_end;             //Dialog ended?

public:
    //Constructor
    CState(std::string sID, std::string sText, std::string sSpeaker, std::string sDialogEnd, 
            std::map<size_t, COptionState*>* playerOptions, bool end) {

        m_sID = sID;
        m_sText = sText;
        m_sSpeaker = sSpeaker;
        m_sDialogEnd = sDialogEnd;
        m_playerOptions = playerOptions;
        m_end = end;
    }

    // *** getter *** //
    
    //Get ID
    std::string getID() {
        return m_sID;
    }

    //Get text
    std::string getText() {
        return m_sText;
    }

    //Get speaker
    std::string getSpeaker() {
        return m_sSpeaker;
    }

    //Gte dialog end
    std::string getDialogEnd() {
        return m_sDialogEnd;
    }

    //Get player options
    std::map<size_t, COptionState*>* getPlayerOptions() {
        return m_playerOptions;
    }

    //Get end
    bool getEnd() {
        return m_end;
    }
};


// *** Class: COptionState *** //
class COptionState
{
private:
    size_t m_id;                  //ID
    std::string m_sText;        //Text
    std::string m_sTargetState; //State this state is linking to

public:
    //Constructor
    COptionState(size_t id, std::string sText, std::string sTargetState) {

        m_id = id;
        m_sText = sText;
        m_sTargetState = sTargetState;
    }

    // *** getter *** //
    
    //Get id
    size_t getID() {
        return m_id;
    }

    //Get text
    std::string getText() {
        return m_sText;
    }

    //Get targetstate
    std::string getTargetState() {
        return m_sTargetState;
    }
};

     
//*** Class CDialog ***//

//startDialog
void CDialog::startDialog()
{
    std::string sIndex = "START";

    for(;;)
    {
        //Create current state
        CState* curState = m_mapStates->at(sIndex);

        //print text
        std::cout << curState->getSpeaker() << "  " << curState->getText() << "\n";

        //Check wether end is reached
        if(curState->getEnd() == true)
        {
            std::cout << curState->getDialogEnd() << "\n";
            return;
        }

        //Print options
        std::map<size_t, COptionState*>* mapPlayerOptions = curState->getPlayerOptions();
        for(auto it=mapPlayerOptions->begin(); it!=mapPlayerOptions->end(); it++)
            std::cout << it ->second->getID() << ": " << it->second->getText() << "\n";
        
        //Player option
        size_t choice;
        std::cout << ">"; std::cin >>choice;
        
        if(choice <=mapPlayerOptions->size())
        {
            std::cout << "PLAYER  " << mapPlayerOptions->at(choice)->getText() << "\n";
            sIndex.assign(mapPlayerOptions->at(choice)->getTargetState());
        }
     }
}
         
    
#endif     
       
        

        
     
        


    
        
    

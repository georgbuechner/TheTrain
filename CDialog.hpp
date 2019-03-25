/**
* CDialog.h
* The class builds a dialog. It mainly contains a dictionary with different states. And a "startDialog"-
* function executiung the dialog. 
* @Author Jan van Dick
*/

#ifndef CDIALOG_H
#define CDIALOG_H

#include <iostream>
#include <string>
#include <map>
#include "CDialogState.hpp"
#include "CDialogOptionState.hpp"
#include "CEventmanager.hpp"

//Forward declarations
class CDialogState;
class CDialogOptionState;
class CEventmanager;


class CDialog
{
private:
    
    //Attributes
    std::map<std::string, CDialogState*> m_mapStates;   //Map containing all states of dialog
    CEventmanager* m_EM;

    static std::map<std::string, void(CDialog::*)(CDialogState*)> m_mapDialogFuncs;

public:
    /**
    * Constructor
    * @parameter map<string, CDialogState*> (dictionary of dialog-states)
    */
    CDialog(std::map<std::string, CDialogState*> mapStates, std::string sEventmanager);

    
    // ** Getter ** //

    /**
    * getStates: return all states of dialog
    * @return map<std::string, CDialogState*> (return referenz to map of dialogs)
    */
    std::map<std::string, CDialogState*>& getStates() {
        return m_mapStates;
    }

    /**
    * startDialog: function starting and running dialog
    */
    void startDialog();

    bool is_number(const std::string& s);

    
    // *** Functions *** //

    /**
    * initializeFunctions: adds all functions to map of dialog-state-functions.
    */
    static void initializeFunctions();

    /**
    * callStateFunction: call function of given state
    * parameter CDialogState* (dialog state)
    */
    void callStateFunction(CDialogState* state);
 
    void func_standard(CDialogState* state);        //Standard function
    void func_parsen_anna(CDialogState* state);          //parsen_anna
};

    
#endif     

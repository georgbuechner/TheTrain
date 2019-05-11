/**
* CGame.h
* The class builds the basic context, containing the player, global variables (f.e. map with all rooms).
* It also contains the play-function with the main loop and the factory creating all characters, rooms
* etc.
* @author = fux
*/


#ifndef CGAME_H
#define CGAME_H


//Forward declarations
class CEventmanager;
class CDialog;
class CQuest;
class CQuestStep;

#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include "CExit.hpp"
#include "CRoom.hpp"
#include "CPlayer.hpp"
#include "CDialog.hpp"
#include "CEventmanager.hpp"
#include "CEventManager.hpp"
#include "CEventhandler.hpp"
#include "CQuesthandler.hpp"
#include "CCommandParser.hpp"
#include "CQuest.hpp"
#include "CQuestStep.hpp"
#include "json.hpp"


class CGame
{
private:
    
    //Attributes
    CPlayer m_Player;                               //Player 
    CEventmanager* m_EM;                            //Eventmanager of the game
    bool m_gameEnd;                                 //Game ended? 

    std::map<std::string, CRoom*> m_mapAllRooms;            //Map of all exits in the game.
    std::map<std::string, CCharacter*> m_mapAllChars;       //Map of all chars in the game.
    std::map<std::string, CQuest*> m_mapQuests;             //Map of all quests in the game.


public:
    /**
    * Constructor
    */
    CGame() : m_Player("", NULL) {

        //Assign default values to attributes
        m_gameEnd = false;
        m_Player = CPlayer("", NULL);
    }

    // ** getter ** //

    /**
    * getPlayer: return player.
    * @return CPlayer& (Referenz to player)
    */
    CPlayer& getPlayer() {
        return m_Player;
    }

    /** 
    * getEventmanager: get eventmanager of game/ of this context.
    * @return CEventmanager& (Referenz to the game's eventmanager)
    */
    CEventmanager* getEventmanager() {
        return m_EM;
    }

    /**
    * getMapRooms: return map of all rooms
    * @return map<string, CRoom*>* (map of all rooms in the game)
    */
    std::map<std::string, CRoom*>& getMapRooms() {
        return m_mapAllRooms;
    }

    /**
    * getMapChars: return map of all characters 
    * @return map<string, CCharacter*> (map of all chars in the game)
    */
    std::map<std::string, CCharacter*>& getMapChars() {
        return m_mapAllChars;
    }
    /**
    * getQuets: return map of all quests 
    * @return map<string, CQuets*> (map of all quests in the game)
    */
    std::map<std::string, CQuest*>& getQuests() {
        return m_mapQuests;
    }
    // ** setter ** //

    /**
    * setEndGame: set whether end of game is reached. (Mostly used by EventHandlers, when event caused
    * game to end.
    * @parameter bool
    */
    void setEndGame(bool end) {
        m_gameEnd = end;
    }

    /**
    * play: function with main loop. Also creates all eventhandlers
    */
    void play();    


    // *** Factorys *** // (Factorys create objects, like characters, rooms, exits and further more)

    /**
    * worldFactory: calls als other factorys and initializes player. Thus creates the hole game world.
    */
    void worldFactory();

    /**
    * roomFactory: Creates all rooms out of a json (single file)  and calls, the other Factory 
    * for each object in a room. This might be changes later, that one room is one json then 
    * roomFactory would still create all rooms but load different json-files. Another option is
    * to add a level "Area". In this case roomFactory would only create all rooms in a area. An
    * "areaFactory" would be needed areafactory <-> roomFactory corresponds like roomFactory <->
    * characterFactory.
    * @parameter string (path to the json file with all rooms)
    * @return map<string, CRoom*> (map with all rooms in the game)
    */
    std::map<std::string, CRoom*> roomFactory(std::string sPath);

    /**
    * exitFactory: gets called by roomFactory. Creates all exits from a room.
    * @parameter nlohmann::json (a json with a list of json-objects (each object is one exit)
    * @return map<size_t, CExit*> (map of all exits created)
    */
    std::map<size_t, CExit*> exitFactory(nlohmann::json j_listDoors);

    /**
    * characterFactory: gets called by roomFactory. Creates all characters in a room.
    * @parameter nlohmann::json (a json with a list of json-objects (each object is one character)
    * @return map<string, CCharacter*> (map of all characters created)
    */
    std::map<std::string, std::string> characterFactory(nlohmann::json j_listCharacters);   

    /**
    * dialogFactory: gets called by characterFactory. Parses a given dialog (.json-file) into 
    * an object of CDialog. Each dialog is owned by a character.
    * @parameter string (Path to the json)
    * @return CDialog* (Parsed dialog)
    */
    CDialog* dialogFactory(std::string sPath);

    /**
    * dialogOptStateFactory: parse list of option states and return a map 
    * @parameter vector<json> (list of jsons)
    * @return map<string, CDialogOptionState> (Map of optionstates)
    */
    std::list<CDialogOptionState*> dialogOptStateFactory(std::vector<nlohmann::json> v_optStates);

    /**
    * questFactory: creates all quests in game.
    */
    std::map<std::string, CQuest*> questFactory(std::string);

    /**
    * questStepFactory: create all steps of a quest.
    * @parameter vector<nlohmann::json> (vecor with all steps of a quest)
    * @return list<CQuestStep*> (list with all quest-steps)
    */
    std::map<std::string, CQuestStep*> questStepFactory(std::vector<nlohmann::json> v_steps);

    /**
    * handler: endGame: Print message for end of game (this might better be moved into CGame::play() )
    * and set CGame::m_gameEnd to true (this causes main loop in CGame::play() function to break)
    * Eventtype: "endGame"
    * @parameter string (Identifier of event thrown)
    */
    void endGame(std::string sEvent);

    /**
    * handler: endGameDirectly: End game without asking
    * Eventtype: "endGameDirectly"
    * @parameter CEvent* (pointer to event thrown)
    */
    void endGameDirectly(std::string sEvent);


};
   
#endif
    

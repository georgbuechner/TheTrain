// *** CommandParser *** //
#include "CCommandParser.hpp"


/**
* parseCommand: parse a command the player enter into an event. The event contains an event type
* what does the player want to do. F.e. "changeRoom" in case the player wants to go somewhere and
* an identifier providing additional information, in our example where the player wants to go to. 
* Assuming the player entered "go to kitchen" the string will be parsed into an event with event 
* type "changeRoom" and identifier "kitchen". 
* @parameter string (player input)
* @return CEvent* (Pointer to event created)
*/
CEvent* CCommandParser::parseCommand(std::string sInput)
{
    //Create regular expressions for different command the player might have choosen
    std::regex showExits("((Z|z)eige).*Ausgänge");
    std::regex goTo("(G|g)(ehe) (.*)");
    std::regex showcharacters("(Z|z)eige.*(P|p)ersonen.*");
    std::regex talkTo1("(S|s)(preche )(.*) an");
    std::regex talkTo2("(R|r)(ede mit )(.*)");
    std::regex end("((V|v)erlasse|(B|b)eende).*(S|s)piel");

    //Create an instans of smatch
    std::smatch m;


    //Check which regular expression the players input matches. Create and return event if match

    //Show exits:
    if(std::regex_match(sInput, showExits)) {
        CEvent* event = new CEvent("showExits", "");
        return event;
    }

    //Change room
    if(std::regex_search(sInput, m, goTo)) {
        CEvent* event = new CEvent("changeRoom", m[3]); 
        return event;
    }

    //Show characters in room:
    if(std::regex_match(sInput, m, showcharacters)) {
        CEvent* event = new CEvent("showChars", "");
        return event;
    }

    //Talk to character:
    if(std::regex_match(sInput, m, talkTo1) || std::regex_match(sInput, m, talkTo2)) {
        CEvent* event = new CEvent("talkTo", m[3]); 
        return event;
    }

    //End game
    if(std::regex_match(sInput, m, end)) {
        CEvent* event = new CEvent("endGame", "");
        return event;
    }

    CEvent* event = new CEvent("falseInput", "");
    return event;
}



/**
* q_eventManagerFactory.cpp
* .cpp-file to create eventmanager for all quests.
*/

#include "CGame.hpp"

void CGame::emQuestFactory()
{
    //Eventmanager for "talk to Jay"

    //Step: "findJay"
    CEventhandler* h_findJay = new CEventhandler("findJay", &CEventhandler::echo_findJay);
    m_EM->add_listener("showChars", h_findJay);

    //Step: "talkToJay"
    CEventhandler* h_talkToJay = new CEventhandler("talkToJay", &CEventhandler::echo_talkToJay);
    m_EM->add_listener("talkTo", h_talkToJay);

    //Step: "gibGeschenk"
    CEventhandler* h_geschenkGeben = new CEventhandler("gibGeschenk", &CEventhandler::echo_gibGeschenk);
    m_EM->add_listener("gibGechenk", h_geschenkGeben);

    //Step: "gibGeschenkNicht"
    CEventhandler* h_geschenkNichtGeben = new CEventhandler("gibGeschenkNicht", 
                                                                &CEventhandler::echo_gibGeschenkNicht);
    m_EM->add_listener("gibGeschenkNicht", h_geschenkNichtGeben);
}
    
    

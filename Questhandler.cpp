#include "CEventhandler.hpp" 


CQuesthandler::CQuesthandler(std::string sId, std::string sQuest, std::string sQuestStep) 
    : CEventhandler::CEventhandler(sId, NULL)
{
    m_sID = sId,
    m_sQuest = sQuest;
    m_sQuestStep = sQuestStep;
    m_func2 = &CQuesthandler::echo_callQuest;

    std::cout << "Created questhandler with id: " << sId << "\n";
}
    
void CQuesthandler::echo_callQuest(CEvent* event)
{
    /*
    event->getGame()->getQuests().at(m_sQuest)->getSteps().at(m_sQuestStep)->callQuestFunction(event);
    */
}

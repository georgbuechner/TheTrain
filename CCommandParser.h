//CCommandparser.h

#ifndef CCOMMANDPARSER_H 
#define CCOMMANDPARSER_H 

#include <iostream>
#include <string>
#include <regex>

class CCommandParser
{
public:
    int parseCommand(std::string sInput);

};

int CCommandParser::parseCommand(std::string sInput)
{
    std::regex showDoors("show.*doors");
    std::regex goTo("go to.*");
    std::regex showcharacters("show.*char.*");
    std::regex talkTo("talk to.*");
    std::regex end("(quit|exit) game");

    if(std::regex_match(sInput, showDoors))
        return 1;
    if(std::regex_match(sInput, goTo))
        return 2;
    if(std::regex_match(sInput, showcharacters))
        return 3;
    if(std::regex_match(sInput, talkTo))
        return 4;
    if(std::regex_match(sInput, end))
        return 5;

    return 0;
}

#endif

    

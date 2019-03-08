#pragma once

#include "expert_system.h"

class Expert;
class Parser
{
public:
    Parser(Parser const &src) = delete;
    Parser &operator=(Parser const &rhs) = delete;
    ~Parser();
private:
    Parser();
    void    parseString(std::string str, Expert &exp);
    void    parseFacts(std::string str, Expert &exp);
    void    checkFact(Expert &exp, char varFact);
    void    parseAllFacts(Expert &exp);
    void    parseQueries(std::string str, Expert &exp);
public:
    static Parser &instance();
    void parseInput(std::vector<std::string> input, Expert &exp);
};

#pragma once

#include "expert_system.h"

class Expert
{
public:
    Expert(Expert const &src) = delete;
    Expert &operator=(Expert const &rhs) = delete;
    ~Expert();
private:
    Expert();
    void    getListOfRules(char name);
    bool    checkRule(std::string rule, char name);
    bool    checkListRules(Rule rule);

    std::vector<Rule> listRules;

public:
    static Expert &instance();

    std::vector<Rule> rules;
    std::vector<Fact> facts;
    std::vector<char> queries;

    bool getAnswer(char name);
};

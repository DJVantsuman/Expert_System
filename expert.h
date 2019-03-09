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
    bool    checkRule(Rule rule, std::vector<Rule> &listRules);
    bool    checkListRuls(Rule rule, char search);
    std::vector<Rule>   createListOfRuleToSolve(char name, char search);
    std::string         createExpression(Rule rule, char name);
    int     calculate(std::string expression);
    int     getFact(char name);



public:
    static Expert &instance();

    std::vector<Rule> rules;
    std::vector<Fact> facts;
    std::vector<char> queries;


    int getAnswer(char name, char search);
};

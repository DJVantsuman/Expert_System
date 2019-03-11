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

    bool                checkRule(Rule rule, std::vector<Rule> &listRules);
    bool                checkListRules(Rule rule, char search);
    int                 findInRule(std::string rule, char name);
    std::vector<Rule>   createListOfRuleToSolve(char name, char search);
    std::string         createExpression(std::string rule, char name);
    char                calculate(std::string expression);
    int                 getPriority(char s, char e);
    char                getFact(char name);



public:
    static Expert &instance();

    std::vector<Rule> rules;
    std::vector<Fact> facts;
    std::vector<char> queries;


    char getAnswer(char name, char search);
};

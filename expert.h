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
    std::vector<std::string> getListOfRules(std::string name);

public:
    static Expert &instance();

    std::vector<Rule> rules;
    std::vector<Fact> facts;
    std::vector<char> queries;

    bool getAnswer(char name);
};

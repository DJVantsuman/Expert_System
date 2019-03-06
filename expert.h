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
public:
    static Expert &instance();

    std::map<std::string, std::string> rules;
    std::map<std::string, bool> facts;
    std::vector<std::string> queries;
};

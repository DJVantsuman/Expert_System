#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <exception>
#include <regex>
#include <algorithm>
#include <cctype>



struct Rule
{
	std::string left;
	std::string right;
	std::string symbol;
};

struct Fact
{
	char name;
    /*
     * 0 - false
     * 1 - true
     * 2 - none
     */
    int value;
};

#include "expert.h"
#include "reader.h"
#include "lexer.h"
#include "parser.h"


#endif // EXPERT_SYSTEM_H

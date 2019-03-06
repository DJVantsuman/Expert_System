#pragma once

#include "expert_system.h"

class Lexer
{
public:
    Lexer(Lexer const &src) = delete;
    Lexer &operator=(Lexer const &rhs) = delete;
    ~Lexer();
private:
    Lexer();
    void    checkString(std::string str);
    void    checkOption(std::string str);
    void    prepareStr(std::vector<std::string> input);
public:
    static Lexer &instance();
    void checkInput(std::vector<std::string> input);
};

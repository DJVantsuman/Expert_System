#include "lexer.h"

Lexer::Lexer() {

}

Lexer::~Lexer() {

}

Lexer &Lexer::instance() {
    static Lexer lexer;
    return lexer;
}

void    Lexer::checkString(std::string str) {
    std::cmatch result;
    std::regex reg("([\\(\\)A-Z \\+!\\|\\^]+)"
                   "([<=>]{2,3})"
                   "([\\(\\)A-Z \\+!\\|\\^]+)"
                   "([#][\\W\\w]*)?");
    if (!std::regex_match(str.c_str(), result, reg))
        throw "Mistake in string \"" + str + "\"";
}

void    Lexer::checkOption(std::string str)
{
    std::cmatch result;
    std::regex reg("([\?=]?)"
                   "([A-Z ]*)"
                   "(#.*)?");
    if (!std::regex_match(str.c_str(), result, reg))
        throw "Mistake in string \"" + str + "\"";
}

void    Lexer::checkInput(std::vector<std::string> input) {
    for (size_t i = 0; i < input.size(); i++)
    {
        input[i].erase(std::remove_if(input[i].begin(), input[i].end(), isspace), input[i].end());
//        std::cout << input[i] << std::endl;
        if (input[i][0] == '#' || input[i].empty())
            continue;
        else if (input[i][0] == '=' || input[i][0] == '?')
            checkOption(input[i]);
        else
            checkString(input[i]);
    }
}

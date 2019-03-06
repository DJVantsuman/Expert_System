#include "parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

Parser &Parser::instance() {
    static Parser parser;
    return parser;
}

void Parser::parseString(std::string str, Expert &exp)
{
    std::cmatch result;
    std::regex reg("([\\(\\)A-Z \\+!\\|\\^]+)"
                   "([<=>]{2,3})"
                   "([\\(\\)A-Z \\+!\\|\\^]+)"
                   "([#][\\W\\w]*)?");
    if (!std::regex_match(str.c_str(), result, reg))
        throw "Mistake in string \"" + str + "\"";
    else {
        exp.rules.insert(make_pair(result[1], result[3]));
        std::cout << result[1] << " <<<>>> " << result[3] <<std::endl;
    }
}

void Parser::parseFacts(std::string str, Expert &exp)
{
    std::string ch;
    std::cmatch result;
    std::regex reg("(=)"
                   "([A-Z ]*)"
                   "(#.*)?");
    if (!std::regex_match(str.c_str(), result, reg))
        throw "Mistake in string \"" + str + "\"";
    else {
        ch = result[2];
        for (size_t i = 0; i < ch.size(); i++) {
            exp.facts.insert(make_pair(std::to_string(ch.at(i)), true));
        }
    }
}

void Parser::parseQueries(std::string str, Expert &exp)
{
    std::string ch;
    std::cmatch result;
    std::regex reg("(\\?)"
                   "([A-Z ]*)"
                   "(#.*)?");
    if (!std::regex_match(str.c_str(), result, reg))
        throw "Mistake in string \"" + str + "\"";
    else {
        ch = result[2];
        for (size_t i = 0; i < ch.size(); i++) {
            exp.queries.push_back(std::to_string(ch.at(i)));
        }
    }
}

void Parser::parseInput(std::vector<std::string> input, Expert &exp)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        input[i].erase(std::remove_if(input[i].begin(), input[i].end(), isspace), input[i].end());
//        std::cout << input[i] << std::endl;
        if (input[i][0] == '#' || input[i].empty())
            continue;
        else if (input[i][0] == '=')
            parseFacts(input[i], exp);
        else if (input[i][0] == '?')
            parseQueries(input[i], exp);
        else
            parseString(input[i], exp);
    }
}

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
        Rule rule;
        
        rule.left = result[1];
        rule.right = result[3];
        rule.symbol = result[2];
        exp.rules.push_back(rule);
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
            Fact fact;
            fact.name = ch.at(i);
            fact.value = '1';
            exp.facts.push_back(fact);
        }
    }
}

void Parser::checkFact(Expert &exp, char varFact)
{
    int f;

    f = 0;
    for (size_t i = 0; i < exp.facts.size(); i++)
    {
        if (exp.facts[i].name == varFact)
            f++;
    }
    if (f == 0)
    {
        Fact fact;

        fact.name = varFact;
        fact.value = '0';
        exp.facts.push_back(fact);
    }
}

void Parser::parseAllFacts(Expert &exp)
{
    for (size_t i = 0; i < exp.rules.size(); i++)
    {
        for (size_t j = 0; j < exp.rules[i].left.size(); j++)
        {
            if(exp.rules[i].left[j] >= 65 && exp.rules[i].left[j] <= 90)
                checkFact(exp, exp.rules[i].left[j]);
        }

        for (size_t k = 0; k < exp.rules[i].right.size(); k++)
        {
            if(exp.rules[i].right[k] >= 65 && exp.rules[i].right[k] <= 90)
                checkFact(exp, exp.rules[i].right[k]);
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
            exp.queries.push_back(ch.at(i));
        }
    }
}

void Parser::parseInput(std::vector<std::string> input, Expert &exp)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        input[i].erase(std::remove_if(input[i].begin(), input[i].end(), isspace), input[i].end());
        if (input[i][0] == '#' || input[i].empty())
            continue;
        else if (input[i][0] == '=')
            parseFacts(input[i], exp);
        else if (input[i][0] == '?')
            parseQueries(input[i], exp);
        else
            parseString(input[i], exp);
    }
    parseAllFacts(exp);
}

#include "expert.h"

Expert::Expert(){

}

Expert::~Expert() {

}

Expert &Expert::instance() {
    static Expert expert;
    return expert;
}

bool    Expert::getAnswer(char name)
{
    this->listRules.clear();
    getListOfRules(name);

    std::cout << "Queries " << name << std::endl;
    for(size_t i = 0; i < this->listRules.size(); i++) {
        std::cout << this->listRules[i].left << this->listRules[i].symbol
                     << this->listRules[i].right <<  std::endl;
    }
    return false;
}

void Expert::getListOfRules(char name)
{
    std::map<std::string, std::string> listRules;

    for (size_t i = 0; i < this->rules.size(); i++)
    {
        for (size_t j = 0; j < this->rules[i].right.size(); j++)
        {
            if(this->rules[i].right[j] == name) {
                if(checkRule(this->rules[i].right, name) && checkListRules(this->rules[i]))
                    this->listRules.push_back(this->rules[i]);
                break ;
            }
        }
    }

    for (size_t i = 0; i < this->rules.size(); i++)
    {
        for (size_t k = 0; k < this->rules[i].left.size(); k++)
        {
            if(this->rules[i].left[k] == name) {
                if(checkRule(this->rules[i].right, name)  && checkListRules(this->rules[i]))
                    this->listRules.push_back(this->rules[i]);
                break ;
            }
        }
    }
}

bool Expert::checkRule(std::string rule, char name)
{
    for (size_t i = 0; i < rule.size(); i++)
    {
        if(!(rule[i] >= 65 && rule[i] <= 90) && rule[i] != '+' &&
            rule[i] != '(' && rule[i] != ')' &&
                !(rule.size() == 2 && rule[0] == '!' && rule[1] == name))
            return false;
    }
    return true;
}

bool Expert::checkListRules(Rule rule)
{
    for (size_t i = 0; i < this->listRules.size(); i++)
    {
        if(this->listRules[i].right == rule.right && this->listRules[i].left == rule.left)
            return false;
    }
    return true;
}
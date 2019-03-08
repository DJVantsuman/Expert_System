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
    std::string var;
    std::vector<std::string> listRules;

    var += name;
    listRules = getListOfRules(var);
//    std::cout << "listRules.size() = " << listRules.size() << std::endl;
    for(size_t i = 0; i < listRules.size(); i++) {
        std::cout << "Queries " << name << "; Rules " <<  listRules[i] <<  std::endl;
    }
    return false;
}

std::vector<std::string> Expert::getListOfRules(std::string name)
{
    std::vector<std::string> listRules;

//    std::cout << "Name = " << name << std::endl;
    for (size_t i = 0; i < this->rules.size(); i++)
    {
//        std::cout << "name = " << name << std::endl;
//        std::cout << "this->rules[i].left = " << this->rules[i].left << std::endl;
//        std::cout << "this->rules[i].right = " << this->rules[i].right << std::endl;

        if(this->rules[i].left == name)
            listRules.push_back(this->rules[i].right);
        else if(this->rules[i].right == name)
            listRules.push_back(this->rules[i].left);
    }
    return  listRules;
}

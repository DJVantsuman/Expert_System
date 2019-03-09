#include "expert.h"

Expert::Expert(){

}

Expert::~Expert() {

}

Expert &Expert::instance() {
    static Expert expert;
    return expert;
}

int    Expert::getAnswer(char name, char search)
{
    int answer;
    std::vector<Rule> listOfRuleToSolve;

    answer = 2;
    listOfRuleToSolve = createListOfRuleToSolve(name, search);



////////////// Delete ////////////////////
    std::cout << "Queries " << name << std::endl;
    for(size_t i = 0; i < listOfRuleToSolve.size(); i++) {
        std::cout << listOfRuleToSolve[i].left << listOfRuleToSolve[i].symbol
                     << listOfRuleToSolve[i].right <<  std::endl;
    }
//////////////////////////////////////////


    for(size_t i = 0; i < listOfRuleToSolve.size(); i++)
    {
        if(listOfRuleToSolve[i].right.size() == 1 && listOfRuleToSolve[i].right[0] == name) {
            try {
                answer = calculate(createExpression(listOfRuleToSolve[i], name));
            }
            catch (...){
                std::cout << name << " is NONE" << std::endl;
                continue;
            }
        }
    }
    return answer;
}

int     Expert::getFact(char name)
{
    for(size_t i = 0; i < this->facts.size(); i++)
    {
        if(this->facts[i].name == name)
            return this->facts[i].value;
    }
    return 2;
}

int    Expert::calculate(std::string expression)
{
    std::vector<int> var;
    std::stack<char> symbol;
    int d;

    d = 0;
    for(size_t i = 0; i < expression.size(); i++) {
        if(expression[i] == '1') {
            d++;
            var.push_back(1);
        }
        else if(expression[i] == '0') {
            d++;
            var.push_back(0);
        }
        else {
            if(expression[i] == '(')
            {
                d = 0;
                symbol.push(expression[i]);
            }
            else if(expression[i] == ')') {
                d++;
                symbol.pop();
            }
            else
                symbol.push(expression[i]);
        }
        if(d == 2)
        {
            if(symbol.top() == '+' && var[var.size() - 1] == 1 && var[var.size() - 2] == 1) {
                var.pop_back();
                var.pop_back();
                symbol.pop();
                var.push_back(1);
            }
            else if(symbol.top() == '|' && (var[var.size() - 1] == 1 || var[var.size() - 2] == 1)) {
                var.pop_back();
                var.pop_back();
                symbol.pop();
                var.push_back(1);
            }
            else if(symbol.top() == '^' && ((var[var.size() - 1] == 1 && var[var.size() - 2] == 0) ||
                    (var[var.size() - 1] == 0 && var[var.size() - 2] == 1))) {
                var.pop_back();
                var.pop_back();
                symbol.pop();
                var.push_back(1);
            }
            else {
                var.pop_back();
                var.pop_back();
                symbol.pop();
                var.push_back(0);
            }
            d--;
        }
    }
    return var[0];
}

std::string    Expert::createExpression(Rule rule, char name)
{
    std::cout << "createExpression from  " << rule.left << std::endl;
    std::string expression;

    expression = "";
    for(size_t i = 0; i < rule.left.size(); i++)
    {
        int f;
        if(rule.left[i] >= 65 && rule.left[i] <= 90)
        {
            f = getFact(rule.left[i]);
            if(f == 2)
                f = getAnswer(rule.left[i], name);
            if(f == 2)
                throw "None";
            expression += std::to_string(f);
        }
        else {
            expression += rule.left[i];
        }
    }
    ///////////////////////////////////////////////////////////
    std::cout<< "Expression: " << expression << std::endl;
    return expression;
}

bool    Expert::checkListRuls(Rule rule, char search)
{
    for (size_t i = 0; i < rule.left.size(); i++)
    {
        if (rule.left[i] == search)
            return false;
    }
    for (size_t i = 0; i < rule.right.size(); i++)
    {
        if (rule.right[i] == search)
            return false;
    }
    return true;
}

std::vector<Rule>    Expert::createListOfRuleToSolve(char name, char search)
{
    std::vector<Rule> listOfRuleToSolve;

    for (size_t i = 0; i < this->rules.size(); i++)
    {
        if(this->rules[i].right.size() == 1 && this->rules[i].right[0] == name && checkListRuls(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
        else if(this->rules[i].right.size() == 2 && this->rules[i].right[0] == '!' &&
                this->rules[i].right[1] == name  && checkListRuls(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
        else if(this->rules[i].left.size() == 1 && this->rules[i].left[0] == name &&
                this->rules[i].symbol == "<=>"  && checkListRuls(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
        else if(this->rules[i].left.size() == 2 && this->rules[i].left[0] == '!' &&
                this->rules[i].left[1] == name && this->rules[i].symbol == "<=>" && checkListRuls(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
    }

    for (size_t i = 0; i < this->rules.size(); i++)
    {
        for (size_t j = 0; j < this->rules[i].right.size(); j++)
        {
            if(this->rules[i].right[j] == name && checkRule(this->rules[i], listOfRuleToSolve)  &&
                    checkListRuls(this->rules[i], search)) {
                listOfRuleToSolve.push_back(this->rules[i]);
                break ;
            }
        }
    }

    for (size_t i = 0; i < this->rules.size(); i++)
    {
        for (size_t k = 0; k < this->rules[i].left.size(); k++)
        {
            if(this->rules[i].left[k] == name && checkRule(this->rules[i], listOfRuleToSolve) &&
            this->rules[i].symbol == "<=>"  && checkListRuls(this->rules[i], search)) {
                listOfRuleToSolve.push_back(this->rules[i]);
                break ;
            }
        }
    }
    return listOfRuleToSolve;
}

bool    Expert::checkRule(Rule rule, std::vector<Rule> &listRules)
{
    for (size_t i = 0; i < rule.right.size(); i++) {
        if(!(rule.right[i] >= 65 && rule.right[i] <= 90) && rule.right[i] != '+' &&
            rule.right[i] != '(' && rule.right[i] != ')' && rule.right[i] != '!')
            return false;
    }

    for (size_t i = 0; i < listRules.size(); i++) {
        if(listRules[i].right == rule.right && listRules[i].left == rule.left)
            return false;
    }
    return true;
}
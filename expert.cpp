#include "expert.h"

Expert::Expert(){

}

Expert::~Expert() {

}

Expert &Expert::instance() {
    static Expert expert;
    return expert;
}

int     Expert::findInRule(std::string rule, char name)
{
    for (size_t i = 0; i < rule.size(); i++)
    {
        if(rule[i] == name)
            return i;
    }
    return -1;
}

char    Expert::getAnswer(char name, char search)
{
    char answer = '0';
    std::vector<Rule> listOfRuleToSolve;

    listOfRuleToSolve = createListOfRuleToSolve(name, search);

    for(size_t i = 0; i < listOfRuleToSolve.size(); i++)
    {
        int f = 0, j;
        std::string expresion;

        j = findInRule(listOfRuleToSolve[i].right, name);
        if(j >= 0)
        {
            std::cout << "Try to find \"" << name << "\" using this expression:" << std::endl;
            std::cout << listOfRuleToSolve[i].left <<
                        listOfRuleToSolve[i].symbol <<
                        listOfRuleToSolve[i].right << std::endl;
            expresion = createExpression(listOfRuleToSolve[i].left, name);
            answer = calculate(expresion);
            if(listOfRuleToSolve[i].right[j - 1] == '!')
                f = 1;
        }
        else if(int j = findInRule(listOfRuleToSolve[i].left, name) >= 0)
        {
            std::cout << "Try to find \"" << name << "\" using this expression:" << std::endl;
            std::cout << listOfRuleToSolve[i].left <<
                      listOfRuleToSolve[i].symbol <<
                      listOfRuleToSolve[i].right << std::endl;
            expresion = createExpression(listOfRuleToSolve[i].right, name);
            answer = calculate(expresion);
            if(listOfRuleToSolve[i].left[j - 1] == '!')
                f = 1;
        }

        if(answer == '0' && f)
            answer = '1';
        else if(answer == '1' && f)
            answer = '0';
        else if(answer == '2' || answer == '0')
            continue;
        else {
            break;
        }
    }
    setFact(name, answer);

    if(answer == '0' && search != '@')
        std::cout << "\"" << name << "\" is FALSE." << std::endl;
    else if(answer == '1' && search != '@')
        std::cout << "\"" << name << "\" is TRUE." << std::endl;
    return answer;
}

void    Expert::setFact(char fact, char value)
{
    for(size_t i = 0; i < this->facts.size(); i++)
    {
        if(this->facts[i].name == fact) {
            this->facts[i].value = value;
            this->facts[i].isConfirm = 1;
            break;
        }
    }
}

char     Expert::getFact(char name)
{
    for(size_t i = 0; i < this->facts.size(); i++)
    {
        if(this->facts[i].name == name) {
            if(this->facts[i].value == '1')
                std::cout << "We know that fact \"" << name << "\" is TRUE." << std::endl;
            return this->facts[i].value;
        }
    }
    return '0';
}

/*
 * 0 - low priority
 * 1 - high priority
 */
int     Expert::getPriority(char top, char e)
{
    char symbols[5] = {'^', '|', '+', '!', '('};
    int n1, n2;

    for(int i = 0; i < 5; i++)
        if(top == symbols[i])
            n1 = i;
    for(int i = 0; i < 5; i++)
        if(e == symbols[i])
            n2 = i;
    return n1 > n2 ? 0 : 1;
}

bool    Expert::isConfirm(char name)
{
    for(size_t i = 0; i < this->facts.size(); i++)
    {
        if(this->facts[i].name == name && this->facts[i].isConfirm == 1) {
            if(this->facts[i].value == '1')
                std::cout << "We know that fact \"" << name << "\" is TRUE." << std::endl;
            else if(this->facts[i].value == '0')
                std::cout << "We know that fact \"" << name << "\" is FALSE." << std::endl;
            return true;
        } else
            return false;
    }
    return false;
}

char    Expert::calculate(std::string expression)
{
    std::vector<char> output;
    std::stack<char> operations;
    std::vector<char> result;

    for(size_t i = 0; i < expression.size(); i++) {
        if(expression[i] == '1' || expression[i] == '0' || expression[i] == '2')
            output.push_back(expression[i]);
        else if(expression[i] == ')') {
            while(operations.top() != '(') {
                output.push_back(operations.top());
                operations.pop();
            }
            operations.pop();
        }
        else if((operations.size() > 0 && getPriority(operations.top(), expression[i])) || operations.size() == 0 ||
                (!getPriority(operations.top(), expression[i]) && operations.top() == '('))
            operations.push(expression[i]);
        else if(!getPriority(operations.top(), expression[i]) && operations.top() == '!') {
            if(output[output.size() - 1] == '1')
                output[output.size() - 1] = '0';
            else if(output[output.size() - 1] == '0')
                output[output.size() - 1] = '1';
            else if(output[output.size() - 1] == '2')
                output[output.size() - 1] = '2';
            operations.pop();
            operations.push(expression[i]);
        }
    }
    while (operations.size() > 0) {
        output.push_back(operations.top());
        operations.pop();
    }
    for(size_t i = 0; i < output.size(); i++)
    {
        char r;
        if(output[i] == '1' || output[i] == '0' || output[i] == '2')
            result.push_back(output[i]);
        else if(output[i] == '+')
        {
            if(result[result.size() - 1] == '1' && result[result.size() - 2] == '1')
                r = '1';
            else if(result[result.size() - 1] == '2' || result[result.size() - 2] == '2')
                r = '2';
            else
                r = '0';
            result.pop_back();
            result.pop_back();
            result.push_back(r);
        }
        else if(output[i] == '|')
        {
            if(result[result.size() - 1] == '1' || result[result.size() - 2] == '1')
                r = '1';
            else if ((result[result.size() - 1] == '2' && result[result.size() - 2] == '0') ||
                    (result[result.size() - 1] == '0' && result[result.size() - 2] == '2'))
                r = '2';
            else
                r = '0';
            result.pop_back();
            result.pop_back();
            result.push_back(r);
        }
        else if(output[i] == '^')
        {
            if((result[result.size() - 1] == '1' && result[result.size() - 2] == '0') ||
                    (result[result.size() - 1] == '0' && result[result.size() - 2] == '1'))
                r = '1';
            else if(result[result.size() - 1] == '2' || result[result.size() - 2] == '2')
                r = '2';
            else
                r = '0';
            result.pop_back();
            result.pop_back();
            result.push_back(r);
        }
        else if(output[i] == '!')
        {
            if(result[result.size() - 1] == '1')
                result[result.size() - 1] = '0';
            else if(result[result.size() - 1] == '0')
                result[result.size() - 1] = '1';
        }
    }
    return result[0];
}

std::string    Expert::createExpression(std::string rule, char name)
{
    std::string expression;
    std::string result;

    expression = "";
    result = "";
    for(size_t i = 0; i < rule.size(); i++)
    {
        char f;
        if(rule[i] >= 65 && rule[i] <= 90)
        {
            f = getFact(rule[i]);
            if(f == '2' || (f == '0' && !isConfirm(rule[i])))
                f = getAnswer(rule[i], name);
            expression += f;
        }
        else {
            expression += rule[i];
        }
    }
    for(size_t i = 0; i < expression.size(); i++)
    {
        if(expression[i] != '!' || (expression[i] == '!' && expression[i + 1] == '('))
            result += expression[i];
        else {
            if(expression[i + 1] == '1')
                result += '0';
            else if(expression[i + 1] == '0')
                result += '1';
            else
                result += '2';
            i++;
        }
    }
    return result;
}

bool    Expert::checkListRules(Rule rule, char search)
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
        if(this->rules[i].right.size() == 1 && this->rules[i].right[0] == name && checkListRules(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
        else if(this->rules[i].right.size() == 2 && this->rules[i].right[0] == '!' &&
                this->rules[i].right[1] == name  && checkListRules(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
        else if(this->rules[i].left.size() == 1 && this->rules[i].left[0] == name &&
                this->rules[i].symbol == "<=>"  && checkListRules(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
        else if(this->rules[i].left.size() == 2 && this->rules[i].left[0] == '!' &&
                this->rules[i].left[1] == name && this->rules[i].symbol == "<=>" && checkListRules(this->rules[i], search))
            listOfRuleToSolve.push_back(this->rules[i]);
    }

    for (size_t i = 0; i < this->rules.size(); i++)
    {
        for (size_t j = 0; j < this->rules[i].right.size(); j++)
        {
            if(this->rules[i].right[j] == name && checkRule(this->rules[i], listOfRuleToSolve)  &&
                    checkListRules(this->rules[i], search)) {
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
            this->rules[i].symbol == "<=>"  && checkListRules(this->rules[i], search)) {
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

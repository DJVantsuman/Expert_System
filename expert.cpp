#include "expert.h"

Expert::Expert(){

}

Expert::~Expert() {

}

Expert &Expert::instance() {
    static Expert expert;
    return expert;
}

char    Expert::getAnswer(char name, char search)
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
        try {
            if(listOfRuleToSolve[i].right.size() == 1 && listOfRuleToSolve[i].right[0] == name) {
                answer = calculate(createExpression(listOfRuleToSolve[i], name));
            }
            else if(listOfRuleToSolve[i].right.size() == 2 && listOfRuleToSolve[i].right[0] == '!' &&
                listOfRuleToSolve[i].right[1] == name) {
                answer = calculate(createExpression(listOfRuleToSolve[i], name));
                if(answer == 0)
                    answer = 1;
                else if(answer == 1)
                    answer = 0;
            }

            if(answer == '2')
                continue;
            else
                return answer;
        }
        catch (...) {
            std::cout << name << " is NONE" << std::endl;
            continue;
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

/*
 * 0 - low priority
 * 1 - high priority
 */
int     Expert::getPriorty(char top, char e)
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

int    Expert::calculate(std::string expression)
{
    std::vector<char> output;
    std::stack<char> operations;
    std::vector<char> result;

    for(size_t i = 0; i < expression.size(); i++) {
        if(expression[i] == '1' || expression[i] == '0')
            output.push_back(expression[i]);
        else if(expression[i] == ')') {
            while(operations.top() != '(') {
                output.push_back(operations.top());
                operations.pop();
            }
            operations.pop();
        }
        else if((operations.size() > 0 && getPriorty(operations.top(), expression[i])) || operations.size() == 0 ||
                (!getPriorty(operations.top(), expression[i]) && operations.top() == '('))
            operations.push(expression[i]);
        else if(!getPriorty(operations.top(), expression[i]) && operations.top() == '!') {
            if(output[output.size() - 1] == '1')
                output[output.size() - 1] = 0;
            else if(output[output.size() - 1] == '0')
                output[output.size() - 1] = 1;
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
        if(output[i] == '1' || output[i] == '0')
            result.push_back(output[i]);
        else if(output[i] == '+')
        {
            if(result[result.size() - 1] == 1 && result[result.size() - 2] == 1)
                r = '1';
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
            else
                r = '0';
            result.pop_back();
            result.pop_back();
            result.push_back(r);
        }
        else if(output[i] == '^')
        {
            if((result[result.size() - 1] == 1 && result[result.size() - 2] == 0) ||
                    (result[result.size() - 1] == 0 && result[result.size() - 2] == 1))
                r = '1';
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
            else
                result[result.size() - 1] = '1';
        }
    }
    return result[0];
}

std::string    Expert::createExpression(Rule rule, char name)
{
    std::cout << "createExpression from  " << rule.left << std::endl;
    std::string expression;
    std::string result;

    expression = "";
    result = "";
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
    for(size_t i = 0; i < expression.size(); i++)
    {
        if(expression[i] != '!' || (expression[i] == '!' && expression[i + 1] == '('))
            result += expression[i];
        else {
            if(expression[i + 1] == '1')
                result += '0';
            else
                result += '1';
            i++;
        }
    }
    ///////////////////////////////////////////////////////////
    std::cout<< "Expression: " << expression << std::endl;
    std::cout<< "Result expression: " << result << std::endl;
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
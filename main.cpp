#include "expert_system.h"

void printMan()
{
    std::cout << "This is a Man" << std::endl;
    exit(1);
}

void    findAnswer(Expert &exp)
{
    char answer;

    for (size_t i = 0; i < exp.queries.size(); i++)
    {
        answer = exp.getFact(exp.queries[i]);
        if(answer == '0')
            answer = exp.getAnswer(exp.queries[i], '@');

        if(answer == '0')
            std::cout << "\"" <<exp.queries[i] << "\" is FALSE." << std::endl;
        else if(answer == '1')
            std::cout << "\"" <<exp.queries[i] << "\" is TRUE." << std::endl;
        else if(answer == '2')
            std::cout << "It is not possible to find a solution for \"" << exp.queries[i] << "\"." << std::endl;
    }
}

int     main(int ac, char *av[])
{
    std::vector<std::string> inputData;
    Expert &exp = Expert::instance();

    if (ac != 2)
        printMan();

    try {
        inputData = Reader::instance().readFile(av[1]);
        Lexer::instance().checkInput(inputData);
        Parser::instance().parseInput(inputData, exp);

        if(exp.rules.size() == 0)
            std::cout << "ERROR: The file \"" << av[1] <<"\" does not contain any rules." << std::endl;
        else if(exp.facts.size() == 0)
            std::cout << "ERROR: The file \"" << av[1] <<"\" does not contain any facts." << std::endl;
        else if(exp.queries.size() == 0)
            std::cout << "ERROR: The file \"" << av[1] <<"\" does not contain any queries." << std::endl;
        else
            findAnswer(exp);

//        for(size_t i = 0; i < exp.rules.size(); i++) {
//            std::cout << "Rule left #" + std::to_string(i)  + " " << exp.rules[i].left << std::endl;
//            std::cout << "Rule right #" + std::to_string(i)  + " " << exp.rules[i].right << std::endl;
//            std::cout << "Rule symbol #" + std::to_string(i)  + " " << exp.rules[i].symbol << std::endl;
//        }
//
//        for(size_t i = 0; i < exp.facts.size(); i++) {
//            std::cout << "Fact " << exp.facts[i].name << "; Value " << exp.facts[i].value << std::endl;
//        }
//
//        for(size_t i = 0; i < exp.queries.size(); i++) {
//            std::cout << "Queries " <<  exp.queries[i] <<  std::endl;
//        }


    } catch (std::string msg) {
        std::cout << "ERROR: " + msg << std::endl;
        exit(1);
    } catch ( ... ) {
        std::cout << "ERROR: Chuvak, something went wrong." << std::endl;
    }

//    for (std::vector<std::string>::iterator it = inputData.begin();
//         it !=inputData.end();
//         ++it)
//        std::cout << *it << std::endl;
    return 0;
}

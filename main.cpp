#include "expert_system.h"

void printMan()
{
    std::cout << "For starting working with program you must transfer to program one parameter,\n"
                 "which is the input file. It will contain a list of rules, then a list of initial \n"
                 "facts, then a list of queries. For each of these queries, the program will tell \n"
                 "you if the query is true or false.\n"
                 "Example:\n"
                 "A + B => C # coment\n"
                 "=AB        # A and B are true\n"
                 "?C         # find C" << std::endl;

    exit(1);
}

void    findAnswer(Expert &exp)
{
    char answer;

    for (size_t i = 0; i < exp.queries.size(); i++)
    {
        std::cout << "Lets find what is fact \"" << exp.queries[i] << "\"." << std::endl;
        answer = exp.getFact(exp.queries[i]);
        if(answer == '0')
            answer = exp.getAnswer(exp.queries[i], '@');

        if(answer == '0')
            std::cout << ">>>>>>>> Answer: \"" <<exp.queries[i] << "\" is FALSE." << std::endl;
        else if(answer == '1')
            std::cout << ">>>>>>>> Answer: \"" <<exp.queries[i] << "\" is TRUE." << std::endl;
        else if(answer == '2')
            std::cout << "It is not possible to find a solution for \"" << exp.queries[i] << "\"." << std::endl;
        std::cout << std::endl;
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
    } catch (std::string msg) {
        std::cout << "ERROR: " + msg << std::endl;
        exit(1);
    } catch ( ... ) {
        std::cout << "ERROR: Chuvak, something went wrong." << std::endl;
    }
    return 0;
}

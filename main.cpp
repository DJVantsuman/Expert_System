#include "expert_system.h"

void printMan()
{
    std::cout << "This is a Man" << std::endl;
    exit(1);
}

int main(int ac, char *av[])
{
    std::vector<std::string> inputData;
    Expert &exp = Expert::instance();

    if (ac != 2)
        printMan();

    try {
        inputData = Reader::instance().readFile(av[1]);
        Lexer::instance().checkInput(inputData);
        Parser::instance().parseInput(inputData, exp);
    } catch (std::string msg) {
        std::cout << "ERROR: " + msg << std::endl;
        exit(1);
    }

//    for (std::vector<std::string>::iterator it = inputData.begin();
//         it !=inputData.end();
//         ++it)
//        std::cout << *it << std::endl;;
    return 0;
}

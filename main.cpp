#include <iostream>
#include "expert_system.h"

void printMan()
{
    std::cout << "This is a Man" << std::endl;
    exit(1);
}

int main(int ac, char *av[])
{
    std::vector<std::string> inputData;

    if (ac != 2)
        printMan();

    inputData = Reader::instance().readFile(av[1]);

    for (std::vector<std::string>::iterator it = inputData.begin();
         it !=inputData.end();
         ++it)
        std::cout << *it;
    return 0;
}

#pragma once

#include <fstream>
#include "expert_system.h"

class Reader
{
    public:
        Reader(Reader const &src) = delete;
        Reader &operator=(Reader const &rhs) = delete;
        ~Reader();
    private:
        Reader();

    public:
        static Reader &instance();
        std::vector<std::string> readFile(std::string fileName);
};

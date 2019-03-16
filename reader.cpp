#include "reader.h"

Reader::Reader() {

}

Reader::~Reader() {

}

Reader  &Reader::instance()
{
    static Reader reader;
    return reader;
}

std::vector<std::string>   Reader::readFile(std::string fileName)
{
    std::vector<std::string> inputData;
    std::string str;
    std::ifstream fin(fileName);
    if (fin.is_open()) {
        while (std::getline(fin, str))
            inputData.push_back(str);
    }
    else {
        throw "File with name \"" + fileName + "\" does not exist.";
    }

    if(inputData.empty())
        throw "File \"" + fileName + "\" is empty or does not exist.";
    return inputData;
}

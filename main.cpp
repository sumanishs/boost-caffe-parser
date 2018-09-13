#include <iostream>
#include <string>

#include "caffereader.hpp"

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cout << "Usage:" << argv[0] << " <file name>" << std::endl;
        return 1;
    }

    std::string file (argv[1]);
    CaffeReader reader;
    if(reader.Read(file)){
        std::cout << "Done...." << std::endl;
        return 0;
    }
    else {
        std::cout << "Failed...." << std::endl;
        return 1;
    }
}

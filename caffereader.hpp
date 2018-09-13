#include <iostream>
#include <string>

#include "caffeparsergrammar.hpp"


class CaffeReader {

    public:
        CaffeReader() {}
        ~CaffeReader() {}

        bool Read(std::string& filename);
};

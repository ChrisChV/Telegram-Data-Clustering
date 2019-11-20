#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include "language.h"

using namespace std;

class JsonParser{
    public:
        JsonParser();
        void printLanguages(Language * lG);
};

#endif
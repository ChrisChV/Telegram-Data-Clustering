#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include "language.h"
#include "newsDiscriminator.h"
#include "classifier.h"

using namespace std;

class JsonParser{
    public:
        JsonParser();
        void printLanguages(Language * lG);
        void printNews(NewsDiscriminator * nD);
        void printCategories(Classifier * classifier);
};

#endif
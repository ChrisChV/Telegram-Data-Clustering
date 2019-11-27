#ifndef THREADING_H
#define THREADING_H

#include <iostream>
#include "D2V.h"
#include "classifier.h"

using namespace std;

class Threading{
    public:
        Threading();
        Threading(Classifier * classifier);
        void run();
        void threadingSort();
        D2V * d2v;
        Classifier * classifier;
        vector<vector<News *>> news_threads;
        vector<News *> all_news_threads;
};

#endif
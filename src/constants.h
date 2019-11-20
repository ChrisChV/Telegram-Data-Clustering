#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

namespace Constants{
    const string configFilePath = "./tgnews.conf";
    const string meta_title = "og:title";
    const string meta_time = "article:published_time";
    const string meta_description = "og:description";
    const int defaultBatchSize = 1000;
}



#endif
#pragma once
#include <vector>
#include <tuple>
#include "../../src/News.h"
#include "../../src/constants.h"

void affinityPropagation(
    std::vector<News* > &data,
    std::vector<int> &examplar,
    int prefType = 1,
    double damping = 0.9,
    int maxit = 350,
    int convit = 25
);

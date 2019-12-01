#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <iostream>
#include <unordered_set>
#include "D2V.h"
#include "newsDiscriminator.h"

using namespace std;

class Classifier{
    public:
        Classifier();
        Classifier(NewsDiscriminator * nD);
        void runClassic();
        void getCategories();
        void getCategoriesWords();
        D2V * english_d2v;
        D2V * russian_d2v;
        map<string, vector<string>> english_categories;
        map<string, vector<string>> russian_categories;
        map<string, unordered_set<string>> english_category_words;
        map<string, unordered_set<string>> russian_category_words;
        vector<vector<News *>> categorized_news;
        map<string, int> _category_si;
        vector<string> _category_is;
        NewsDiscriminator * nD;
};

#endif
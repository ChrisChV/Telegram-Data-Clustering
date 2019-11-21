#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <iostream>
#include <unordered_set>
#include "News.h"

using namespace std;

class Language{
    public:
        Language();
        void loadWords();
        void clearData();
        void detectLanguage(News * news);
        void deleteStopWords(News * news);
        unordered_set<string> russian_words;
        unordered_set<string> english_words;
        vector<News *> english_news;
        vector<News *> russian_news;
};


#endif
#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <iostream>
#include <unordered_set>
#include "parser.h"

using namespace std;

class Language{
    public:
        Language();
        Language(Parser * parser);
        void loadWords();
        string detectLanguage(News * news);
        Parser * parser;
        unordered_set<string> russian_words;
        unordered_set<string> english_words;
        vector<News *> english_news;
        vector<News *> russian_news;
};


#endif
#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <iostream>
#include <unordered_set>
#include "News.h"
#include "../libs/langdetect/bin/include/langdetect.h"

using namespace std;
using namespace langdetect;

class Language{
    public:
        Language();
        ~Language();
        void loadWords();
        void clearData();
        bool detectLanguage(News * news);
        bool detectLanguageLib(News * news, bool otherFlag);
        void deleteStopWords(News * news);
        void deleteTitleStopWords(News * news);
        void printAll();
        unordered_set<string> russian_words;
        unordered_set<string> english_words;
        vector<News *> english_news;
        vector<News *> russian_news;
        map<string, vector<News *>> other_news;
        Detector detector;
};


#endif
#ifndef NEWSDISCRIMINATOR_H
#define NEWSDISCRIMINATOR_H

#include <iostream>
#include <unordered_set>
#include "News.h"
using namespace std;

class NewsDiscriminator{
   public:
        NewsDiscriminator();
        void discriminate(News * news);
        void loadWords();
        vector<News *> news_english_articles;
        vector<News *> news_russian_articles;
        unordered_set<string> news_english_words;
        unordered_set<string> news_russian_words;
        
};

#endif
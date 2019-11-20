#ifndef NEWSMANAGER_H
#define NEWSMANAGER_H

#include <iostream>
#include <vector>
#include "News.h"
#include "parser.h"
#include "language.h"
#include "fileManager.h"

using namespace std;

class NewsManager{
    private:
        void t_start();
        void t_end();
        clock_t _start;
        clock_t _end;
        
    public:
        NewsManager();
        NewsManager(string& option, string& dirPath);
        void start();
        void copyParseData();
        void printAllData();
        vector<News *> news_data;
        FileManager * fM;
        Language * lG;
        Parser * parser;
        string option;

};


#endif
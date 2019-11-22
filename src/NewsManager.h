#ifndef NEWSMANAGER_H
#define NEWSMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include "News.h"
#include "parser.h"
#include "language.h"
#include "fileManager.h"
#include "jsonParser.h"
#include "newsDiscriminator.h"
#include "D2V.h"
#include "classifier.h"

using namespace std;

class NewsManager{
    private:
        void t_start();
        void t_end();
        clock_t _start;
        clock_t _end;
        JsonParser jsonparser;
        
    public:
        NewsManager();
        NewsManager(string& option, string& dirPath);
        void start();
        void copyParseData();
        void printAllData();
        vector<News *> news_data;   
        FileManager * fM;
        Parser * parser;
        Language * lG;
        NewsDiscriminator * nD;
        D2V * d2v;
        Classifier * classifier;
        string option;

};


#endif
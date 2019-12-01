#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include "fileManager.h"
#include "News.h"

using namespace std;

class Parser{
    private:
        void parse(string& data, string& name);
    public:
        Parser();
        ~Parser();
        Parser(FileManager * fM);
        void parseData();
        void parseDataWithoutBatch();
        vector<News *> news_data;
        FileManager * fM;

};

#endif

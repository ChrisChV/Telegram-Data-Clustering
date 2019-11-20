#ifndef NEWS_H
#define NEWS_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;


class News{
    public:
        News();
        void saveMeta(string& property, string& content);
        void printAllData();
        vector<string> title;
        vector<string> body;
        vector<string> description;
        string _time;
        string fileName;
        map<string, string> meta_tags;
};

#endif
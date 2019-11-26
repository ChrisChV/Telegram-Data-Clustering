#ifndef NEWS_H
#define NEWS_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;


class News{
    public:
        News();
        ~News();
        void saveMeta(string& property, string& content);
        void printAllData();
        void printTitle();
        void splitTitle(string& title);
        vector<string> title;
        vector<string> body;
        vector<string> description;
        vector<float> similarityVector;
        vector<News *> news_thread;
        string _time;
        string fileName;
        string _title;
        int language;
        int category;
        int _id;
        map<string, string> meta_tags;
};

#endif
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
        void clearBody();
        vector<string> title;
        vector<string> body;
        vector<float> similarityVector;
        vector<News *> news_thread;
        string fileName;
        string _title;
        int language;
        int category;
        int _id;
};

#endif
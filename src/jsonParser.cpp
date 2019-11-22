#include <iostream>
#include "jsonParser.h"

using namespace std;

JsonParser::JsonParser(){}

void JsonParser::printLanguages(Language * lG){
    string temp = "";
    cout << "[{\"lang_code\": \"en\", \"articles\": [";
    for(auto it = lG->english_news.begin(); it != lG->english_news.end(); it++){
        temp += '\"' + (*it)->fileName + "\",";
    }
    temp.pop_back();
    cout << temp;
    cout << "]}, {\"lang_code\": \"ru\", \"articles\": [";
    temp = "";
    for(auto it = lG->russian_news.begin(); it != lG->russian_news.end(); it++){
        temp += '\"' + (*it)->fileName + "\",";
    }
    temp.pop_back();
    cout << temp;
    cout << "]}]";
}

void JsonParser::printNews(NewsDiscriminator * nD){
    string temp = "";
    cout << "{\"articles\": [";
    for(auto it = nD->news_english_articles.begin(); it != nD->news_english_articles.end(); it++){
        temp += '\"' + (*it)->fileName + "\",";
    }
    for(auto it = nD->news_russian_articles.begin(); it != nD->news_russian_articles.end(); it++){
        temp += '\"' + (*it)->fileName + "\",";
    }
    temp.pop_back();
    cout << temp;
    cout << "]}";
}

void JsonParser::printCategories(Classifier * classifier){
    string temp = "";
    cout << "[";
    int i = 0;
    for(auto it = classifier->categorized_news.begin(); 
        it != classifier->categorized_news.end(); it++){
        cout << "{\"category\": \""  << classifier->_category_is[i++];
        cout << "\", \"articles\": [";
        temp = "";
        for(auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            temp += "\"" + (*it2)->fileName + "\",";
        }
        cout << temp << "]},";
    }
    cout << "]";
}
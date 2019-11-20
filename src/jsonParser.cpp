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
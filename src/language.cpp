#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include "language.h"
#include "constants.h"

using namespace std;
using namespace langdetect;

const float OTHER_THRESHOLD = 0.95;

Language::Language(){
    this->loadWords();
}
Language::~Language(){
    this->russian_words.clear();
    this->english_words.clear();
    this->english_news.clear();
    this->english_news.shrink_to_fit();
    this->russian_news.clear();
    this->russian_news.shrink_to_fit();
}

bool Language::detectLanguage(News * news){
    int english = 0;
    int russian = 0;
    int other = 0;
    int total = news->body.size();
    for(auto it = news->body.begin(); it != news->body.end(); it++){
        if(this->english_words.find(*it) != this->english_words.end()){
            english++;
            continue;
        }
        if(this->russian_words.find(*it) != this->russian_words.end()){
            russian++;
            continue;
        }
        other++;
    }
    if(float(other) / float(total) >= OTHER_THRESHOLD){
        delete news;
        return false;
    }
    else{
        if(english >= russian){
            news->language = Constants::lang_english_value;
            this->english_news.push_back(news);
        }
        else{
            news->language = Constants::lang_russian_value;
            this->russian_news.push_back(news);
        }
    }
    return true;
}

bool Language::detectLanguageLib(News * news, bool otherFlag){
    string content = "";
    for(auto it = news->body.begin(); it != news->body.end(); it++){
        content += (*it) + " ";
    }
    string lang = detector.detect(content.c_str(), content.size()).name();
    if(lang == "en"){
        news->language = Constants::lang_english_value;
        this->english_news.push_back(news);
        return true;
    }
    else if(lang == "ru"){
        news->language = Constants::lang_russian_value;
        this->russian_news.push_back(news);
        return true;
    }
    else{
        int english = 0;
        int russian = 0;
        int other = 0;
        int total = news->body.size();
        for(auto it = news->body.begin(); it != news->body.end(); it++){
            if(this->english_words.find(*it) != this->english_words.end()){
                english++;
                continue;
            }
            if(this->russian_words.find(*it) != this->russian_words.end()){
                russian++;
                continue;
            }
            other++;
        }
        if(float(other) / float(total) >= OTHER_THRESHOLD){
            if(otherFlag){
                news->language = Constants::lang_other_value;
                if(lang.size() > 2) lang = lang.substr(0, 2);
                if(this->other_news.find(lang) == this->other_news.end()){
                    this->other_news[lang] = vector<News *>();
                }
                this->other_news[lang].push_back(news);
            }
            else delete news;
            return false;
        }
        else if(english < russian){
            news->language = Constants::lang_russian_value;
            this->russian_news.push_back(news);
            return true;
        }
        return true;
    }
}

void Language::loadWords(){
    string line = "";
    ifstream file(Constants::english_sw_path);
    while(getline(file, line)){
        this->english_words.insert(line);
    }
    file.close();
    file.open(Constants::russian_sw_path);
    while(getline(file, line)){
        this->russian_words.insert(line);
    }
    file.close();
}

void Language::clearData(){
    this->english_news.clear();
    this->russian_news.clear();
}

void Language::deleteStopWords(News * news){
    vector<string> new_vec;
    if(news->language == Constants::lang_english_value){
        for(auto it = news->body.begin(); it != news->body.end(); it++){
            if(this->english_words.find(*it) != this->english_words.end()){
                new_vec.push_back(*it);
            }
        }
    }
    else if(news->language == Constants::lang_russian_value){
        for(auto it = news->body.begin(); it != news->body.end(); it++){
            if(this->russian_words.find(*it) != this->russian_words.end()){
                new_vec.push_back(*it);
            }
        }
    }
    news->body.clear();
    news->body.shrink_to_fit();
    news->body = new_vec;
}

void Language::deleteTitleStopWords(News * news){    
    vector<string> new_vec;
    news->_title = "";
    if(news->language == Constants::lang_english_value){
        for(auto it = news->title.begin(); it != news->title.end(); it++){
            if(news->_title.size() == 0) news->_title = (*it);
            else news->_title += " " + (*it);
            if((*it).size() == 1) continue;
            (*it)[0] = tolower((*it)[0], locale("en_US.utf8"));
            if(this->english_words.find(*it) == this->english_words.end()){
                new_vec.push_back(*it);
            }
        }
    }
    else if(news->language == Constants::lang_russian_value){
        for(auto it = news->title.begin(); it != news->title.end(); it++){
            if(news->_title.size() == 0) news->_title = (*it);
            else news->_title += " " + (*it);
            if((*it).size() == 1) continue;
            if(this->russian_words.find(*it) == this->russian_words.end()){
                new_vec.push_back(*it);
            }
        }
    }    
    news->title.clear();
    news->title.shrink_to_fit();
    news->title = new_vec;
}

void Language::printAll(){
    for(auto it = this->english_news.begin(); it != this->english_news.end(); it++){
        (*it)->printTitle();
    }
    cout << "----------" << endl;
    for(auto it = this->russian_news.begin(); it != this->russian_news.end(); it++){
        (*it)->printTitle();
    }
    cout << "----------" << endl;

    for(auto it = this->other_news.begin(); it != this->other_news.end(); it++){
        for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
            (*it2)->printTitle();
        }
    }
}
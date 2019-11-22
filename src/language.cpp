#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include "language.h"
#include "constants.h"

using namespace std;

const float OTHER_THRESHOLD = 0.95;

Language::Language(){
    this->loadWords();
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
    /*
    if(english == 0 && russian == 0){
        news->language = Constants::lang_other_value;
    }
    else{
        if(english >= russian) news->language = Constants::lang_english_value;
        else news->language = Constants::lang_russian_value;
    }*/
    
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
    /*
    if(english >= russian && english >= other){
        news->language = Constants::lang_english_value;
    }
    else if(russian >= english && russian >= other){
        news->language = Constants::lang_russian_value;
    }
    else news->language = Constants::lang_other_value;*/
}

void Language::loadWords(){
    string line = "";
    ifstream file(Constants::english_words_path);
    file.close();
    /*file.open(Constants::english_words_path);
    while(getline(file, line)){
        this->english_words.insert(line);
        //cout << line << endl;
    }
    file.close();*/
    //cout << this->english_words.size() << endl;
    file.open(Constants::english_sw_path);
    while(getline(file, line)){
        this->english_words.insert(line);
    }
    file.close();
    
    /*file.open(Constants::russian_words_path);
    while(getline(file, line)){
        this->russian_words.insert(line);
    }
    file.close();*/
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
    if(news->language == Constants::lang_english_value){
        for(auto it = news->title.begin(); it != news->title.end(); it++){
            if((*it).size() == 1) continue;
            (*it)[0] = tolower((*it)[0], locale("en_US.utf8"));
            if(this->english_words.find(*it) == this->english_words.end()){
                new_vec.push_back(*it);
            }
        }
    }
    else if(news->language == Constants::lang_russian_value){
        for(auto it = news->title.begin(); it != news->title.end(); it++){
            if(this->russian_words.find(*it) == this->russian_words.end()){
                new_vec.push_back(*it);
            }
        }
    }
    news->title.clear();
    news->title.shrink_to_fit();
    news->title = new_vec;
}
#include <iostream>
#include <fstream>
#include <string>
#include "language.h"
#include "constants.h"

using namespace std;

const float OTHER_THRESHOLD = 0.95;

Language::Language(){
    this->parser = nullptr;
}
Language::Language(Parser * parser){
    this->parser = parser;
    this->loadWords();
}

string Language::detectLanguage(News * news){
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
        news->language = Constants::lang_other_value;
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
    /*
    if(english >= russian && english >= other){
        news->language = Constants::lang_english_value;
    }
    else if(russian >= english && russian >= other){
        news->language = Constants::lang_russian_value;
    }
    else news->language = Constants::lang_other_value;*/
    return to_string(english) + " " + to_string(russian) + " " + to_string(other);
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
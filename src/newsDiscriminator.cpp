#include <iostream>
#include <fstream>
#include "newsDiscriminator.h"
#include "constants.h"

using namespace std;

const int WORD_NUMBER_THRESHOLD = 40;
const float NEWS_THRESHOLD = 0.2;

NewsDiscriminator::NewsDiscriminator(){
    this->loadWords();
}

void NewsDiscriminator::loadWords(){
    ifstream file(Constants::news_english_words_path);
    string line = "";
    while(getline(file, line)){
        this->news_english_words.insert(line);
    }
    file.close();
    file.open(Constants::news_russian_words_path);
    while(getline(file, line)){
        this->news_russian_words.insert(line);
    }
    file.close();
}

bool NewsDiscriminator::discriminate(News * news){
    if(news->body.size() <= WORD_NUMBER_THRESHOLD){
        delete news;
        return false;
    }
    int news_words = 0;
    int total = news->title.size();
    if(news->language == Constants::lang_english_value){
        for(auto it = news->title.begin(); it != news->title.end(); it++){
            if(this->news_english_words.find(*it) != this->news_english_words.end()){
                news_words++;
            }
        }    
    }
    else if(news->language == Constants::lang_russian_value){
        for(auto it = news->title.begin(); it != news->title.end(); it++){
            if(this->news_russian_words.find(*it) != this->news_russian_words.end()){
                news_words++;
            }
        }    
    }
    if(float(news_words) / float(total) >= NEWS_THRESHOLD){
        if(news->language == Constants::lang_english_value){
            this->news_english_articles.push_back(news);
        }
        else if(news->language == Constants::lang_russian_value){
            this->news_russian_articles.push_back(news);
        }
        return true;
    }
    else{
        delete news;
        return false;
    } 
}
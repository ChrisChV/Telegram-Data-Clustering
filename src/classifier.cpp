#include <iostream>
#include <locale>
#include "classifier.h"
#include "constants.h"

using namespace std;


Classifier::Classifier(){
    this->english_d2v = nullptr;
    this->russian_d2v = nullptr;
    this->nD = nullptr;
}
Classifier::Classifier(NewsDiscriminator * nD){
    this->nD = nD;
    this->english_d2v = nullptr;
    this->russian_d2v = nullptr;
}

void Classifier::runD2V(){
    this->english_d2v = new D2V(this->nD->news_english_articles, true, Constants::lang_english_value);
    this->getCategories();
}

void Classifier::runClassic(){
    this->getCategories();
    this->getCategoriesWords();
    map<string, int> _temp;
    map<string, int> points;
    int max = -1;
    const string * actual_max = nullptr;

    for(auto it = this->_category_si.begin(); it != this->_category_si.end(); it++){
        _temp[it->first] = 0;
    }

    for(auto it = this->nD->news_english_articles.begin();
            it != this->nD->news_english_articles.end(); it++){
        points = _temp;
        for(auto it2 = (*it)->title.begin(); it2 != (*it)->title.end(); it2++){
            for(auto it3 = this->english_category_words.begin();
                    it3 != this->english_category_words.end(); it3++){
                if(it3->second.find(*it2) != it3->second.end()){
                    points[it3->first]++;
                }
            }
        }
        actual_max = nullptr;
        max = -1;
        for(auto it3 = points.begin(); it3 != points.end(); it3++){
            if(it3->second > 0 && it3->second > max){
                max = it3->second;
                actual_max = &it3->first;
            }
        }
        if(actual_max){
            (*it)->category = this->_category_si[*actual_max];
        }
        else (*it)->category = this->_category_si["other"];
        categorized_news[(*it)->category].push_back(*it);
    }

    for(auto it = this->nD->news_russian_articles.begin();
            it != this->nD->news_russian_articles.end(); it++){
        points = _temp;
        for(auto it2 = (*it)->title.begin(); it2 != (*it)->title.end(); it2++){
            for(auto it3 = this->russian_category_words.begin();
                    it3 != this->russian_category_words.end(); it3++){
                if(it3->second.find(*it2) != it3->second.end()){
                    points[it3->first]++;
                }
            }
        }
        actual_max = nullptr;
        max = -1;
        for(auto it3 = points.begin(); it3 != points.end(); it3++){
            if(it3->second > 0 && it3->second > max){
                max = it3->second;
                actual_max = &it3->first;
            }
        }
        if(actual_max){
            (*it)->category = this->_category_si[*actual_max];
        }
        else (*it)->category = this->_category_si["other"];
        categorized_news[(*it)->category].push_back(*it);
    }

}

void Classifier::getCategoriesWords(){
    string line = "";
    ifstream inFile(Constants::english_category_words);
    bool flag = false;
    string actual_category = "";
    while(getline(inFile, line)){
        if(line[0] == '|'){
            flag = true;
            continue;
        }
        if(flag){
            actual_category = line;
            this->english_category_words[line] = unordered_set<string>();
            this->english_category_words[line].insert(line);
            flag = false;
            continue;
        }
        else{
            this->english_category_words[actual_category].insert(line);
        }
    }
    inFile.close();
    inFile.open(Constants::russian_category_words);
    flag = false;
    while(getline(inFile, line)){
        if(line[0] == '|'){
            flag = true;
            continue;
        }
        if(flag){
            actual_category = line;
            this->russian_category_words[line] = unordered_set<string>();
            this->russian_category_words[line].insert(line);
            flag = false;
            continue;
        }
        else{
            this->russian_category_words[actual_category].insert(line);
        }
    }
    inFile.close();
}

void Classifier::getCategories(){
    string line = "";
    ifstream categoryFile(Constants::english_categories);
    bool flag = false;
    string actual_category = "";
    int actual_id = 0;
    while(getline(categoryFile, line)){
        if(line[0] == '-'){
            flag = true;
            continue;
        }
        if(flag){
            line[0] = tolower(line[0], locale("en_US.utf8"));
            actual_category = line;
            this->english_categories[line] = vector<string>();
            this->english_categories[line].push_back(line);
            this->categorized_news.push_back(vector<News *>());
            this->_category_si[line] = actual_id++;
            this->_category_is.push_back(line);
            flag = false;
            continue;
        }
        else{
            line[0] = tolower(line[0], locale("en_US.utf8"));
            this->english_categories[actual_category].push_back(line);
        }
    }
    categoryFile.close();
    this->_category_si["other"] = actual_id++;
    this->_category_is.push_back("other");
    this->categorized_news.push_back(vector<News *>());
    categoryFile.open(Constants::russian_categories);
    flag = false;
    while(getline(categoryFile, line)){
        if(line[0] == '-'){
            flag = true;
            continue;
        }
        if(flag){
            actual_category = line;
            this->russian_categories[actual_category] = vector<string>();
            this->russian_categories[actual_category].push_back(line);
            flag = false;
            continue;
        }
        else{
            this->russian_categories[actual_category].push_back(line);
        }
    }
    categoryFile.close();
}
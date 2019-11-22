#include <iostream>
#include <fstream>
#include <string>
#include "NewsManager.h"
#include "constants.h"

using namespace std;

NewsManager::NewsManager(){
    this->fM = nullptr;
    this->parser = nullptr;
    this->lG = nullptr;
    this->nD = nullptr;
}
NewsManager::NewsManager(string& option, string& dirPath){
    if(option == Constants::d2v_category_option){
        this->fM = new FileManager(dirPath, 1);
    }
    else this->fM = new FileManager(dirPath);
    this->parser = new Parser(this->fM);
    this->option = option;
    this->lG = nullptr;
    this->nD = nullptr;
}

void NewsManager::start(){
    string temp = "";
    if(option == Constants::language_option){
        this->lG = new Language();
        //this->t_start();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                this->lG->detectLanguage(*it);
                //cout << (*it)->language << " " << temp << " ";
                //(*it)->printTitle();
            }
            //this->t_end();
            //this->t_start();
        }
        this->jsonparser.printLanguages(this->lG);
    }
    else if(option == Constants::news_option){
        this->lG = new Language();
        this->nD = new NewsDiscriminator();
        //this->t_start();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            this->lG->clearData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                this->lG->detectLanguage(*it);
            }
            for(auto it = this->lG->english_news.begin(); it != this->lG->english_news.end(); it++){
                this->lG->deleteStopWords(*it);
                this->nD->discriminate(*it);
            }
            for(auto it = this->lG->russian_news.begin(); it != this->lG->russian_news.end(); it++){
                this->lG->deleteStopWords(*it);
                this->nD->discriminate(*it);
            }
            //this->t_end();
            //this->t_start();
        }
        this->jsonparser.printNews(this->nD);
    }
    else if(option == Constants::d2v_category_option){
        this->lG = new Language();
        cout << "Parsing all data" << endl;
        this->parser->parseDataWithoutBatch();
        this->fM->clearData();
        cout << "Detecting Languages" << endl;
        for(auto it = this->parser->news_data.begin(); 
                it != this->parser->news_data.end(); it++){
            if(this->lG->detectLanguage(*it)){
                this->lG->deleteTitleStopWords(*it);
            }
        }
        cout << "Init Training" << endl;
        this->d2v = new D2V(this->lG->english_news, true, Constants::lang_english_value);
        this->getCategories();
        ofstream outFile(Constants::english_category_words);
        vector<string> actual_words;
        for(auto it = this->english_categories.begin(); it != this->english_categories.end(); it++){
            outFile << "|" << endl;
            outFile << it->first << endl;
            for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
                actual_words = this->d2v->getKNNwords(*it2, 500);
                for(auto it3 = actual_words.begin(); it3 != actual_words.end(); it3++){
                    outFile << *it3 << endl;
                }
            }
        }
        outFile.close();

        auto res = this->d2v->getKNNwords("Economy", 10);
        for(auto it = res.begin(); it != res.end(); it++){
            cout << *it << endl;
        }
    }
    else{
        cout << "The option doesn't exist" << endl;
    }
}

void NewsManager::copyParseData(){
    this->news_data.insert(this->news_data.end(), 
            this->parser->news_data.begin(), this->parser->news_data.end());
}

void NewsManager::t_start(){
    this->_start = clock();
}
void NewsManager::t_end(){
    this->_end = clock();
    double time_taken = double(this->_end - this->_start) / double(CLOCKS_PER_SEC);
    cout << "Time: " << fixed << time_taken << endl;
}

void NewsManager::printAllData(){
    News * actual = nullptr;
    for(int i = 0; i < this->news_data.size(); i++){
        actual = this->news_data[i];
        actual->printAllData();
        cout << i << endl;
    }
}

void NewsManager::getCategories(){
    string line = "";
    ifstream categoryFile(Constants::english_categories);
    bool flag = false;
    string actual_category = "";
    while(getline(categoryFile, line)){
        if(line[0] == '-'){
            flag = true;
            continue;
        }
        if(flag){
            actual_category = line;
            this->english_categories[line] = vector<string>();
            this->english_categories[line].push_back(line);
            line[0] = tolower(line[0]);
            this->english_categories[line].push_back(line);
            flag = false;
            continue;
        }
        else{
            this->english_categories[actual_category].push_back(line);
            line[0] = tolower(line[0]);
            this->english_categories[actual_category].push_back(line);
        }
    }
    categoryFile.close();
}

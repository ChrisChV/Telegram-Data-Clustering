#include <iostream>
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
    this->fM = new FileManager(dirPath);
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
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
    this->d2v = nullptr;
    this->classifier = nullptr;
}

void NewsManager::start(){
    string temp = "";
    if(option == Constants::language_option){
        this->lG = new Language();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                this->lG->detectLanguageLib(*it, true);
            }
        }
        this->jsonparser.printLanguages(this->lG);
        //this->lG->printAll();
    }
    else if(option == Constants::news_option){
        this->lG = new Language();
        this->nD = new NewsDiscriminator();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            this->lG->clearData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                this->lG->detectLanguageLib(*it, true);
            }
            for(auto it = this->lG->english_news.begin(); it != this->lG->english_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
            for(auto it = this->lG->russian_news.begin(); it != this->lG->russian_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
        }
        this->jsonparser.printNews(this->nD);
    }
    else if(option == Constants::categories_option){
        this->lG = new Language();
        this->nD = new NewsDiscriminator();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            this->lG->clearData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                this->lG->detectLanguageLib(*it, true);
            }
            for(auto it = this->lG->english_news.begin(); it != this->lG->english_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
            for(auto it = this->lG->russian_news.begin(); it != this->lG->russian_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
        }
        this->classifier = new Classifier(this->nD);
        this->classifier->runClassic();
        this->jsonparser.printCategories(this->classifier);
    }
    else if(option == Constants::threads_option){
        this->lG = new Language();
        this->nD = new NewsDiscriminator();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            this->lG->clearData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                this->lG->detectLanguageLib(*it, true);
            }
            for(auto it = this->lG->english_news.begin(); it != this->lG->english_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
            for(auto it = this->lG->russian_news.begin(); it != this->lG->russian_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
        }
        this->classifier = new Classifier(this->nD);    
        this->classifier->runClassic();
        this->tH = new Threading(this->classifier);
        this->tH->run();
        this->jsonparser.printThreads(this->tH);
    }
    else if(option == Constants::top_option){
        this->lG = new Language();
        this->nD = new NewsDiscriminator();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            this->lG->clearData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                this->lG->detectLanguageLib(*it, true);
            }
            for(auto it = this->lG->english_news.begin(); it != this->lG->english_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
            for(auto it = this->lG->russian_news.begin(); it != this->lG->russian_news.end(); it++){
                this->lG->deleteTitleStopWords(*it);
                this->nD->discriminate(*it);
            }
        }
        this->classifier = new Classifier(this->nD);    
        this->classifier->runClassic();
        this->tH = new Threading(this->classifier);
        this->tH->run();
        this->tH->threadingSort();
        this->jsonparser.printTop(this->tH, this->classifier);
    }
    else if(option == Constants::d2v_category_option){
        this->lG = new Language();
        cout << "Parsing all data" << endl;
        this->parser->parseDataWithoutBatch();
        this->fM->clearData();
        cout << "Detecting Languages" << endl;
        for(auto it = this->parser->news_data.begin(); 
                it != this->parser->news_data.end(); it++){
            if(this->lG->detectLanguageLib(*it, true)){
                this->lG->deleteTitleStopWords(*it);
            }
        }
        cout << "Init English Training" << endl;
        this->d2v = new D2V(this->lG->english_news, true, Constants::lang_english_value);
        this->classifier = new Classifier();
        this->classifier->getCategories();
        ofstream outFile(Constants::english_category_words);
        vector<string> actual_words;
        for(auto it = this->classifier->english_categories.begin(); 
                it != this->classifier->english_categories.end(); it++){
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
        delete this->d2v;
        outFile.open(Constants::russian_category_words);
        this->d2v = new D2V(this->lG->russian_news, true, Constants::lang_russian_value);
        for(auto it = this->classifier->russian_categories.begin();
                it != this->classifier->russian_categories.end(); it++){
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
        actual_words.clear();
        actual_words.shrink_to_fit();
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

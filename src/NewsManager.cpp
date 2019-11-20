#include <iostream>
#include "NewsManager.h"
#include "constants.h"

using namespace std;

NewsManager::NewsManager(){
    this->fM = nullptr;
    this->parser = nullptr;
    this->lG = nullptr;
}
NewsManager::NewsManager(string& option, string& dirPath){
    this->fM = new FileManager(dirPath);
    this->parser = new Parser(this->fM);
    this->option = option;
    this->lG = nullptr;
}

void NewsManager::start(){
    string temp = "";
    if(option == Constants::language_option){
        this->lG = new Language(this->parser);
        //this->t_start();
        while(this->fM->nextBatch()){
            this->parser->parseData();
            for(auto it = this->parser->news_data.begin(); 
                    it != this->parser->news_data.end(); it++){
                temp = this->lG->detectLanguage(*it);
                //cout << (*it)->language << " " << temp << " ";
                //(*it)->printTitle();
            }
            //this->t_end();
            //this->t_start();
        }
        this->jsonparser.printLanguages(this->lG);
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
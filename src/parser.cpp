#include <iostream>
#include <fstream>
#include "parser.h"
#include "constants.h"

using namespace std;

Parser::Parser(){
    this->fM = nullptr;
}

Parser::Parser(FileManager * fM){
    this->fM = fM;
}

void Parser::parseData(){
    this->news_data.clear(); 
    for(int i = 0; i < this->fM->file_data.size(); i++){
        this->parse(this->fM->file_data[i],
             this->fM->file_names[i + this->fM->batch_size * this->fM->actual_batch]);
    }
}

void Parser::parseDataWithoutBatch(){
    this->news_data.clear();
    string name = "only_you.html";
    for(auto it = this->fM->file_data.begin(); it != this->fM->file_data.end(); it++){
        this->parse(*it, name);
    }
}

void Parser::parse(string& data, string& name){
    char c = 0;
    int state = 0;
    string tag = "";
    string option = "";
    string property = "";
    string content = "";
    string word = "";
    News * actual_news = new News();
    actual_news->fileName = name;
    //cout << data << endl;
    
    for(int i = 0; i < data.size(); i++){
        c = data[i];
        if(state == 0){
            if(c == '<'){
                state = 1;
                tag = "";
            } 
        }
        else if(state == 1){
            if(c == ' ' || c == '>'){
                if(tag == "meta"){
                    tag = "";
                    option = "";
                    state = 2;
                }
                else if(tag == "body"){
                    tag = "";
                    state = 6;
                }
                else state = 0;
                continue;
            }
            tag.push_back(c);
        }
        else if(state == 2){
            if(c == '"'){
                if(option == "property"){
                    property = "";
                    state = 3;
                }
                else if(option == "content"){
                    content = "";
                    state = 4;
                }
                else{
                    state = 5;
                } 
                continue;
            }
            else if(c == '>'){
                state = 0;
                continue;
            }
            if(c != ' ' && c != '=') option.push_back(c);
        }
        else if(state == 3){
            if(c == '"'){
                option = "";
                state = 2;
                continue;
            }
            property.push_back(c);
        }
        else if(state == 4){
            if(c == '"'){
                actual_news->saveMeta(property, content);
                state = 0;
                continue;
            }
            content.push_back(c);
        }
        else if(state == 5){
            if(c == '"'){
                option = "";
                state = 2;
            }
        }
        else if(state  == 6){
            if(c == '<'){
                tag = "";
                state = 7;
            }
        }
        else if(state == 7){
            if(c == '>'){
                if(tag == "/body"){
                    
                }
                else{
                    word = "";
                    state = 8;
                }
                continue;
            }
            tag.push_back(c);
        }
        else if(state == 8){
            if(c == ' '){
                if(word.size() > 1) actual_news->body.push_back(word);
                word = "";
                continue;
            }
            else if(c == '<'){
                if(word.size() > 1) actual_news->body.push_back(word);
                tag = "";
                word = "";
                state = 7;
                continue;
            }
            if( !(c >= 0 && c <= 31) && !(c >= 33 && c <= 47) && !(c >= 58 && c <= 64) ) {
                word.push_back(c);
            }
        }
    }
    //actual_news->printAllData();
    this->news_data.push_back(actual_news);
}

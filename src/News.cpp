#include <iostream>
#include "News.h"
#include "constants.h"

News::News(){
    this->_time = "";
    this->fileName = "";
    this->language = 0;
}

News::~News(){
    this->title.clear();
    this->title.shrink_to_fit();
    this->body.clear();
    this->body.shrink_to_fit();  
}

void News::saveMeta(string& property, string& content){
    if(property == Constants::meta_title) this->splitTitle(content);
    else if(property == Constants::meta_time) this->_time = content;
    //else if(property == Constants::meta_description) this->description.push_back(content);
}

void News::splitTitle(string& title){
    string word = "";
    char c = 0;
    for(int i = 0; i < title.size(); i++){
        c = title[i];
        if(c == ' '){
            if(word.size() != 0) this->title.push_back(word);
            word = "";
        }
        else word.push_back(c);
    }
}

void News::printAllData(){
    string word = "";
    cout << "File Name " << this->fileName << endl;
    cout << "Title: ";
    if(this->title.size() == 0) cout << "No title" << endl;
    else{
        for(int i = 0; i < this->title.size(); i++){
            word = this->title[i];
            cout << word << " ";
        }
        cout << endl;
    }
    cout << "Time: ";
    if(this->_time == "") cout << "No time" << endl;
    else cout << this->_time << endl;
    cout << "Body: " << endl;
    if(this->body.size() == 0) cout << "No body" << endl;
    else{
        for(int i = 0; i < this->body.size(); i++){
            word = this->body[i];
            cout << word << " " << endl;
            /*for(int j = 0; j < word.size(); j++){
                char c = word[j];
                int cc = int(c);
                cout << cc << " ";
            }
            cout << endl;*/
            
        }
    }
}

void News::printTitle(){
    for(int i = 0; i < this->title.size(); i++){
        cout << this->title[i] << " ";
    }
    cout << endl;
}
#include <iostream>
#include "News.h"
#include "constants.h"

News::News(){
    this->_time = "";
    this->fileName = "";
}

void News::saveMeta(string& property, string& content){
    if(property == Constants::meta_title) this->title.push_back(content);
    else if(property == Constants::meta_time) this->_time = content;
    else if(property == Constants::meta_description) this->description.push_back(content);
    else this->meta_tags[property] = content;
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
    cout << "Description " << endl;
    if(this->description.size() == 0) cout << "No description" << endl;
    else{
        for(int i = 0; i < this->description.size(); i++){
            word = this->description[i];
            cout << word << " ";
        }
        cout << endl;
    }
    cout << "Meta tags: " << endl;
    if(this->meta_tags.size() == 0) cout << "No metas" << endl;
    else{
        map<string,string>::iterator it;
        for(it = this->meta_tags.begin(); it != this->meta_tags.end(); it++){
            cout << it->first << " " << it->second << endl;
        }
    }
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
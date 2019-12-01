#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <math.h>
#include "fileManager.h"
#include "constants.h"

using namespace std;

FileManager::FileManager(){}
FileManager::FileManager(string& dirPath){
    this->batch_size = Constants::defaultBatchSize;
    this->actual_batch = -1;
    this->dirPath = dirPath;
    if(dirPath.back() != '/') dirPath.push_back('/');
    this->listFiles(dirPath);
}
FileManager::FileManager(string& dirPath, int flag){
    if(flag == 1){
        this->listFilesRecur(dirPath);
    }
}
FileManager::~FileManager(){
    this->clearData();
}

bool FileManager::nextBatch(){
    int actual_index = 0;
    this->file_data.clear();
    this->actual_batch++;
    if(this->actual_batch == ceil(this->file_names.size() / float(this->batch_size))){
        return false;
    }
    for(int i = 0; i < this->batch_size; i++){
        actual_index = i + this->batch_size * this->actual_batch;
        if(actual_index >= this->file_names.size()) break;
        this->getData(this->file_names[actual_index]);
    }
    return true;
}

void FileManager::clearData(){
    this->file_data.clear();
    this->file_data.shrink_to_fit();
    this->file_names.clear();
    this->file_names.shrink_to_fit();
}

void FileManager::loadAllData(){
    for(auto it = this->file_names.begin(); it != this->file_names.end(); it++){
        this->getData(*it);
    }
}


void FileManager::getData(string& filePath){
    ifstream file(filePath);
    this->file_data.push_back(string ((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>())));
    file.close();
}

void FileManager::getFileNumber(string& filePath, string& actual){
    char c = 0;
    bool flag = false;
    for(int i = 0; i < filePath.size(); i++){
        c = filePath[i];
        if(c == '/'){
            flag = !flag;
            actual = "";
            continue;
        }
        else if(c == '.'){
            actual += ".html";
            return;
        }
        if(flag) actual.push_back(c);
    }
}

void FileManager::getFileName(int index, string& out){
    return this->getFileNumber(this->file_names[index + this->batch_size * this->actual_batch], out);
}

void FileManager::listFiles(string & dirPath){
    struct dirent *entry;
    DIR *dir = opendir(dirPath.c_str());
    string fileName = "";

    if (dir == NULL) {
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        fileName = entry->d_name;
        if(fileName == "." || fileName == "..") continue;
        if(verifyHtmlExtension(fileName)){
            this->file_names.push_back(dirPath + "/" + fileName);
        }
        else{
            fileName = dirPath + "/" + fileName;
            this->listFiles(fileName);
        }
    }
    closedir(dir);
}


void FileManager::printActualBatch(){
    for(int i = 0; i < this->batch_size && i < this->file_names.size(); i++){
        cout << this->file_names[i + this->batch_size * this->actual_batch] << endl;
        cout << this->file_data[i];
    }
}

void FileManager::listFilesRecur(string& dirPath){
    string temp = "";
    vector<string> vec_data_dirs;
    vector<string> vec_date_dirs;
    vector<string> vec_number_dirs;
    this->listFiles(dirPath);
    vec_data_dirs = this->file_names;
    this->file_names.clear();
    for(auto it = vec_data_dirs.begin(); it != vec_data_dirs.end(); it++){
        temp = dirPath + "/" + (*it);
        this->listFiles(temp);
        vec_date_dirs = this->file_names;
        this->file_names.clear();
        for(auto it2 = vec_date_dirs.begin(); it2 != vec_date_dirs.end(); it2++){
            temp = dirPath + "/" + (*it) + "/" + (*it2);
            this->listFiles(temp);
            vec_number_dirs = this->file_names;
            this->file_names.clear();
            for(auto it3 = vec_number_dirs.begin(); it3 != vec_number_dirs.end(); it3++){
                temp = dirPath + "/" + (*it) + "/" + (*it2) + "/" + (*it3);
                this->listFiles(temp);
                this->dirPath = temp;
                cout << this->dirPath << endl;
                this->loadAllData();
                this->file_names.clear();
            }
            vec_number_dirs.clear();
        }
        vec_date_dirs.clear();
    }
}

bool FileManager::verifyHtmlExtension(string& fileName){
    bool flag = false;
    string extension = "";
    for(char c : fileName){
        if(c == '.') flag = true;
        else if(flag){
            extension.push_back(c);
        }
    }
    return extension == Constants::htmlExtension;
}

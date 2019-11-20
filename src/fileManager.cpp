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
    this->listFiles(dirPath);
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

void FileManager::getData(string& fileName){
    string filePath = this->dirPath + '/' + fileName;
    ifstream file(filePath);
    string data( (istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()) );
    this->file_data.push_back(data);
    file.close();
}

string FileManager::getFileNumber(string& filePath){
    char c = 0;
    string actual = "";
    bool flag = false;
    for(int i = 0; i < filePath.size(); i++){
        c = filePath[i];
        if(c == '/'){
            flag = !flag;
            actual = "";
            continue;
        }
        else if(c == '.') return actual;
        if(flag) actual.push_back(c);
    }
    return "";
}

void FileManager::listFiles(string& dirPath) {
    struct dirent *entry;
    DIR *dir = opendir(dirPath.c_str());
    string fileName = "";


    if (dir == NULL) {
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        fileName = entry->d_name;
        if(fileName == "." || fileName == "..") continue;
        this->file_names.push_back(fileName);
    }
    closedir(dir);
}

void FileManager::printActualBatch(){
    for(int i = 0; i < this->batch_size && i < this->file_names.size(); i++){
        cout << this->file_names[i + this->batch_size * this->actual_batch] << endl;
        cout << this->file_data[i];
    }
}
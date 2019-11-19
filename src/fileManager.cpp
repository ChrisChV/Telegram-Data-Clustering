#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include "fileManager.h"
#include "constants.h"

using namespace std;

FileManager::FileManager(string& dirPath){
    this->batch_size = Constants::defaultBatchSize;
    this->actual_batch = -1;
    this->dirPath = dirPath;
    this->listFiles(dirPath);
    this->nextBatch();
}

bool FileManager::nextBatch(){
    this->file_data.clear();
    this->actual_batch++;
    for(int i = 0; i < this->batch_size && i < this->file_names.size(); i++){
        this->getData(this->file_names[i + this->batch_size * this->actual_batch]);
    }
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
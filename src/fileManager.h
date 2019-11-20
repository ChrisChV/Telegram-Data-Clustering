#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <map>
#include <vector>
using namespace std;

class FileManager{
    private:
        string dirPath;
    public:
        FileManager();
        FileManager(string& dirPath);
        int batch_size;
        int actual_batch;
        vector<string> file_names;
        vector<string> file_data;
        bool nextBatch();
        void getData(string& filePath);
        void listFiles(string& dirPath);
        void printActualBatch();
        string getFileNumber(string& filePath);


        
};

#endif
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
        FileManager(string& dirPath, int flag);
        int batch_size;
        int actual_batch;
        vector<string> file_names;
        vector<string> file_data;
        bool nextBatch();
        void loadAllData();
        void getData(string& filePath);
        void listFiles(string& dirPath);
        void printActualBatch();
        void listFilesRecur(string& dirPath);
        void clearData();
        string getFileNumber(string& filePath);
        


        
};

#endif
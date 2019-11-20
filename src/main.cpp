#include <iostream>
#include <chrono>
#include "fileManager.h"
#include "parser.h"

using namespace std;

void printAllData(vector<News *> & data){
    News * actual = nullptr;
    for(int i = 0; i < data.size(); i++){
        actual = data[i];
        actual->printAllData();
        cout << i << endl;
    }
}

int main(int argc, char ** argv){
    string dirPath = "./data/DataClusteringSample0817/20191117/00";
    clock_t start, end;
    
    FileManager * fManager = new FileManager(dirPath);
    vector<News *> all_data;
    Parser parser(fManager);
    start = clock();
    while(fManager->nextBatch()){
        parser.parseData();
        all_data.insert(all_data.end(), parser.news_data.begin(), parser.news_data.end());
        end = clock(); 
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Time: " << fixed << time_taken << endl;
        start = clock();
    }
    //printAllData(all_data);
    return 0;
}



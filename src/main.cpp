#include <iostream>
#include <chrono>
#include "fileManager.h"

using namespace std;

int main(int argc, char ** argv){
    string dirPath = "./data/DataClusteringSample0817/20191117/00";
    clock_t start, end;
    start = clock();
    FileManager fManager(dirPath);
    //fManager.printActualBatch();
    //fManager.nextBatch();
    //fManager.printActualBatch();
    end = clock(); 
    
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time: " << fixed << time_taken << endl;
    
    return 0;
}
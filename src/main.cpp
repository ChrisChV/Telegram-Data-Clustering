#include <iostream>
#include "NewsManager.h"

using namespace std;

int main(int argc, char ** argv){
    if(argc < 3){
        cout << "Missing arguments: tgnews <option> <source_dir>" << endl;
        return 0;
    }
    string option(argv[1]);
    string dirPath(argv[2]);
    NewsManager nM(option, dirPath);
    nM.start();
    

    
    return 0;
}



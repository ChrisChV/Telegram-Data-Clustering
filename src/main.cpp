#include <iostream>
#include "NewsManager.h"
#include "../libs/doc2vec/cpp/TaggedBrownCorpus.h"
#include "../libs/doc2vec/cpp/Doc2Vec.h"

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

/*
int main(){
    Doc2Vec d2v;
    d2v.train(".d2v_data", 100, 0, 1, 0, 15, 10, 0.025, 1e-5, 4, 6);
    knn_item_t items[20];
    TaggedDocument myDoc;
    myDoc.m_word_num = 3;
    
    d2v.word_knn_words("Economy", items, 20);
    //d2v.doc_knn_docs("_*23134_Distributed_Representations_of_Sentences_and_Documents", items, 3);
    for(int i = 0; i < 20; i++){
        cout<< items[i].word << " -> " << items[i].similarity << " -> " << items[i].idx << endl;
    }
    return 0;
}
*/



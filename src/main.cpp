#include <iostream>
#include <stdarg.h>
#include <locale>
#include <string>
#include <algorithm>
#include "NewsManager.h"
#include "../libs/doc2vec/cpp/TaggedBrownCorpus.h"
#include "../libs/doc2vec/cpp/Doc2Vec.h"

using namespace std;

/*
void buildDoc(TaggedDocument * doc, ...)
{
  va_list pArg;
  va_start(pArg, doc);
  for(int i = 0; i < doc->m_word_num; i++){
    strcpy(doc->m_words[i], va_arg(pArg, char*));
  }
  va_end(pArg);
}

void buildDoc(TaggedDocument * doc, vector<string> & words){
    doc->m_word_num = words.size() + 1;
    int i = 0;
    for(; i < words.size(); i++){
        strcpy(doc->m_words[i], words[i].c_str());
    }
    strcpy(doc->m_words[i], "</s>");
}*/


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
    d2v.train(".d2v_data", 300, 1, 1, 0, 500, 10, 0.025, 1e-5, 3, 7);
    knn_item_t items[2000];
    TaggedDocument myDoc;
    float * infer_vector = NULL;
    posix_memalign((void **)&infer_vector, 128, d2v.dim() * sizeof(float)); 
    vector<string> words = {"Chile", "police", "stopped", "rescue", "workers", "helping", "dying", "protester:", "human", "rights"};
    buildDoc(&myDoc, words);
    d2v.sent_knn_docs(&myDoc, items, 20, infer_vector);


    
    //d2v.word_knn_words("economy", items, 20);
    char * word = nullptr;
    int id = 0;
    //d2v.doc_knn_docs("_*34155 sweden detains iranian suspicion murder iran", items, 3);
    for(int i = 0; i < 20; i++){
        word = items[i].word;
        word += 2;
        id = atoi(word);
        cout<< id << " -> " << items[i].similarity << " -> " << items[i].idx << endl;
    }
    return 0;
}*/

/*
int main(){
    wstring a = L"Политика";
    a[0] = towlower(a[0]);
    wcout << a << endl;
}
*/
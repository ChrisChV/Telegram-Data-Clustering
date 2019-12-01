#ifndef D2V_H
#define D2V_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdarg.h>
#include "News.h"
#include "../libs/doc2vec/cpp/Doc2Vec.h"
#include "../libs/doc2vec/cpp/TaggedBrownCorpus.h"


using namespace std;

class D2V{
    private:
        Doc2Vec d2v;
        void buildDoc(TaggedDocument * doc, vector<string> & words);
        void threadgetKNNdocs(vector<News *>* news_vec, int init, int end);
        int getId(char * word);
        int dim;
        int cbow;
        int negative;
        int hs;
        int iterations;
        int window;
        float alpha;
        float sample;
        int min_count;
        int threads;
        ofstream similarityMatrix;
    public:
        D2V();
        D2V(vector<News * >& news_vec, bool cat_flag, int language);
        void generateFile(vector<News *>& news_vec, bool cat_flag, int language);
        void addCategories(ofstream& outFile, int actual_index, int language);
        void generateSimilarityMatrix(vector<News *>& news_vec);
        vector<string> getKNNwords(string word, int k);
        void getKNNdocs(News * news, int k, int doc_id);

};

#endif
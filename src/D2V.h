#ifndef D2V_H
#define D2V_H

#include <iostream>
#include <fstream>
#include <vector>
#include "News.h"
#include "../libs/doc2vec/cpp/Doc2Vec.h"

using namespace std;

class D2V{
    private:
        Doc2Vec d2v;
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
    public:
        D2V();
        D2V(vector<News * >& news_vec, bool cat_flag, int language);
        void generateFile(vector<News *>& news_vec, bool cat_flag, int language);
        void addCategories(ofstream& outFile, int actual_index, int language);
        vector<string> getKNNwords(string word, int k);

};

#endif
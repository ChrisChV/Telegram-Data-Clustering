#include <iostream>
#include <fstream>
#include <string>
#include "D2V.h"
#include "constants.h"
#include <thread>

using namespace std;

D2V::D2V(){}
D2V::D2V(vector<News *> & news_vec, bool cat_flag, int language){
    this->generateFile(news_vec, cat_flag, language);
    this->dim = Constants::d2v_default_dim;
    this->cbow = Constants::d2v_default_cbow;
    this->hs = Constants::d2v_default_hs;
    this->negative = Constants::d2v_default_negative;
    this->iterations = Constants::d2v_default_iterations;
    this->window = Constants::d2v_default_window;
    this->alpha = Constants::d2v_default_alpha;
    this->sample = Constants::d2v_default_sample;
    this->min_count = Constants::d2v_default_min_cunt;
    this->threads = Constants::d2v_default_threads;
    this->d2v.train(Constants::d2v_data_file.c_str(), this->dim, this->cbow,
                    this->hs, this->negative, this->iterations, this->window,
                    this->alpha, this->sample, this->min_count, this->threads);
}

void D2V::generateFile(vector<News* >& news_vec, bool cat_flag, int language){
    int actual_id = 0;
    ofstream outFile(Constants::d2v_data_file);
    for(auto it = news_vec.begin(); it != news_vec.end(); it++){
        outFile << "_*" << to_string(actual_id++);
        for(auto its = (*it)->title.begin(); its != (*it)->title.end(); its++){
            outFile << " " << (*its);
        }
        outFile << endl;
    }
    if(cat_flag) this->addCategories(outFile, actual_id, language);
    outFile.close();
}

void D2V::addCategories(ofstream& outFile, int actual_id, int language){
    if(language == Constants::lang_english_value){
        ifstream testCategoriesFile(Constants::d2v_english_categories);
        string line = "";
        while(getline(testCategoriesFile, line)){
            outFile << "_*" << to_string(actual_id++) << " " << line << endl;
        }
        testCategoriesFile.close();
    }
    else if(language == Constants::lang_russian_value){
        ifstream testCategoriesFile(Constants::d2v_russian_categories);
        string line = "";
        while(getline(testCategoriesFile, line)){
            outFile << "_*" << to_string(actual_id++) << " " << line << endl;
        }
        testCategoriesFile.close();
    }
}

vector<string> D2V::getKNNwords(string word, int k){
    knn_item_t items[k];
    vector<string> res;
    this->d2v.word_knn_words(word.c_str(), items, k);
    for(int i = 0; i < k; i++){
        res.push_back(items[i].word);
    }
    return res;
}

void D2V::buildDoc(TaggedDocument * doc, vector<string> & words){
    doc->m_word_num = words.size() + 1;
    int i = 0;
    for(; i < words.size(); i++){
        strcpy(doc->m_words[i], words[i].c_str());
    }
    strcpy(doc->m_words[i], "</s>");
}

int D2V::getId(char * word){
    word += 2;
    return atoi(word);
}

void D2V::threadgetKNNdocs(vector<News *>* news_vec, int init, int end){
    int size = 0;
    if((*news_vec).size() == 1) size = 1;
    else size = (*news_vec).size() / 2;
    for(int i = init; i < end; i++){
        (*news_vec)[i]->similarityVector = vector<float>((*news_vec).size());
        this->getKNNdocs((*news_vec)[i], size, i);
    }
}


void D2V::generateSimilarityMatrix(vector<News *>& news_vec){
    thread threads[Constants::d2v_default_threads];
    int change = news_vec.size() / Constants::d2v_default_threads;
    int init = 0;
    int end = 0;
    for(int i = 0; i < Constants::d2v_default_threads; i++){
        if(i == Constants::d2v_default_threads - 1) end = news_vec.size();
        else end = init + change;
        threads[i] = thread(&D2V::threadgetKNNdocs, this, &news_vec, init, end);
        init = end;
    }

    for(int i = 0; i < Constants::d2v_default_threads; i++){
        threads[i].join();
    }

    /*
    int i = 0;
    int size = 0;
    if(news_vec.size() == 1) size = 1;
    else size = news_vec.size() / 2;
    for(auto it = news_vec.begin(); it != news_vec.end(); it++){
        (*it)->similarityVector = vector<float>(news_vec.size());
        this->getKNNdocs(*it, size, i++);
    }*/
}

void D2V::getKNNdocs(News * news, int k, int doc_id){
    int actual_id = 0;
    TaggedDocument newDoc;
    knn_item_t items[k];
    //news->similarityVector = vector<float>(k, 0);
    news->_id = doc_id;
    this->buildDoc(&newDoc, news->title);
    float * infer_vector = NULL;
    
    posix_memalign((void **)&infer_vector, 128, this->d2v.dim() * sizeof(float));
    this->d2v.sent_knn_docs(&newDoc, items, k, infer_vector);
    for(int i = 0; i < k; i++){
        actual_id = this->getId(items[i].word);
        news->similarityVector[actual_id] = items[i].similarity;
    }    
    free(infer_vector);
}

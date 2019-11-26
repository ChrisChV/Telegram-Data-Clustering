#include <iostream>
#include <fstream>
#include <string>
#include "D2V.h"
#include "constants.h"


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

void D2V::generateSimilarityMatrix(vector<News *>& news_vec){
    int i = 0;    
    for(auto it = news_vec.begin(); it != news_vec.end(); it++){
        this->getKNNdocs(*it, news_vec.size(), i++);
    }
}

void D2V::getKNNdocs(News * news, int k, int doc_id){
    int actual_id = 0;
    TaggedDocument newDoc;
    knn_item_t items[k];
    news->similarityVector = vector<float>(k, 0);
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

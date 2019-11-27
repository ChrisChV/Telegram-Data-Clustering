#include <iostream>
#include <tuple>
#include <map>
#include <algorithm>
#include "threading.h"
#include "../libs/affinity-propagation-sparse/ap.h"


using namespace std;

Threading::Threading(){
    this->classifier = nullptr;
    this->d2v = nullptr;
}
Threading::Threading(Classifier * classifier){
    this->classifier = classifier;
    this->d2v = nullptr;
}

void Threading::run(){
    vector<int> examplar;
    map<int, News *> find_examplar;
    int actual_index = 0;
    int i = 0;
    vector<float> * similarityVector;
    for(auto it = this->classifier->categorized_news.begin();
        it != this->classifier->categorized_news.end(); it++){
        this->d2v = new D2V((*it), false, 0);
        this->d2v->generateSimilarityMatrix((*it));
        affinityPropagation(*it, examplar, 3);
        this->news_threads.push_back(vector<News *>());
        actual_index = 0;
        for(auto it2 = examplar.begin(); it2 != examplar.end(); it2++){
            if(find_examplar.find(*it2) == find_examplar.end()){
                find_examplar[*it2] = (*it)[*it2];
                this->news_threads.back().push_back((*it)[*it2]);
                this->all_news_threads.push_back((*it)[*it2]);
                continue;
            }
            find_examplar[*it2]->news_thread.push_back((*it)[actual_index++]);
        }
        examplar.clear();
        find_examplar.clear();
        delete this->d2v;
        for(auto it2 = this->news_threads.back().begin(); 
            it2 != this->news_threads.back().end(); it2++){
            similarityVector = &(*it2)->similarityVector;
            sort((*it2)->news_thread.begin(), (*it2)->news_thread.end(), 
                [similarityVector](News * a, News * b){
                    return (*similarityVector)[a->_id] > (*similarityVector)[b->_id];
                });
            if((*it2)->news_thread.size() == 0){
                (*it2)->news_thread.insert((*it2)->news_thread.begin(), (*it2));
            }
        }
    }
}

void Threading::threadingSort(){
    sort(this->all_news_threads.begin(), this->all_news_threads.end(), 
            [](News * a, News * b){
                return a->news_thread.size() > b->news_thread.size();
            });
    for(auto it = this->news_threads.begin(); it != this->news_threads.end(); it++){
        sort((*it).begin(), (*it).end(), 
                [](News * a, News * b){
                    return a->news_thread.size() > b->news_thread.size();
                });
    }
}

#include <iostream>
#include "jsonParser.h"

using namespace std;

JsonParser::JsonParser(){}

void JsonParser::printLanguages(Language * lG){
    cout << "[{\"lang_code\": \"en\", \"articles\": [";
    for(auto it = lG->english_news.begin(); it != lG->english_news.end(); it++){
        cout << '\"' << (*it)->fileName << "\"";
        if(it + 1 != lG->english_news.end()) cout << ",";
    }    
    cout << "]}, {\"lang_code\": \"ru\", \"articles\": [";
    for(auto it = lG->russian_news.begin(); it != lG->russian_news.end(); it++){
        cout << '\"' << (*it)->fileName << "\"";
        if(it + 1 != lG->russian_news.end()) cout << ',';
    }
    cout << "]}";
    if(lG->other_news.size() != 0) cout << ",";
    for(auto it = lG->other_news.begin(); it != lG->other_news.end(); it++){
        cout << "{\"lang_code\": \"" << it->first << "\", \"articles\": [";
        for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
            cout << "\"" << (*it2)->fileName << "\"";
            if(it2 + 1 != it->second.end()) cout << ",";
        }
        cout << "]}";
        it++;
        if(it != lG->other_news.end()) cout << ",";
        it--;
    }
    cout << "]";
}

void JsonParser::printNews(NewsDiscriminator * nD){
    cout << "{\"articles\": [";
    for(auto it = nD->news_english_articles.begin(); it != nD->news_english_articles.end(); it++){
        cout << '\"' << (*it)->fileName << "\"";
        if(it + 1 != nD->news_english_articles.end()) cout << ",";
        else if(nD->news_russian_articles.size() != 0) cout << ",";
    }
    for(auto it = nD->news_russian_articles.begin(); it != nD->news_russian_articles.end(); it++){
        cout << '\"' << (*it)->fileName << "\"";
        if(it + 1 != nD->news_russian_articles.end()) cout << ",";
    }
    cout << "]}";
}

void JsonParser::printCategories(Classifier * classifier){
    cout << "[";
    int i = 0;
    for(auto it = classifier->categorized_news.begin(); 
        it != classifier->categorized_news.end(); it++){
        cout << "{\"category\": \""  << classifier->_category_is[i++];
        cout << "\", \"articles\": [";
        for(auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            cout << "\"" << (*it2)->fileName << "\"";
            if(it2 + 1 != (*it).end()) cout << ",";
        }
        cout << "]}";
        if(it + 1 != classifier->categorized_news.end()) cout << ",";
    }
    cout << "]";
}

void JsonParser::printThreads(Threading * threading){
    cout << "[";
    for(auto it = threading->news_threads.begin(); it != threading->news_threads.end(); it++){
        for(auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            cout << "{\"title\": \"" << (*it2)->_title << "\",";
            cout << "\"articles\": [";
            for(auto it3 = (*it2)->news_thread.begin(); it3 != (*it2)->news_thread.end(); it3++){
                cout << "\"" << (*it3)->fileName << "\"";
                if(it3 + 1 != (*it2)->news_thread.end()) cout << ",";
            }
            cout << "]}";
            if(it2 + 1 != (*it).end() || it + 1 != threading->news_threads.end()) cout << ",";
        }
    }
    cout << "]";
}

void JsonParser::printTop(Threading * threading, Classifier * classifier){
    int i = 0;
    cout << "[{\"category\": \"any\", \"threads\": [";
    for(auto it = threading->all_news_threads.begin(); it != threading->all_news_threads.end(); it++){
        cout << "{\"title\": \"" << (*it)->_title << "\",";
        cout << "\"category\": \"" << classifier->_category_is[(*it)->category] << "\",";
        cout << "\"articles\": [";
        for(auto it2 = (*it)->news_thread.begin(); it2 != (*it)->news_thread.end(); it2++){
            cout << "\"" << (*it2)->fileName << "\"";
            if(it2 + 1 != (*it)->news_thread.end()) cout << ",";
        }
        cout << "]}";
        if(it + 1 != threading->all_news_threads.end()) cout << ",";
    }
    cout << "]},";
    for(auto it = threading->news_threads.begin(); it != threading->news_threads.end(); it++){
        cout << "{\"category\": \"" << classifier->_category_is[i++] << "\",";
        cout << "\"threads\": [";
        for(auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            cout << "{\"title\": \"" << (*it2)->_title << "\",";
            cout << "\"articles\": [";
            for(auto it3 = (*it2)->news_thread.begin(); it3 != (*it2)->news_thread.end(); it3++){
                cout << "\"" << (*it3)->fileName << "\"";
                if(it3 + 1 != (*it2)->news_thread.end()) cout << ",";
            }
            cout << "]}";
            if(it2 + 1 !=  (*it).end()) cout << ",";
        }
        cout << "]}";
        if(it + 1 != threading->news_threads.end()) cout << ",";
    }
    cout << "]";
}
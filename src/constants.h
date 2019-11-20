#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

namespace Constants{
    const string russian_sw_path = "./stopwords-russian";
    const string english_sw_path = "./stopwords-english";
    const string russian_words_path = "./words_russian";
    const string english_words_path = "./words_english";
    const string configFilePath = "./tgnews.conf";
    const string meta_title = "og:title";
    const string meta_time = "article:published_time";
    const string meta_description = "og:description";
    const string language_option = "languages";
    const int defaultBatchSize = 1000;
    const int lang_other_value = 0;
    const int lang_english_value = 1;
    const int lang_russian_value = 2;
}



#endif
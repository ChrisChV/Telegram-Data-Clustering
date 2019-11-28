#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

namespace Constants{
    const string russian_sw_path = "./dictionaries/stopwords-russian";
    const string english_sw_path = "./dictionaries/stopwords-english";
    const string russian_words_path = "./dictionaries/words_russian";
    const string english_words_path = "./dictionaries/words_english";
    const string news_english_words_path = "./dictionaries/news_english_words";
    const string news_russian_words_path = "./dictionaries/news_russian_words";
    const string configFilePath = "./tgnews.conf";
    const string d2v_data_file = "./.d2v_data";
    const string d2v_similarity_file = "./.d2v_similarity_data";
    const string d2v_english_categories = "./dictionaries/test_english_category_title_news";
    const string d2v_russian_categories = "./dictionaries/test_russian_category_title_news";
    const string english_categories = "./dictionaries/english_main_category_words";
    const string russian_categories = "./dictionaries/russian_main_category_words";
    const string english_category_words = "./dictionaries/english_all_category_words";
    const string russian_category_words = "./dictionaries/russian_all_category_words";

    const string meta_title = "og:title";
    const string meta_time = "article:published_time";
    const string meta_description = "og:description";
    const string language_option = "languages";
    const string news_option = "news";
    const string categories_option = "categories";
    const string threads_option = "threads";
    const string top_option = "top";
    const string d2v_category_option = "_d2v_category";
    const int defaultBatchSize = 1000;
    const int lang_other_value = 0;
    const int lang_english_value = 1;
    const int lang_russian_value = 2;

    //const int d2v_default_dim = 1000;
    //const int d2v_default_dim = 300;
    const int d2v_default_dim = 1000;
    const int d2v_default_cbow = 1;
    const int d2v_default_hs = 1;
    const int d2v_default_negative = 0;
    //const int d2v_default_iterations = 10000;
    //const int d2v_default_iterations = 500;
    const int d2v_default_iterations = 1700;
    const int d2v_default_window = 10;
    const float d2v_default_alpha = 0.025;
    const float d2v_default_sample = 1e-5;
    const int d2v_default_min_cunt = 3;
    const int d2v_default_threads = 8;
}



#endif
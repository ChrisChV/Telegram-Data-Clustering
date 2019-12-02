#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <tuple>
#include <iostream>
#include "ap.h"
using namespace std;

// test
int main(int argc, char** argv)
{
  int prefType = 3;
  ifstream inFile("../../.d2v_similarity_data");
  vector<tuple<int,int,float>> data;
  string line = "";
  getline(inFile, line);
  int n = atoi(line.c_str());
  string a = "";
  string b = "";
  string c = "";
  int state = 0;
  char cc = 0;
  while(getline(inFile, line)){
    a.clear();
    b.clear();
    c.clear();
    state = 0;
    for(int i = 0; i < line.size(); i++){
      cc = line[i];
      if(cc == ' ') state++;
      else if(state == 0) a.push_back(cc);
      else if(state == 1) b.push_back(cc);
      else if(state == 2) c.push_back(cc);
    }
    //cout << a << " " << b << "  " << c << endl;
    data.push_back(make_tuple(atoi(a.c_str()), atoi(b.c_str()), atof(c.c_str())));
  }
  inFile.close();
  
  vector<int> examplar = affinityPropagation(data, prefType, n);
  for (size_t i = 0; i < examplar.size(); ++i) {
    printf("%d \n", examplar[i]);
  }
  puts("");
  return 0;
}

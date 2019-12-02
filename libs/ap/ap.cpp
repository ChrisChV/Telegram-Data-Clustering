// An Implementation of Affinity Propergation
// See: Clustering by Passing Messages Between Data Points

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <thread>
#include "ap.h"

using namespace std;

namespace {
  struct Edge {
    int src;      // index of source
    int dst;      // index of destination
    double s;     // similarity s(src, dst)
    double r;     // responsibility r(src, dst)
    double a;     // availability a(src, dst)

    Edge(int src, int dst, double s): src(src), dst(dst), s(s), r(0), a(0) {}
    bool operator<(const Edge& rhs) const { return s < rhs.s; }
  };

  typedef vector<Edge*> Edges;

  struct Graph {
    int n;                // the number of vertices
    Edges* outEdges;      // array of out edges of corresponding vertices
    Edges* inEdges;       // array of in edges of corresponding vertices
    vector<Edge> edges;   // all edges
  };

  // Build graph from sparse similarity matrix stored in COO format.
  // Input specification is following:
  // First line contains an integer standing for the size of the matrix.
  // Following lines each contain two integers and a real number standing for
  // the row index i, the column index j and the similarity s(i,j) respectively.
  // Input ends with an end-of-file.
  // Note that this function does not check any errors in the given input.
  // Parameter:
  //   input: Input file handle.
  //   prefType:
  //     1: use median of similarities as preference
  //     2: use minimum of similarities as preference
  //     3: use min - (max - min) of similarities as preference
  Graph* buildGraph(vector<News *> &data, int prefType)
  {
    Graph* graph = new Graph;
    //fscanf(input, "%d", &graph->n);
    graph->n = data.size();
    graph->outEdges = new Edges[graph->n];
    graph->inEdges = new Edges[graph->n];
    vector<Edge>& edges = graph->edges;

    // read similarity matrix

    
    int i = 0;
    int j = 0;
    double s = 0;
    for(auto it = data.begin(); it != data.end(); it++){
      j = 0;
      for(auto it2 = (*it)->similarityVector.begin(); it2 != (*it)->similarityVector.end(); it2++){
        //cout << "AAAA->" << *it2 << endl;
        if(i == j) continue;
        if(*it2 == 0) continue;
        edges.push_back(Edge(i, j++, *it2));
      }
      i++;
    }

    /*
    while (fscanf(input, "%d%d%lf", &i, &j, &s) != EOF) {
      if (i == j) { continue; }
      edges.push_back(Edge(i, j, s));
    }*/

    // calculate preferences
    double pref;
    if (prefType == 1) {
      sort(edges.begin(), edges.end());
      int m = edges.size();
      pref = (m % 2) ? edges[m/2].s : (edges[m/2 - 1].s + edges[m/2].s) / 2.0;
    } else if (prefType == 2) {
      pref = min_element(edges.begin(), edges.end())->s;
    } else if (prefType == 3) {
      double minValue = min_element(edges.begin(), edges.end())->s;
      double maxValue = max_element(edges.begin(), edges.end())->s;
      pref = 2*minValue - maxValue;
    } else {
      assert(false);      // invalid prefType
    }
    for (int i = 0; i < graph->n; ++i) {
      edges.push_back(Edge(i, i, pref));
    }

    for (size_t i = 0; i < edges.size(); ++i) {
      Edge* p = &edges[i];
      // add small noise to avoid degeneracies
      p->s += (1e-16 * p->s + 1e-300) * (rand() / (RAND_MAX + 1.0));
      // add out/in edges to vertices
      graph->outEdges[p->src].push_back(p);
      graph->inEdges[p->dst].push_back(p);
    }

    return graph;
  }

  void destroyGraph(Graph* graph)
  {
    delete [] graph->outEdges;
    delete [] graph->inEdges;
    delete graph;
  }

  inline void update(double& variable, double newValue, double damping)
  {
    variable = damping * variable + (1.0 - damping) * newValue;
  }

  void _updateResponsibilities(Graph* graph, double damping, int init, int end){
    for(int i = init; i < end; ++i){
      Edges& edges = graph->outEdges[i];
      int m = edges.size();
      double max1 = -HUGE_VAL, max2 = -HUGE_VAL;
      double argmax1 = -1;
      for (int k = 0; k < m; ++k) {
        double value = edges[k]->s + edges[k]->a;
        if (value > max1) { swap(max1, value); argmax1 = k; }
        if (value > max2) { max2 = value; }
      }
      // update responsibilities
      for (int k = 0; k < m; ++k) {
        if (k != argmax1) {
          update(edges[k]->r, edges[k]->s - max1, damping);
        } else {
          update(edges[k]->r, edges[k]->s - max2, damping);
        }
      }
    }
  }

  void updateResponsibilities(Graph* graph, double damping)
  {
    thread threads[Constants::d2v_default_threads];
    int change = graph->n / Constants::d2v_default_threads;
    int init = 0;
    int end = 0;
    for(int i = 0; i < Constants::d2v_default_threads; i++){
      if(i == Constants::d2v_default_threads - 1) end = graph->n;
      else end += change;
      threads[i] = thread(_updateResponsibilities, graph, damping, init, end);
      init = end;
    }
    for(int i = 0; i < Constants::d2v_default_threads; i++){
      threads[i].join();
    }
  }

  void _updateAvailabilities(Graph* graph, double damping, int init, int end){
    for (int k = init; k < end; ++k) {
      Edges& edges = graph->inEdges[k];
      int m = edges.size();
      // calculate sum of positive responsibilities
      double sum = 0.0;
      for (int i = 0; i < m-1; ++i) {
        sum += max(0.0, edges[i]->r);
      }
      // calculate availabilities
      double rkk = edges[m-1]->r;
      for (int i = 0; i < m-1; ++i) {
        update(edges[i]->a, min(0.0, rkk + sum - max(0.0, edges[i]->r)), damping);
      }
      // calculate self-availability
      update(edges[m-1]->a, sum, damping);
    }
  }

  void updateAvailabilities(Graph* graph, double damping)
  {
    thread threads[Constants::d2v_default_threads];
    int change = graph->n / Constants::d2v_default_threads;
    int init = 0;
    int end = 0;
    for(int i = 0; i < Constants::d2v_default_threads; i++){
      if(i == Constants::d2v_default_threads - 1) end = graph->n;
      else end += change;
      threads[i] = thread(_updateAvailabilities, graph, damping, init, end);
      init = end;
    }
    for(int i = 0; i < Constants::d2v_default_threads; i++){
      threads[i].join();
    }
  }

  void _updateExamplars(Graph* graph, vector<int> * examplar, bool * changed, int init, int end){
    for (int i = init; i < end; ++i) {
      Edges& edges = graph->outEdges[i];
      int m = edges.size();
      double maxValue = -HUGE_VAL;
      int argmax = i;
      for (int k = 0; k < m; ++k) {
        double value = edges[k]->a + edges[k]->r;
        if (value > maxValue) {
          maxValue = value;
          argmax = edges[k]->dst;
        }
      }
      if ((*examplar)[i] != argmax) {
        (*examplar)[i] = argmax;
        *changed = true;
      }
    }
  }

  bool updateExamplars(Graph* graph, vector<int>& examplar)
  {
    bool changed = false;
    thread threads[Constants::d2v_default_threads];
    int change = graph->n / Constants::d2v_default_threads;
    int init = 0;
    int end = 0;
    for(int i = 0; i < Constants::d2v_default_threads; i++){
      if(i == Constants::d2v_default_threads - 1) end = graph->n;
      else end += change;
      threads[i] = thread(_updateExamplars, graph, &examplar, &changed ,init, end);
      init = end;
    }
    for(int i = 0; i < Constants::d2v_default_threads; i++){
      threads[i].join();
    }
    return changed;
  }
}

// Cluster data points with Affinity Propagation.
// Parameters:
//   input: Input file which contains sparse similarity matrix. see buildGraph().
//   prefType: Specify what kind of preference we use. see buildGraph().
//   damping: The damping factor. (0.5 <= damping < 1.0)
//   maxit: The maximum number of iterations.
//   convit: Specify how many iterations this algorithm stops when examplars
//           did not change for.
// Returns:
//   Array of examplars of corresponding data points.
void affinityPropagation(vector<News *>& data, vector<int>& examplar ,int prefType, double damping, int maxit, int convit)
{
  assert(0.499 < damping && damping < 1.0);

  Graph* graph = buildGraph(data, prefType);
  examplar = vector<int>(graph->n, -1);

  for (int i = 0, nochange = 0; i < maxit && nochange < convit; ++i, ++nochange) {
    updateResponsibilities(graph, damping);
    updateAvailabilities(graph, damping);
    if (updateExamplars(graph, examplar)) { nochange = 0; }
  }
  
  destroyGraph(graph);
}

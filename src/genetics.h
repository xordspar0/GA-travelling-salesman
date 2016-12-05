#include <vector>
#include "Route.h"

using namespace std;

Route crossover(std::vector< std::vector<double> > aWE, int e, int n, Route a, Route b, vector<double> nC);
Route mutate(std::vector< std::vector<double> > aWE, int e, int n, Route a, vector<double> nC);

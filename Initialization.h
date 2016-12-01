#include <vector>
#include "Route.h"

/*
Function to generate a new route or finish a preexisting route
	aWE is the vector containing all of the edges and weights from the file
	e is the number of edges
	n is the number of nodes (currently unused)
	pR is the partially completed route. Enter an empty Route object if generating a new route
	cV is the cities visited by the partially completed route, enter an empty vector if generating new route
*/
Route generate(std::vector< std::vector<double> > aWE, int e, int n);
Route generate(std::vector< std::vector<double> > aWE, int e, int n, Route pR, vector<double> cV);
Route finish();

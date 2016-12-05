#include <cstdlib>
#include <cmath>

#include <algorithm>
#include <vector>

#include "config.h"
#include "Route.h"

using namespace std;

/*
Function to test the fitness of a vector of routes and return a vector
containing the most fit routes
*/
bool compareRoutes(Route a, Route b) {
	return (a.fitness<b.fitness);
}

vector<Route> selectBestRoutes(vector<Route> routeList) {
	int topSelection = (int)(GEN_SIZE/5);
	int randomSelection = (int)(GEN_SIZE/20);

	vector<Route> fitRoutes;

	sort(routeList.begin(), routeList.end(), compareRoutes);

	for(int i = 0; i < topSelection; i++) {
		fitRoutes.push_back(routeList[0]);
		// Prevent a route from being selected more than once.
		routeList.erase(routeList.begin());
	}

	for(int i = 0; i < randomSelection; i++) {
		int selection = fmod(rand(), routeList.size());
		fitRoutes.push_back(routeList[selection]);
		// Prevent a route from being selected more than once.
		routeList.erase(routeList.begin() + selection);
	}

	return fitRoutes;
}

#include <cmath>

#include <algorithm>
#include <vector>

#include "select.h"
#include "Route.h"

using namespace std;

double fitnessMean(vector<Route> routes) {
	double sum = 0;
	for (int i = 0; i < routes.size(); i++) {
		sum += routes[i].fitness;
	}
	return sum / routes.size();
}

double fitnessMedian(vector<Route> routes) {
	sort(routes.begin(), routes.end(), compareRoutes);
	int medianIndex = (int)(routes.size()/2);
	return(routes[medianIndex].fitness);
}

double fitnessStddev(vector<Route> routes) {
	double deviationSum = 0;
	double mean = fitnessMean(routes);

	for (int i = 0; i < routes.size(); i++) {
		deviationSum += pow(routes[i].fitness - mean, 2);
	}
	double variance = deviationSum / routes.size();
	return sqrt(variance);
}

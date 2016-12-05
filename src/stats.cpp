#include <cmath>

#include <vector>

#include "Route.h"

using namespace std;

double fitnessMean(vector<Route> routes) {
	double sum = 0;
	for (int i = 0; i < routes.size(); i++) {
		sum += routes[i].fitness;
	}
	return sum / routes.size();
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

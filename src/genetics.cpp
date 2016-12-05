#include <cstdlib>

#include <vector>

#include "generate.h"
#include "Route.h"

using namespace std;

Route crossover(std::vector< std::vector<double> > aWE, int e, int n, Route a, Route b, vector<double> nC) {
	std::vector<double> childNodeList;

	int crossPointA = std::rand() % a.nodeList.size();
	int crossPointB = std::rand() % b.nodeList.size();

	for (int i = 0; i <= crossPointA; i++) {
		childNodeList.push_back(a.nodeList[i]);
	}
	for (uint i = crossPointB; i < b.nodeList.size(); i++) {
		childNodeList.push_back(b.nodeList[i]);
	}

	Route childRoute;
	childRoute.nodeList = childNodeList;
	childRoute = generate(aWE, e, n, childRoute, nC);

	return childRoute;
}

Route mutate(std::vector< std::vector<double> > aWE, int e, int n, Route a, vector<double> nC) {
	std::vector<double> childNodeList;

	int cutPoint = std::rand() % a.nodeList.size();

	for (int i = 0; i <= cutPoint; i++) {
		childNodeList.push_back(a.nodeList[i]);
	}

	Route childRoute;
	childRoute.nodeList = childNodeList;
	childRoute = generate(aWE, e, n, childRoute, nC);

	return childRoute;
}

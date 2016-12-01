#include <stdlib.h>

#include <iostream>
#include <vector>

#include "Route.h"
#include "Initialization.h"

Route crossover(std::vector< std::vector<double> > aWE, int e, int n, Route a, Route b) {
	std::vector<int> childNodeList;

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
	childRoute = generate(aWE, e, n, childRoute);

	return childRoute;
}

Route mutate(std::vector< std::vector<double> > aWE, int e, int n, Route a) {
	std::vector<int> childNodeList;

	int cutPoint = std::rand() % a.nodeList.size();

	for (int i = 0; i <= cutPoint; i++) {
		childNodeList.push_back(a.nodeList[i]);
	}

	Route childRoute;
	childRoute.nodeList = childNodeList;
	childRoute = generate(aWE, e, n, childRoute);

	return childRoute;
}

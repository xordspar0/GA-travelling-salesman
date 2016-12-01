#include <cstdlib>
#include <vector>
#include <iostream>
#include "Route.h"

Route crossover(Route a, Route b) {
	std::vector<int> childNodeList;

	int crossPointA = std::rand() % a.nodeList.size();
	int crossPointB = std::rand() % b.nodeList.size();

	for (int i = 0; i <= crossPointA; i++) {
		childNodeList.push_back(a.nodeList[i]);
	}
	for (int i = crossPointB; i < b.size(); i++) {
		childNodeList.push_back(b.nodeList[i]);
	}

	// Route childRoute = genRoute(child);

	return childRoute;
}

Route mutate(Route a) {
	std::vector<int> childNodeList;

	int cut_point = std::rand() % a.nodeList.size();

	for (int i = 0; i <= cross_point_a; i++) {
		childNodeList.push_back(a.nodeList[i]);
	}

	// Route childRoute = genRoute(child);

	return childRoute;
}

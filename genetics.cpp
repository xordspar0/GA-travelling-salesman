#include <cstdlib>
#include <vector>
#include <iostream>

std::vector<int> crossover(std::vector<int> a, std::vector<int> b) {
	std::vector<int> child;

	int cross_point_a = std::rand() % a.size();
	int cross_point_b = std::rand() % b.size();

	for (int i = 0; i <= cross_point_a; i++) {
		child.push_back(a[i]);
	}
	for (int i = cross_point_b; i < b.size(); i++) {
		child.push_back(b[i]);
	}

	// gen_route(child);

	return child;
}

std:vector<int> mutate(std::vector<int> a) {
	int cut_point = std::rand() % a.size();

	for (int i = 0; i <= cross_point_a; i++) {
		child.push_back(a[i]);
	}

	// gen_route(child);

	return child;
}

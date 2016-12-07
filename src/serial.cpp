#include <cmath>
#include <sys/stat.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include "config.h"
#include "generate.h"
#include "genetics.h"
#include "select.h"
#include "stats.h"
#include "Route.h"

using namespace std;

int main(int argc, char* argv[])
{
	//generate random seed
	srand(time(0));

	//open file
	fstream inputFile;
	struct stat buf;
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " network_filename" << endl;
		return 1;
	} else if (stat(argv[1], &buf) == -1) {
		cout << "File not found: " << argv[1];
		return 2;
	} else {
		inputFile.open(argv[1], std::ios::in);
	}

	/*
	variables u, v, and w used for file input
	totalWeight is used to get the total weight of all the edges
	*/
	double u, v, w, totalWeight = 0;

	//vector that stores edges from file
	vector< vector<double> > allWeightedEdges;

	vector<double> nCount;
	vector<double>::iterator it;

	//loop transfers file data to vector
	int EDGES = 0;
	while(inputFile >> u >> v >> w)
	{
		EDGES++;
		allWeightedEdges.push_back( {u,v,w} );
		totalWeight += w;

		it = find(nCount.begin(), nCount.end(), u);
		if(it == nCount.end())
		{
			nCount.push_back(u);
		}
		it = find(nCount.begin(), nCount.end(), v);
		if(it == nCount.end())
		{
			nCount.push_back(v);
		}
	}

	int NODES = nCount.size();
	cout << "Total number of nodes: " << NODES << endl;
	cout << "Total number of edges: " << EDGES << endl;
	cout << "Total weight of edges: " << totalWeight << endl;

	//route object generated here
	//Route r1 = generate(allWeightedEdges, EDGES, NODES, nCount);

	//cout<< "Route weight: " << r1.fitness << endl;

	vector<Route> routeVector;

	for(int i = 0; i<GEN_SIZE ; i++)
	{
		routeVector.push_back(generate(allWeightedEdges, EDGES, NODES, nCount));
	}

	vector<Route> fitVector;
	fitVector = selectBestRoutes(routeVector);
	double mean;
	double stdev;

	for(int i = 0; i<GEN_NO; i++)
	{
		routeVector.clear();
		for(int j = 0; j < GEN_SIZE; j++)
		{
			if(rand()%MUTATION_FRACTION == 1)
			{
				routeVector.push_back
					(mutate(allWeightedEdges, EDGES, NODES, fitVector[fmod(rand(), fitVector.size())], nCount));
			}
			else
			{
				routeVector.push_back
					(crossover(allWeightedEdges, EDGES, NODES,
					fitVector[fmod(rand(), fitVector.size())], fitVector[fmod(rand(), fitVector.size())], nCount));
			}
		}

		cout << "Generation #" << i << endl;
		cout << "Median: " << fitnessMedian(routeVector) << endl;
		cout << "Standard deviation: " << fitnessStddev(routeVector) << endl;
		cout << "Selected parents:" << endl;
		fitVector = selectBestRoutes(routeVector);
		for(int i = 0; i < fitVector.size(); i++)
		{
			cout << "\tVector # " << i << " Weight: " << fitVector[i].fitness << endl;
		}

	}

	cout << endl;
	//cout << "BEST ROUTE WEIGHT: " << fitVector[0] << endl;

	return 0;
}

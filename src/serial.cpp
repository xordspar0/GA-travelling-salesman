#include <cmath>

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

int main()
{
	//generate random seed
	srand(time(0));

	//constant for # of edges in file (676 in small)(9824 in large)
	const int EDGES = 676;
	//constant for # of nodes in file (269 in small)(3917 in large)
	const int NODES = 269;

	//open file
	fstream inputFile;
	inputFile.open ("data/network-small.txt", std::ios::in);

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
	while(inputFile >> u >> v >> w)
	{
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

	cout << "Total weight of edges: " << totalWeight << endl;

	cout << "Total nodes: " << nCount.size() << endl;

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

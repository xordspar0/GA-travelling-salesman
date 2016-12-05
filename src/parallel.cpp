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

vector<Route> routeVector;
int generated;

pthread_mutex_t routevectormutex;
pthread_mutex_t generatedmutex;

void threadFunc(vector< vector<double> > aWE, int e, int n, vector<Route> fV, vector<double> nC)
{
	while (generated < GEN_SIZE) {
		pthread_mutex_lock(&generatedmutex);
		generated++;
		pthread_mutex_unlock(&generatedmutex);

		Route temp;

		if(rand()%MUTATION_FRACTION == 1)
		{
			temp = mutate(aWE, e, n, fV[fmod(rand(), fV.size())], nC);
		}
		else
		{
			temp = crossover(aWE, e, n,
				fV[fmod(rand(), fV.size())], fV[fmod(rand(), fV.size())], nC);
		}

		pthread_mutex_lock(&routevectormutex);
		routeVector.push_back(temp);
		pthread_mutex_unlock(&routevectormutex);
	}
}

int main()
{
	//generate random seed
	srand(time(0));

	pthread_mutex_init(&routevectormutex, NULL);
	pthread_mutex_init(&generatedmutex, NULL);

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

	for(int i = 0; i<GEN_SIZE ; i++)
	{
		routeVector.push_back(generate(allWeightedEdges, EDGES, NODES, nCount));
	}

	vector<Route> fitVector;
	fitVector = selectBestRoutes(routeVector);
	double mean;
	double stdev;

	thread workerThreads[NUMTHREADS];

	for(int i = 0; i<GEN_NO; i++)
	{
		routeVector.clear();
		generated = 0;
		for(int j = 0; j < NUMTHREADS; j++)
		{
			workerThreads[j] = thread(threadFunc,
				allWeightedEdges,  EDGES,  NODES,  fitVector,  nCount);
		}

		for(int j = 0; j < NUMTHREADS; j++)
		{
			workerThreads[j].join();
		}
		cout << "Generation #" << i << endl;
		cout << "Mean: " << fitnessMean(routeVector) << endl;
		cout << "Standard deviation: " << fitnessStddev(routeVector) << endl;
		cout << "Selected parents:" << endl;
		fitVector = selectBestRoutes(routeVector);
		for(int i = 0; i < fitVector.size(); i++)
		{
			cout << "\tVector # " << i << " Weight: " << fitVector[i].fitness << endl;
		}

	}

	cout << endl;

	return 0;
}

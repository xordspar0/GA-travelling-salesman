#include <cstdlib>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Initialization.h"
#include "Route.h"
#include "config.h"


using namespace std;

/*
Function to generate a new route or finish a preexisting route
	aWE is the vector containing all of the edges and weights from the file
	e is the number of edges
	n is the number of nodes (currently unused)
	pR is the partially completed route. Enter an empty Route object if generating a new route
	cV is the cities visited by the partially completed route, enter an empty vector if generating new route
*/
Route generate(vector< vector<double> > aWE, int e, int n, Route pR, vector<double> nC)
{

	double currentCity, totalWeight;

	int currentEdge, ccIndex, noVisited, currentCityEdges;

	vector<double> citiesVisited;
	vector<double> nList;

	vector<double>::iterator it;

	Route outputRoute;

	/*
	if a partially complete route is passed to the function,
	citiesVisited is set equal to that vector, noVisited is
	set to the size of that vector, and totalWeight is set
	to the total weight of that route
	*/
	//citiesVisited.swap(cV);

	//totalWeight = pR.weight;
	nList.swap(pR.nodeList);

	//initial edge randomly selected here
	if(nList.size() == 0)
	{
		currentEdge = rand()%676;
		//currentEdge = 38;
		//first two cities added to citiesVisited and nList vectors
		citiesVisited.push_back(aWE[currentEdge][0]);
		citiesVisited.push_back(aWE[currentEdge][1]);
		nList.push_back(aWE[currentEdge][0]);
		nList.push_back(aWE[currentEdge][1]);
		totalWeight += aWE[currentEdge][2];
	}
	//if a partial route is present, the initial edge is found here
	else
	{
		for(int i = 0; i < nList.size(); i++)
		{
			for(int j = 0; j<aWE.size(); j++)
			{
				if(aWE[j][0] == nList[nList.size()-2] && aWE[j][1] == nList[nList.size()-1])
				{
					//the current edge is the last two elements in the nList vector
					currentEdge = j;
					totalWeight += aWE[j][2];
				}
				else if(aWE[j][0] == nList[i] && aWE[j][1] == nList[i+1])
				{
					totalWeight += aWE[j][2];
				}
			}
		}

		for(int i = 0; i<nList.size(); i++)
		{
			it = find(citiesVisited.begin(), citiesVisited.end(), nList[i]);
			if(it == citiesVisited.end())
			{
				//cities visited by preexisting route are put into citiesVisited vector
				citiesVisited.push_back(nList[i]);
			}
		}
	}

	noVisited = citiesVisited.size();

	//current city set
	currentCity = aWE[currentEdge][1];


	while(noVisited < n)
	{
		//if statement imposes a hard weight cap on loop
		if(totalWeight >= 1000000.0)
		{
			break;
		}

		currentCityEdges = 0;
		ccIndex = 0;
		bool indexFound = false;

		//get edges for current city here
		for(int i = 0; i<aWE.size(); i++)
		{
			if(aWE[i][0] == currentCity)
			{
				if(indexFound == false)
				{
					ccIndex = i;
					indexFound = true;
				}
				currentCityEdges++;
			}
		}

		//one of the edges of the current city is randomly chosen here
		currentEdge = fmod(rand(), currentCityEdges) + ccIndex;

		//the newest city is added to the nodeList
		nList.push_back(aWE[currentEdge][1]);

		//add weight of edge to totalWeight
		totalWeight += aWE[currentEdge][2];

		//set currentCity to the city to which we are travelling
		currentCity = aWE[currentEdge][1];


		noVisited = citiesVisited.size();

		/*
		loop checks if the new currentCity is in the citiesVisited
		vector. If it isn't, it's added to the vector and noVisited
		is incremented by one
		*/
		//consider replacing with std::find
		for(int i = 0; i<=noVisited; i++)
		{
			if(citiesVisited[i] == currentCity)
			{
				//cout<<"City already present"<<endl;
				break;
			}
			else if(i == noVisited)
			{
				citiesVisited.push_back(currentCity);
				//noVisited++;
			}
		}

		//cout<<"City: "<<currentCity<<" Cities Visited: "<<noVisited<<endl;
	}

	sort(citiesVisited.begin(),citiesVisited.end());
	sort(nC.begin(), nC.end());
	vector<double> diff;
	set_symmetric_difference(citiesVisited.begin(), citiesVisited.end(), nC.begin(), nC.end(), back_inserter(diff));

	for(int i = 0; i<diff.size(); i++)
	{
		cout<< "Missing: " << diff[i] << endl;
	}


	//nodeList and total weight of route are added to the Route object
	outputRoute.nodeList.swap(nList);
	outputRoute.weight = totalWeight;

	//cout<<"Route complete"<<endl;
	return outputRoute;

}

Route generate(vector< vector<double> > aWE, int e, int n, vector<double> nC) {
	vector<double> emptyVector;
	Route emptyRoute;

	return generate(aWE, e, n, emptyRoute, nC);
}

/*
Function to test the fitness of a vector of routes and return a vector
containing the most fit routes
*/
bool compareRoutes(Route a, Route b)
{
	return (a.weight<b.weight);
}

vector<Route> testFitness(vector<Route> routeList)
{

	//const double GEN_SIZE = routeList.size();

	int topSelection = (int)(GEN_SIZE/5);
	int randomSelection = (int)(GEN_SIZE/20);

	vector<Route> fitVector;

	sort(routeList.begin(), routeList.end(), compareRoutes);

	for(int i = 0; i < topSelection; i++)
	{
		fitVector.push_back(routeList[0]);
		routeList.erase(routeList.begin());
	}

	for(int i = 0; i < randomSelection; i++)
	{
		int selection = fmod(rand(), routeList.size());
		fitVector.push_back(routeList[selection]);
		routeList.erase(routeList.begin() + selection); // Prevent a route from being selected more than once.
	}

	return fitVector;

}







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

double fitnessMean(vector<Route> routes) {
	double sum = 0;
	for (int i = 0; i < routes.size(); i++) {
		sum += routes[i].weight;
	}
	return sum / routes.size();
}

double fitnessStddev(vector<Route> routes) {
	double deviationSum = 0;
	double mean = fitnessMean(routes);

	for (int i = 0; i < routes.size(); i++) {
		deviationSum += pow(routes[i].weight - mean, 2);
	}
	double variance = deviationSum / routes.size();
	return sqrt(variance);
}

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

	//cout<< "Route weight: " << r1.weight << endl;

	vector<Route> routeVector;

	for(int i = 0; i<GEN_SIZE ; i++)
	{
		routeVector.push_back(generate(allWeightedEdges, EDGES, NODES, nCount));
	}

	vector<Route> fitVector;
	fitVector = testFitness(routeVector);
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
		cout << "Mean: " << fitnessMean(routeVector) << endl;
		cout << "Standard deviation: " << fitnessStddev(routeVector) << endl;
		cout << "Selected parents:" << endl;
		fitVector = testFitness(routeVector);
		for(int i = 0; i < fitVector.size(); i++)
		{
			cout << "\tVector # " << i << " Weight: " << fitVector[i].weight << endl;
		}

	}

	cout << endl;
	//cout << "BEST ROUTE WEIGHT: " << fitVector[0] << endl;

	return 0;
}

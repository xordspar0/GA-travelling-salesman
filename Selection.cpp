#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>
#include <algorithm>

#include "Route.h"

using namespace std;

bool compareRoutes(Route a, Route b)
{
	return (a.weight<b.weight);
}

vector<Route> testFitness(vector<Route> routeList)
{
	
	const double GEN_SIZE = routeList.size();
	
	int topSelection = (int)(GEN_SIZE/5);
	int randomSelection = (int)(GEN_SIZE/20);
	
	vector<Route> fitVector;
	
	sort(routeList.begin(), routeList.end(), compareRoutes);
	
	for(int i = 0; i < topSelection; i++)
	{
		fitVector.push_back(routeList[i]);
	}
	
	for(int i = 0; i < randomSelection; i++)
	{
		fitVector.push_back(routeList[fmod(rand(), routeList.size())]);
	}
	
	return fitVector;
	
}

int main()
{
	
	srand(time(0));
	
	vector<Route> testVector;
	vector<Route> fitVector;
	Route temp;
	
	for(int i = 0; i < 50; i++)
	{
		temp.weight = fmod(rand(), 100.0);
		testVector.push_back(temp);
		cout<< temp.weight<<endl;
	}
	
	fitVector = testFitness(testVector);
	
	for(int i = 0; i < fitVector.size(); i++)
	{
		cout << "Vector # " << i << " Weight: " << fitVector[i].weight << endl;
	}
	
	return 0;
	
}
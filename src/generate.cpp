#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>

#include "config.h"
#include "Route.h"

using namespace std;

/*
Function to generate a new route or finish a preexisting route
	aWE is the vector containing all of the edges and weights from the file
	e is the number of edges
	n is the number of nodes (currently unused)
	pR is the partially completed route. Enter an empty Route object if generating a new route
	cV is the cities visited by the partially completed route, enter an empty vector if generating new route
*/
Route generate(vector< vector<double> > aWE, int e, int n, Route pR, vector<double> nC) {
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
	nList.swap(pR.nodeList);

	//initial edge randomly selected here..
	if(nList.size() == 0)
	{
		currentEdge = rand()%676;
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
		if(totalWeight >= FITNESS_CAP)
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
	outputRoute.fitness = totalWeight;

	return outputRoute;
}

Route generate(vector< vector<double> > aWE, int e, int n, vector<double> nC) {
	vector<double> emptyVector;
	Route emptyRoute;

	return generate(aWE, e, n, emptyRoute, nC);
}

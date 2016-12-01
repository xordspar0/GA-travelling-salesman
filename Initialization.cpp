#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>
#include <algorithm>

//#include <Route.h>


using namespace std;

class Route
{
	public:
		vector<double> nodeList;
		double weight;
};

/*
Function to generate a new route or finish a preexisting route
	aWE is the vector containing all of the edges and weights from the file
	e is the number of edges
	n is the number of nodes (currently unused)
	pR is the partially completed route. Enter an empty Route object if generating a new route
	cV is the cities visited by the partially completed route, enter an empty vector if generating new route
*/
Route generate(vector< vector<double> > aWE, int e, int n, Route pR, vector<double> cV)
{
	
	double currentCity, totalWeight;
	
	int currentEdge, ccIndex, noVisited, currentCityEdges;
	
	vector<double> citiesVisited;
	vector<double> nList;
	
	Route outputRoute;
	
	/*
	if a partially complete route is passed to the function, 
	citiesVisited is set equal to that vector, noVisited is
	set to the size of that vector, and totalWeight is set 
	to the total weight of that route
	*/
	citiesVisited = cV;
	noVisited = citiesVisited.size();
	totalWeight = pR.weight;
	nList.swap(pR.nodeList);
	
	//initial edge randomly selected here
	currentEdge = rand()%675;
	
	//first two cities are added to citiesVisited array here
	citiesVisited.push_back(aWE[currentEdge][0]);
	citiesVisited.push_back(aWE[currentEdge][1]);
	nList.push_back(aWE[currentEdge][0]);
	nList.push_back(aWE[currentEdge][1]);
	currentCity = aWE[currentEdge][1];
	totalWeight += aWE[currentEdge][2];
	
	/*
	the condition for this loop should be (noVisited < n), where n is the number of nodes
	however, the program constantly hits the totalWeight hard cap when that is the case. 
	*/
	while(noVisited < 258)
	{
		//if statement imposes a hard weight cap on loop
		if(totalWeight >= 100000.0)
		{
			break;
		}
		
		currentCityEdges = 0;
		ccIndex = 0;
		
		//get edges for current city here
		for(int i = 0; i<aWE.size(); i++)
		{
			if(aWE[i][0] == currentCity)
			{
				if(ccIndex != (i-1))
					ccIndex = i;
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
		
		cout<<"City: "<<currentCity<<" Cities Visited: "<<noVisited<<endl;
	}
	
	//nodeList and total weight of route are added to the Route object
	outputRoute.nodeList.swap(nList);
	outputRoute.weight = totalWeight;
	
	return outputRoute;
	
}

//function to complete a partial route
//currently the generate route is also designed to handle this functionality
Route finish()
{
	//take an incomplete route and complete it
}



int main()
{
	//generate random seed
	srand(time(0));
	
	//constant for # of edges in file
	const int EDGES = 676;
	//constant for # of nodes in file
	const int NODES = 269;
	
	//open file
	fstream inputFile;
	inputFile.open ("network-small.txt", std::ios::in);
	
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
	vector<double> emptyVector;
	Route emptyRoute;
	Route r1 = generate(allWeightedEdges, EDGES, NODES, emptyRoute, emptyVector);
	
	cout<< "Route weight: " << r1.weight << endl;
	
	return 0;
}
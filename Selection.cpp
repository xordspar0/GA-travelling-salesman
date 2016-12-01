// Franklin Slaby

//Fitness Determination

#include <stdio.h>
#include <iostream>
#include <vector>

int main()
{
	//vector of routes
	std::vector<pair<double, double>> tempRoute;
	std::vector<pair<double, double>> selectedRoutes;
	std::vector<pair<double, double>> minVector;
	
	//minimum variable
	double minWeight = 0;
		
	//calculate 20% of the vector
	int topSelection = GEN_SIZE/5;

	// calculate 5% of the vector	
	int randomSelection = GEN_SIZE/20;

	//Look at a route
	for (int i = 0, i < GEN_SIZE, i++)
		{
			//add route to temporary list
			tempRoute.push_back(make_pair(routes[i].cityList, routes[i].weight));
	
		}
	//grab 20% of routes
	for (int j = 0, j < topSelection, j++)
		{
			//sort through to find best scores
			for (int e = 0, e < GEN_SIZE, e++)
			{
				//find best scores (smallest weights)
				if (minWeight == 0 || minweight > tempRoute[j].second)
				{				
					minVector.clear();
					minWeight = tempRoute[j].second;
					minVector.push_back(make_pair(tempRoute[j].first, tempRoute[j].second));
				}
			}
			//add route to vector or array of top 
			selectedRoutes.push_back(make_pair(minVector[j].first, minVector[j].second));
			
			//remove route from list of route to be examined
		
		
			//reset minimum
			minWeight = 0;
		}
	
		for (int k = 0, k < randomSelection, k++)
		{
			//randomly select a number
			
			//
			
			
			
		}
}
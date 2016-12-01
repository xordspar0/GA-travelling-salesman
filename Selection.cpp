// Franklin Slaby

//Fitness Determination

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//variable to erase element
	int eraseVariable;
	
	//vector of routes
	vector<pair<double, double>> tempRoute;
	vector<pair<double, double>> selectedRoutes;
	vector<pair<double, double>> minVector;
	vector<double> removedList;
	
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
			for (int e = 0, e < tempRoute.size(), e++)
			{

				//find best scores (smallest weights)
				if (minWeight == 0 || minweight > tempRoute[e].second)
				{				
					//if new minimum is found clear list and set values
					minVector.clear();
					minWeight = tempRoute[e].second;
					minVector.push_back(make_pair(tempRoute[e].first, tempRoute[e].second));
					eraseValue = e - 1;
				}
				
			}
			
			//add route to vector or array of top 
			selectedRoutes.push_back(make_pair(minVector[0].first, minVector[0].second));
			
			//remove route from list of route to be examined
			tempRoute.erase (tempRoute.begin() + eraseVariable);
		
			//reset minimum
			minWeight = 0;
		}
	
		for (int k = 0, k < randomSelection, k++)
		{
			//randomly select a number
			randomSelection = rand() % tempRoute.size();
			randomValueErase = randomSelection - 1;
			
			//Add random route to selection list
			selectedRoutes.push_back(make_pair(tempRoute[randomSelection].first, tempRoute[randomSelection].second));
			
			//remove random routes
			tempRoute.erase (tempRoute.begin() + randomValueErase);			
			
		}
}
Genetic algorithm for solving the travelling salesman problem

1.	Make a list of cities to use in our tests. Pick, say, 100 US cities.
2.	Make a dataset containing pairs of cities and the distance between those
	pairs.
3.	Use the genetic algorithm to find the best route.
	a.	Test each route in parallel.
	b.	Do the route modification in parallel.

Open questions:

*	How should we combine routes? Do we use the top 10%? 1%? Do we splice these
	routes together at random? Do we swap individual cities?
*	How should we implement the parallel portion? GPU? Threads? MPI?

To do:

*	For our initial presentation, prepare the network database with the weights
	between cities.
	*	Figure out how to use the Google APIs to get that information for us.

Our data is the roadNet-TX.txt dataset from snap.stanford.edu

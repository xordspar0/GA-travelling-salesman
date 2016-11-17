Genetic algorithm for solving the travelling salesman problem

We have some networks. Our goal is to visit every node in the network
using the
shortest path possible. We will be using large networks where the
search space
for the best path is too large to try every possible route. To find an
optimal
route, we will be using a genetic algorithm.

Process
-------

1.	Randomly generate a list of routes. These routes are simply generated by shuffling the list of nodes.

2.	Run a fitness test on each route that finds the length of the route.

3.	With the results from step two combine and splice the routes together to create a more favored route.

4.	Go back to step two and run until the optimal route is found.

Open questions:
---------------

*	How should we combine routes? Do we use the top 10%? 1%? Do we splice these
	routes together at random? Do we swap individual cities?
	
*	How should we implement the parallel portion? GPU? Threads? MPI?
	*	*We're planning to use threads now.*

To do:
------

* [x]	Implement a randomly generated system to give weights to routes.
* [ ]	Implement an algorithm to generete candidate routes.
	*	Routes that are significantly worse than the average for the previous generation should be killed off before they finish.
* [ ]	Implement the genetic part of the algorithm: combine and mutate the best routes to make the next generation.
* [ ]	Parallelize route generation.
* [ ]	Parallelize combining and splicing.
* [ ]   Write a 5 to 10 page paper describing the project.

	*	Part One:
		Describe Genetic Algorithims.

	*	Part Two:
		Describe the Traveling Salesman problem.

	*	Part Three:
		Describe project results.
		
Our data is the roadNet-TX.txt dataset from snap.stanford.edu

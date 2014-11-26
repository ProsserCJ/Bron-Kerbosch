/*
	Chris Prosser, Laura Wendlendt, Eric Weaver, Michael Wiegand
	Interface of the Bron-Kerbosch class
	COMP 442 -- Introduction to Algorithms
	Project 2	
*/

#ifndef __BRON
#define __BRON

#include <set>
#include <vector>
using namespace std;

class BronKerbosch
{
public:
	BronKerbosch(char* file);
	
	//Initialize parameters and call recursive function
	void run();
	
	//Print calculated maximal cliques
	void print();

	//Run several tests and print asymptotic analysis
	void analyze(int trials);

private:
	vector<vector<int>> graph;
	set<set<int>> maxCliques;
	long long start, end;

	//Recursive backtracking function
	void backtrack(set<int> R, set<int> P, set<int> X);
	
	//Returns the number of neighbors in "v"
	set<int> getNeighbors(int v);	
	int getEdgeCount();
};

#endif
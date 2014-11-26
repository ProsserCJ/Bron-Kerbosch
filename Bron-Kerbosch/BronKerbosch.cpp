/*
	Chris Prosser, Laura Wendlendt, Eric Weaver, Michael Wiegand
	Implementation of the Bron-Kerbosch class
	COMP 442 -- Introduction to Algorithms
	Project 2	
*/

#include "BronKerbosch.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <chrono>

BronKerbosch::BronKerbosch(char* file)
{
	ifstream fin(file);

	int index = 0;
	while(!fin.eof())
	{
		graph.push_back(vector<int>());
		
		while(fin.peek() != '\n' && fin.peek() != EOF)
			graph[index].push_back(fin.get() - '0');
		
		fin.get();
		index++;
	}

	fin.close();
}

set<int> BronKerbosch::getNeighbors(int v)
{
	set<int> ret;
	for(int i=0; i<graph.size(); i++)
		if(graph[v][i] == 1) ret.insert(i);

	return ret;
}

void BronKerbosch::backtrack(set<int> R, set<int> P, set<int> X)
{
	if (P.size() == 0 && X.size() == 0)
	{
		maxCliques.insert(R);
		return;
	}

	////choose pivot vertex (with the most neighbors)
	//set<int> pUx;
	//set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(pUx, pUx.begin()));

	//int max = 0; set<int> maxNeighbors;
	//for(auto it = pUx.begin(); it != pUx.end(); ++it)
	//{
	//	set<int> temp = neighbors(*it);
	//	if (temp.size() > max)
	//	{
	//		max = temp.size();
	//		maxNeighbors = temp;
	//	}
	//}

	//for(auto it = maxNeighbors.begin(); it != maxNeighbors.end(); ++it)
	//	P.erase(*it);


	
	//iterate through neighbors of pivot
	for(auto it = P.begin(); it != P.end();)
	{
		set<int> N = getNeighbors(*it), R2 = R, P2, X2;
		
		//Store R union v in R2
		R2.insert(*it);

		//Store P intersect N in P2, X intersect N in X2
		set_intersection(P.begin(), P.end(), N.begin(), N.end(), inserter(P2, P2.begin()));
		set_intersection(X.begin(), X.end(), N.begin(), N.end(), inserter(X2, X2.begin()));

		backtrack(R2, P2, X2);

		X.insert(*it);
		P.erase(it++);		
	}
}

void BronKerbosch::run()
{
	set<int> R,P,X;
	for (int i=0; i<graph.size(); i++) P.insert(i);

	//Begin time
	start = chrono::duration_cast<chrono::milliseconds>(
		chrono::high_resolution_clock::now().time_since_epoch()).count();

	backtrack(R,P,X);

	//End time
	end = chrono::duration_cast<chrono::milliseconds>(
		chrono::high_resolution_clock::now().time_since_epoch()).count();

}

void BronKerbosch::print()
{
	cout << "Maximal cliques:\n";

	for (auto it = maxCliques.begin(); it != maxCliques.end(); it++)
	{
		cout << "{";
		
		//Print first value here, for formatting purposes
		auto it2 = (*it).begin();
		cout << (*it2) + 1; ++it2;

		for (; it2 != (*it).end(); ++it2)
			cout << ", " << (*it2) + 1; //add one for silly humans

		cout << "}\n";		
	}

	cout << "\nV = " << graph.size() << "\n";
	cout << "E = " << getEdgeCount() << "\n";
	cout << "Time: " << end - start << " milliseconds \n"; 
}

int BronKerbosch::getEdgeCount()
{
	int count = 0;
	for (int i=0; i<graph.size(); i++)
		for(int j=i+1; j<graph[i].size(); j++)
			count += graph[i][j];

	return count;
}

void BronKerbosch::analyze(int trials)
{
	cout << "\n\nExtra analysis:\n";
	
	//Run a number of trials, doubling the size V and quadrupling the size of E
	for(int i=0; i<trials; i++)
	{		
		int size = graph.size();
		for (int j=0; j<size; j++)
		{
			graph.push_back(vector<int>());
			graph[j].insert(graph[j].end(), graph[j].begin(), graph[j].end());
			graph[j+size].insert(graph[j+size].end(), graph[j].begin(), graph[j].end());
		}

		run();

		cout << "\nV = " << graph.size() << "\n";
		cout << "E = " << getEdgeCount() << "\n";
		cout << "Time: " << end - start << " milliseconds \n"; 		
	}
}
/*
	Chris Prosser, Laura Wendlendt, Eric Weaver, Michael Wiegand
	Driver for the Bron-Kerbosch class
	COMP 442 -- Introduction to Algorithms
	Project 2	
*/

#include "BronKerbosch.h"

void main()
{
	BronKerbosch bk("input.txt");
	bk.run();
	bk.print();	

	bk.analyze(7);
}
/*
	Chris Prosser, Laura Wendlendt, Eric Weaver, Michael Wiegand
	Driver for the Bron-Kerbosch class
	COMP 442 -- Introduction to Algorithms
	Project 2	
*/

#include "BronKerbosch.h"
#include "RealWorld.h"

void main()
{
	//makeDataFile();
	//BronKerbosch bk("input.txt");
	//BronKerbosch bk("realData.txt");
	//BronKerbosch bk("realData2.txt");
	//BronKerbosch bk("realData3.txt");
	BronKerbosch bk("realData4.txt");


	bk.run();
	bk.print();	

	//bk.analyze(2);
}
/*
	Chris Prosser, Laura Wendlendt, Eric Weaver, Michael Wiegand
	Interface getting real data from people and friendships
	COMP 442 -- Introduction to Algorithms
	Project 2	
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class Person
{
public:
	Person(int id, string name): id(id), name(name){}
	string name;
	int id;
	vector<int> friends; 
	void addFriend(int id)
	{
		friends.push_back(id);
	}
private:


};

vector<string> parse(string s, string delimiter)
{
	vector<string> rtn;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		rtn.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	rtn.push_back(s);
	return rtn;
}

vector<Person> loadList()
{
	vector<Person> output; 
	ifstream f("friendships.txt");
	string friendships((std::istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
	ifstream p("people.txt");
	//cout << p.fail() << endl;
	string people((std::istreambuf_iterator<char>(p)), istreambuf_iterator<char>());
	//cout << people.length() << endl;
	vector<string> peopleList = parse(people, "\n");
	vector<string> friendList = parse(friendships, "\n");
	vector<string> ids;
	vector<vector<string>> peopleP;
	vector<vector<string>> friendshipsP;
	for(int i(0); i < peopleList.size(); i++)
	{
		peopleP.push_back(parse(peopleList[i], ","));
	}
	for(int i(0); i < friendList.size(); i++)
	{
		friendshipsP.push_back(parse(friendList[i], ","));
	}
	for(int i(0); i < peopleP.size(); i++)
	{
		bool found(false);
		for(int j(0); j < ids.size(); j++)
		{
			if(peopleP[i].at(0) == ids[j])
			{
				output.push_back(Person(j, peopleP[i][1]));
				found = true;
				break;
			}
		}
		if(!found)
		{
			output.push_back(Person(ids.size(), peopleP[i][1]));
			ids.push_back(peopleP[i].at(0));
		}
	}
	for(int i(0); i < friendshipsP.size(); i++)
	{
		int id1(0);
		int id2(0);
		bool found(false);
		for(int j(0); j < ids.size(); j++)
		{
			if(friendshipsP[i].at(0) == ids[j])
			{
				id1 = j;
				found = true;
				break;
			}
		}
		if(!found)
		{
			id1 = ids.size();
			ids.push_back(friendshipsP[i].at(0));
		}

		bool found2(false);
		for(int j(0); j < ids.size(); j++)
		{
			if(friendshipsP[i].at(1) == ids[j])
			{
				id2 = j;
				found2 = true;
				break;
			}
		}
		if(!found2)
		{
			id2 = ids.size();
			ids.push_back(friendshipsP[i].at(1));
		}
		if(id1 < output.size())
		{
			output[id1].addFriend(id2);
		}
		if(id2 < output.size())
		{
			output[id2].addFriend(id1);
		}
		
	}

	return output;
}

void makeDataFile()
{
	vector<Person> people = loadList();
	vector<vector<int>> op;
	for(int i(0); i < people.size(); i++)
	{
		vector<int> a;
		for(int j(0); j < people.size(); j++)
		{
			a.push_back(0);
		}
		op.push_back(a);
	}
	for(int i(0); i < people.size(); i++)
	{
		for(int j(0); j < people.size(); j++)
		{
			for(int k(0); k < people[i].friends.size(); k++)
			{
				if(people[i].friends[k] == j)
				{
					op[i][j] = 1;
					op[j][i] = 1;
					break;
				}
			}
		}
	}
	ofstream out("realData4.txt");
	for(int i(0); i < people.size()/8; i++)
	{
		for(int j(0); j < people.size()/8; j++)
		{
			out << op[i][j];
		}
		if(i < people.size()/8-1)
		{
				out << endl;
		}
	}
	out.close();
}
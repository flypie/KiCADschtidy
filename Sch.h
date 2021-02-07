#pragma once
#include <iostream>
#include <fstream>
#include <climits>
#include <string>

using namespace std;

class Sch
{
public:

	Sch();
	~Sch() {};

	Sch(const string FileName,const unsigned long UUID);

private:

	void Process();


	ifstream Infile;
	ofstream Outfile;
	Sch* Sub;
	unsigned long UUID;
};


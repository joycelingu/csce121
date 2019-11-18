#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	ifstream file;
	file.open(argv[1]);
	
	string line;
	float one, two;
	vector<vector<float> > data;
	while(getline(file,line))
	{
		vector<float> temp;
		istringstream iss(line);
		while(iss >> one >> two)
		{
			temp.push_back(one);
			temp.push_back(two);
		}
		data.push_back(temp);
	}
	
	for(int i=1; i<=12; i++)
	{	
		cout << "---------------" << endl;
		cout << "hour=" << i << endl;
		for(int j=0; j<data.size(); j++)
		{
			Point2D p;
			p.set(0,0,data[j][0]);
			p.set(0,1,data[j][1]);
			Rot2D R;
			R.set2(p.get(0,0),p.get(0,1));
			R.hour(i*30);
		}
	}
}
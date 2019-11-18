#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

void subsetsR(vector<string> v, int index, vector<string> now)
{
	vector<vector<string> > powerset;
	

	powerset.push_back(now);
	
	for(int i = index+1; i<v.size(); i++)
	{
		now.push_back(v[i]);
		subsetsR(v,i,now);
		now.pop_back();
	
	}
	for(int i=0; i<powerset.size();i++)
	{
		for(int j=0; j<powerset[i].size();j++)
			cout << powerset[i][j] << " ";
		cout << endl;
	}
}

vector<vector<string> > subsetsI(vector<string> set)
{
	vector<vector<string> > powerset;
	vector<string> subset;
	
	for(int i =0; i< pow(2,set.size()); i++)
	{
		for(int j=0; j<set.size(); j++)
		{
			 if(i & (1 << j)) 
				subset.push_back(set[j]);
		}
		powerset.push_back(subset);
		subset.clear();
	}
	return powerset;

}

int main(int argc, char** argv)
{
	vector<string> v;
	
	//getting list of items to find subsets for
	cout << ">";
	string input;
	getline(cin, input);
	istringstream iss(input);
	string item;
	while(iss >> item)
		v.push_back(item);
	
	//calling recursive function
	vector<string> now;
	cout << "subsetsR:" << endl;
	subsetsR(v,-1,now);
	
	//calling iterative function
	vector<vector<string> > I = subsetsI(v);
	cout << "subsetsI:" << endl;
	for(int i=0; i<I.size(); i++)
	{
		for(int j=0; j<I[i].size(); j++)
			cout << I[i][j] << " ";
		cout << endl;
	}
	
}
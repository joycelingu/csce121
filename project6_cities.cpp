#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

struct City
{
	string name;
	float lat;
	float lon;
	string fst;
	float fdist;
	string cst;
	float cdist;
};

float distance(vector<City> c, int one, int two)
{
	c[two].lat = c[two].lat*(M_PI/180);
	c[two].lon = c[two].lon*(M_PI/180);
	c[one].lat = c[one].lat*(M_PI/180);
	c[one].lon = c[one].lon*(M_PI/180);
	float dlat = c[two].lat-c[one].lat;
	float dlon = c[two].lon-c[one].lon;
	float a = pow(sin(dlat/2),2) + cos(c[one].lat)*cos(c[two].lat)*pow(sin(dlon/2),2);
	float c2 = 2*atan2(sqrt(a),sqrt(1-a));
	float d = 3961*c2;
	
	return d;
}

City closest(vector<City> c, int i)
{
	string close;
	float dist = 0.0;
	City cl;
	if(i!=0)
		dist = distance(c,i,i-1);
	else
		dist = distance(c,i,i+1);
	
	for(int j=0; j<c.size(); j++)
	{
		if(distance(c,i,j) < dist && j!=i)
		{
			dist = distance(c,i,j);
			close = c[j].name;
		}
	}
	cl.cst = close;
	cl.cdist = dist;
	return cl;
}

City farthest(vector<City> c, int i)
{
	string far;
	float dist = 0.0;
	City f;
	
	for(int j=0; j<c.size(); j++)
	{
		if(distance(c,i,j) > dist)
		{
			dist = distance(c,i,j);
			far = c[j].name;
		}
	}
	f.fst = far;
	f.fdist = dist;
	return f;
	
}

vector<City> close_cities(vector<City> t, string n, int N)
{
	vector<City> list;
	int index = 0;
	int temp_index = 0;
	vector<City> c = t;
	for(int i=0; i<N; i++)
	{	
		for(int k=0; k<c.size(); k++)
		{
			if(c[k].name == n)
				index = k;
		}
		City temp = closest(c,index);
		list.push_back(temp);
		for(int j=0; j<c.size(); j++)
		{
			if(c[j].name == temp.cst )
				temp_index = j;
		}
		c.erase(c.begin()+temp_index);
	}
	return list;
	
}

int main(int argc, char** argv)
{
	ifstream file;
	file.open(argv[1]);
	string line;
	City c;
	vector<City> city;
	while(getline(file, line))
	{
		istringstream iss(line);
		iss >> c.name >> c.lat >> c.lon;
		city.push_back(c);
	}
	if(argc==2)
	{	
		string close;
		float d_close = distance(city,0,1);
		string far;
		float d_far = 0.0;
		for(int i=0; i<city.size(); i++)
		{
			if(closest(city,i).cdist < d_close)
			{
				d_close = closest(city,i).cdist;
				close = city[i].name + " and " + closest(city,i).cst;
			}
			if(farthest(city,i).fdist > d_far)
			{
				d_far = farthest(city,i).fdist;
				far = city[i].name + " and " + farthest(city,i).fst;
			}
			cout << setw(12) << city[i].name << "   closest=" << closest(city,i).cst << " (" << closest(city,i).cdist << ")     farthest" << farthest(city,i).fst << " (" << farthest(city,i).fdist << ")" << endl;
		}
		cout << "closest cities: " << close << ", distance =" << d_close << "mi" << endl;
		cout << "farthest cities: " << far << ", distance =" << d_far << "mi" << endl;
	}
	
	if(argc==4)
	{
		string n = argv[2];
		int N = stoi(argv[3]);
		for(int i=0; i<5; i++)
		{
			cout << close_cities(city,n,N)[i].cst << " (" << close_cities(city,n,N)[i].cdist << "mi)" << endl;
		}
	}
	vector<City> list;
	int index = 0;
	int temp_index = 0;
	
}
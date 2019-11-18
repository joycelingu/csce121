#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdlib.h>

using namespace std;

//prints histogram
void histogram(float s, float b, vector<float> p, int bucket_n)
{
	float interval = (b - s)/bucket_n;
	float first = s;
	float second = s + interval;
	for(int i=0; i<bucket_n; i++)
	{
		cout << setw(7) << first << " - " << setw(7) << second << "  ";
		for (int j=0; j<p.size(); j++)
		{
			if(p.at(j)>=first && p.at(j)<=second)
				cout << "*";
		}
		cout << endl;
		first = second; 
		second += interval; 
		
	}
}

//finding standard deviation
float std_dev(float m, int c, vector<float> p)
{
	float sum_of_diff = 0.0;
	for (int i=0; i<p.size(); i++)
		sum_of_diff += pow(m - p.at(i),2);
	float sd = sqrt(sum_of_diff/c);
	return sd;	
}

int main(int argc, char** argv)
{
	ifstream input;
	input.open(argv[1]);
	int bucket_num = atoi(argv[2]);
	float num;
	float sum = 0.0;
	int count = 0;
	float biggest = 0.0;
	float smallest = 10000;
	vector<float> price;
	
	while(input >> num)
	{
		sum += num;
		count++;
		price.push_back(num);
		if(num > biggest)
			biggest = num;
		if(num < smallest)
			smallest = num;
	}
	float mean = sum/count;
	
	cout << "count:" << count << endl;
	cout << "mean:" << mean << endl;
	cout << "standard deviation:" << std_dev(mean, count, price) << endl;
	cout << "range:" << smallest << " - " << biggest << endl;
	cout << endl;
	
	histogram(smallest, biggest, price, bucket_num);
	
	input.close();
	
}
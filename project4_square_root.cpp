#include <iostream>
#include <cmath>

using namespace std;

float function(float n, int n2)
{
	return n*n- n2;
}

float derivative(float n)
{
	return 2*n;
}

void iteration(int num)
{
	float square_root = num;
	cout << "iteration 1: " << num << endl;
	
	for(int i=2; i<=10; i++)
	{
		float x = square_root;
		square_root = x - function(x, num)/derivative(x);
		cout << "iteration " << i << ": " << square_root << endl;
	}
}

float recursion(float num, double square_root)
{
	if(abs(square_root*square_root-num)<=0.00001)
		return square_root;
	else
	{
		cout << "recursive estimate: " << square_root << endl;
		square_root = square_root - function(square_root, num)/derivative(square_root);
		return recursion(num, square_root);
	}
}

int main(int argc, char** argv)
{
	int number;
	cout << "Enter a number to find the square root for: ";
	cin >> number;
	cout << endl; 
	iteration(number);
	cout << "sqrt(" << number << ") = " << sqrt(number) << endl; 
	cout << endl;
	cout << "recursive estimate: " << recursion(number,number) << endl;;
	cout << "sqrt(" << number << ") = " << sqrt(number) << endl; 
}
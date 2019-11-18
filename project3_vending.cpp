#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

void get_change(float b, int q, int d, int n)
{
	int quarter = floor(b/0.25);
	b -= quarter*0.25; 
	int dime = floor(b/0.1);
	b -= dime*0.1;
	int nickel = round(b/0.05);
	if(quarter != 0)
	{	if(quarter <= q)
			cout << quarter << " quarter ";
		else
		{
			dime += 2;
			nickel += 1;
		}
	}	
	if(dime != 0)
	{	if(dime <= d)
			cout << dime << " dime ";
		else
			nickel += 2;
	}
	if(nickel <= n && nickel != 0)
		cout << nickel << " nickel" << endl;
	
}

int main(int argc, char** argv)
{
	cout << "> vending" << endl;

	ifstream input_item;
	input_item.open(argv[1]);
	
	ifstream input_count;
	input_count.open(argv[2]);
	
	ifstream input_prices;
	input_prices.open(argv[3]);
	
	vector<string> items;	
	vector<int> count;
	vector<float> prices;
	
	string word;
	while(input_item >> word)
		items.push_back(word);
	
	int num;
	while(input_count >> num)
		count.push_back(num);
	
	float cost;
	while(input_prices >> cost)
		prices.push_back(cost);
	
	//calculating balance based on user input
	float balance = 0.0f;
	string input;
	string user;
	while(getline(cin,input))
	{
		istringstream iss(input);
		if(input == "quit")
			break;
		while(iss >> user)
		{
			if(user=="quarter" || user=="nickel" || user=="dime")
			{
				for(int i=0; i<items.size(); i++)
				{
					if(items[i]==user)
					{
						balance += prices[i]; 
						count[i]++;
					}
				}
				
			}
			
			else if(user=="press")
				continue;
			
			else if(user=="coke" || user=="gum" || user=="juice" || user=="chips" || user=="snicker")
			{
				
				for(int i=0; i<items.size(); i++)
				{
					if(items[i]==user)
					{
						if(count[i]>=1)
						{	
							if(balance >= prices[i])
							{
								cout << "dispensing: " << user << endl;
								balance -= prices[i]; 
								cout << "change: ";
								get_change(balance, count[0], count[1], count[2]);
								balance = 0.0;
								count[i]--;
							}
							else
								cout << "balance insufficient" << endl;
						}
						else
							cout << "item not available" << endl;
					}
				}
			}
			
			else
			{
				cout << "invalid input" << endl;
			}
		}
		if(balance != 0.0)
			cout << "balance: $" << fixed << setprecision(2) << balance << endl;
		cout << endl;
	}
	
	
	
	
}


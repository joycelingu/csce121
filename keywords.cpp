#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <unordered_map>
using namespace std;

unordered_map<string,int> read (string filename) //to read files
{
	ifstream file;
	file.open(filename);
	unordered_map<string,int> map;
	string line;
	
	while(getline(file,line))
	{
		line.erase(remove(line.begin(),line.end(),'\n'),line.end());
		istringstream iss(line);
		string word;
		while(iss >> word)
		{		
			transform(word.begin(),word.end(),word.begin(),::tolower); //changing word to lower case
			for(int i=word.size()-1; i>=0; i--)
			{
				if(isdigit(word[i]))
					word.erase(word.begin()+i); //removing digits
				if(ispunct(word[i])&&word[i]!='-') //removing punctuations that are not hypens
					word.erase(word.begin()+i);
			}
	
			if(map.find(word)==map.end()) //if word not found in map
				map[word] = 1;
			else
				map[word] += 1;		
		}
	}
	return map;
}
int count (unordered_map<string,int> m) //counting number of words in document/collection
{
	int num = 0;
	for (auto i:m)
		num += i.second;
	return num;
}

float freq (int word, unordered_map<string,int> m) //calculating frequency of word in document/collection
{
	int total = count(m);
	return (float)word/total;
}

float expect (unordered_map<string,int> m,unordered_map<string,int> map,string word)
{
	return count(m)*freq(map[word],map);
}

float enrich (unordered_map<string,int> m, unordered_map<string,int> map,string word)
{
	return (m[word]+5)/(expect(m,map,word)+5);
}

int main(int argc, char** argv)
{
	if(argc!=2 && argc!=3) //checking for invalid command line input
		cout << "Invalid input" << endl;
	
	else //program only runs if there are one or two file names on command line
	{
	vector<pair<int,string> > all;
	unordered_map<string,int> map = read(argv[1]);
		
	for(auto i:map)
		all.push_back(make_pair(i.second,i.first));
		
	sort(all.begin(),all.end()); 
	
	if(argc == 2) //if only collection name is entered onto command line
	{
		for(int i=all.size()-1; i>all.size()-18; i--)
			cout << get<0>(all[i]) << " " << get<1>(all[i]) << endl;
		cout << "(and more...only printed first few)";
	}

	
	else if(argc == 3) //if specific document name is also entered onto command line
	{
		
		ifstream file2;
		unordered_map<string,int> doc = read(argv[2]);
		vector<pair<float,string> > d;
		for(auto i: doc)
		{
			d.push_back(make_pair(enrich(doc,map,i.first),i.first));
		}
		sort(d.begin(),d.end());
		cout << left<< "WORD     num(doc) freq(doc) num(all) freq(all) expected  ratio" << endl;
	
		for(int i=d.size()-1; i>d.size()-11; i--)
		{
			string word = get<1>(d[i]);
			cout << left << setw(13) << word << setw(5) << doc[word] << setw(10) << setprecision(4) << freq(doc[word],doc) << setw(8) << map[word];
			
			printf("%9.6f %7.1f %8.4f", freq(map[word],map),expect(doc,map,word),get<0>(d[i]));
			cout << endl;
		}
		cout << "(and more...only printed first few)";
		
	}
	}

}
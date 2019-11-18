#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iomanip>
//#include "codons.hpp"

using namespace std;
	
string read_genome(char* filename)
{
	ifstream file;
	file.open(filename);
	string line;
	string sequence;
	string code;
	getline(file,line);
	
	while(getline(file,code))
	{
		sequence += code;		
	}
	file.close();
	return sequence;
}

void analyze_genome(string s)
{
	float num = 0.0;
	int count = 0;
	string c = "";
	int location = 0;
	for(int i=0; i<s.size(); i++)
		{
			if(s[i]=='G' || s[i]=='C')
				num++;
			int current = 1;
			for(int j=i+1; j<s.size(); j++)
			{
				if(s[i] != s[j])
					break;
				current++;
			}
			if(current > count)
			{
				location = i;
				count = current;
				c = s[i];
			}
		}
	
	cout << "length: " << s.size() << " bp" << endl;
	cout << "GC content: " << (num/s.size())*100 << "%" << endl;
	cout << "longest homopolymer: ";
	for(int i=0; i < count; i++)
		cout << c;
	cout << "(len=" << count << "bp) at coord " << location;	
}

struct Gene
	{
		string description;
		int start;
		int end;
		string strand;
		int size;
		string ignore1;
		string ignore2;
		string name;
		string orfid; 
	};

vector<Gene> read_genes(char* fname)
{
	
	vector<Gene> genes;
	ifstream file;
	file.open(fname);
	string line;
	string data;
	while(getline(file,line))
	{
		istringstream iss(line);
		string token;
		Gene gene;
		int count = 1;
		while(getline(iss,token,'\t'))
		{
			
			if(count == 1)
			{
				gene.description = token;
				count++;
			}
			else if(count == 2)
			{
				gene.start = stoi(token);
				count++;
			}
			else if(count == 3)
			{
				gene.end = stoi(token);
				count++;
			}
			else if(count == 4)
			{
				gene.strand = token;
				count++;
			}
			else if(count == 5)
			{
				gene.size = stoi(token);
				count++;
			}
			else if(count == 6)
			{
				gene.ignore1 = token;
				count++;
			}
			else if(count == 7)
			{
				gene.ignore2 = token;
				count++;
			}
			else if(count == 8)
			{
				gene.name = token;
				count++;
			}
			else
			{
				gene.orfid = token;
				count++;
			}
		}
		genes.push_back(gene);
		
	}

	return genes;
}
int smallest_gene(vector<Gene> gene)
{	
	int smallest = gene[0].end - gene[0].start + 1;
	for(int i=0; i<gene.size(); i++)
	{	
		if((gene[i].end-gene[i].start + 1) < smallest)
			smallest = gene[i].end-gene[i].start + 1;
	}
	return smallest;
}

int largest_gene(vector<Gene> gene)
{
	int largest = 0;
	for(int i=0; i<gene.size(); i++)
	{
		if((gene[i].end-gene[i].start + 1) > largest)
			largest = gene[i].end-gene[i].start + 1;
	}
	return largest;
}

float find_mean(vector<Gene> gene)
{
	float sum = 0.0;
	for(int i=0; i<gene.size(); i++)
		sum += gene[i].end-gene[i].start + 1;
	return sum/gene.size();
}

float std_dev(vector<Gene> gene, float mean)
{
	float sum_diff = 0.0;
	for(int i=0; i<gene.size(); i++)
		sum_diff += pow(gene[i].end-gene[i].start + 1 - mean,2);
	return sqrt(sum_diff/gene.size());
}

float genome_fraction(vector<Gene> gene, string s)
{
	float sum = 0.0;
	for(int i=0; i<gene.size(); i++)
		sum += gene[i].end-gene[i].start + 1;
	return sum/s.size()*100;
}
void calculate_intergenic(vector<Gene> gene)
{
	int largest_inter = 0;
	string large_orfid;
	string large_name;
	int smallest_inter = gene[1].start - gene[0].end;
	string small_orfid;
	string small_name;
	float sum_inter = 0;
	for(int i=0; i<gene.size()-1; i++)
	{
		sum_inter += gene[i+1].start-gene[i].end;
		if((gene[i+1].start-gene[i].end) < smallest_inter)
		{
			smallest_inter = gene[i+1].start-gene[i].end;
			small_orfid = gene[i].orfid;
			small_name = gene[i].name;
		}
		if((gene[i+1].start-gene[i].end) > largest_inter)
		{
			largest_inter = gene[i+1].start-gene[i].end;
			large_orfid = gene[i].orfid;
			large_name = gene[i].name;
		}
	}
	float mean_inter = sum_inter/gene.size();
	cout << "mean size of intergenic regions:" << mean_inter << "bp" << endl;
	cout << "largest intergenic region:" << largest_inter << "bp (after " << large_orfid << "/" << large_name << ")" << endl;
	cout << "smallest intergenic region:" << smallest_inter << "bp (after " << small_orfid << "/" << small_name << ")" << endl;
}

void longest_position(vector<Gene> gene, string s)
{
	int count = 0;
	string c = "";
	string homopolymer;
	string position;
	int location = 0;
	for(int i=0; i<s.size(); i++)
	{
		int current = 1;
		for(int j=i+1; j<s.size(); j++)
		{
			if(s[i] != s[j])
				break;
			current++;
		}
		if(current > count)
		{
			location = i;
			count = current;
			c = s[i];
		}
	}
	for(int i=0; i<count; i++)
		homopolymer += c;
	
	cout << "longest homopolymer: " << homopolymer << ", (len=" << count << "bp) at coord " << location;
	for(int i=0; i<gene.size(); i++)
	{
		if(location>=gene[i].start && location<=gene[i].end)
			cout << " in " << gene[i].orfid << "/" << gene[i].name << endl;
		else if(location < gene[i].start && location>gene[i-1].end)
			cout << " after " << gene[i-1].orfid << "/" << gene[i-1].name << endl;
		else
			continue;
			
	}
	
	
	
}

string transcription(string s, char* g, vector<Gene> gene)
{
	string transcript;
	for(int i=0; i<gene.size(); i++)
	{
		if(g == gene[i].name || g == gene[i].orfid)
		{
			if(gene[i].strand == "-")
			{	for(int j=gene[i].end-1; j>=gene[i].start-1; j--)
				{
					if(s[j] == 'T')
						transcript.append("A");
					else if(s[j] == 'A')
						transcript.append("T");
					else if(s[j] == 'C')
						transcript.append("G");
					else if(s[j] == 'G')
						transcript.append("C");
				}
			}
			else
			{
				for(int j=gene[i].start-1; j<gene[i].end; j++)
				{
					if(s[j] == 'T')
						transcript.append("A");
					else if(s[j] == 'A')
						transcript.append("T");
					else if(s[j] == 'C')
						transcript.append("G");
					else if(s[j] == 'G')
						transcript.append("C");
				}
			}
		}
	}
	return transcript;
}

void print_seq(string t)
{
	for(int i=1; i<=t.size(); i++)
	{
		if((i-1)%70==0)
			cout << setw(4) << i << " ";
		cout << t[i-1];
		if(i%70==0)
			cout << endl;
	}
	
}
char aa(string s) 
{
  if (s=="TTA") return 'L';
  if (s=="TTG") return 'L';
  if (s=="CTT") return 'L';
  if (s=="CTC") return 'L';
  if (s=="CTA") return 'L';
  if (s=="CTG") return 'L';
  if (s=="TGG") return 'W';
  if (s=="TAA") return '*';
  if (s=="TAG") return '*';
  if (s=="TGA") return '*';
  if (s=="ATG") return 'M';
  if (s=="TTT") return 'F';
  if (s=="TTC") return 'F';
  if (s=="TAT") return 'Y';
  if (s=="TAC") return 'Y';
  if (s=="TCT") return 'S';
  if (s=="TCC") return 'S';
  if (s=="TCA") return 'S';
  if (s=="TCG") return 'S';
  if (s=="AGT") return 'S';
  if (s=="AGC") return 'S';
  if (s=="CCT") return 'P';
  if (s=="CCC") return 'P';
  if (s=="CCA") return 'P';
  if (s=="CCG") return 'P';
  if (s=="TGT") return 'C';
  if (s=="TGC") return 'C';
  if (s=="CAT") return 'H';
  if (s=="CAC") return 'H';
  if (s=="CAA") return 'Q';
  if (s=="CAG") return 'Q';
  if (s=="AAT") return 'N';
  if (s=="AAC") return 'N';
  if (s=="CGT") return 'R';
  if (s=="CGC") return 'R';
  if (s=="CGA") return 'R';
  if (s=="CGG") return 'R';
  if (s=="AGA") return 'R';
  if (s=="AGG") return 'R';
  if (s=="ATT") return 'I';
  if (s=="ATC") return 'I';
  if (s=="ATA") return 'I';
  if (s=="AAA") return 'K';
  if (s=="AAG") return 'K';
  if (s=="GAT") return 'D';
  if (s=="GAC") return 'D';
  if (s=="GAA") return 'E';
  if (s=="GAG") return 'E';
  if (s=="ACT") return 'T';
  if (s=="ACC") return 'T';
  if (s=="ACA") return 'T';
  if (s=="ACG") return 'T';
  if (s=="GTT") return 'V';
  if (s=="GTC") return 'V';
  if (s=="GTA") return 'V';
  if (s=="GTG") return 'V';
  if (s=="GCT") return 'A';
  if (s=="GCC") return 'A';
  if (s=="GCA") return 'A';
  if (s=="GCG") return 'A';
  if (s=="GGT") return 'G';
  if (s=="GGC") return 'G';
  if (s=="GGA") return 'G';
  if (s=="GGG") return 'G';
  return '?';
}
string translation(string t)
{
	string temp;
	string translated;
	for(int i=0; i<t.size(); i+=3)
	{
		temp.push_back(t[i]);
		temp.push_back(t[i+1]);
		temp.push_back(t[i+2]);
		translated += aa(temp);
		temp = "";
	}
	return translated;
}

int main(int argc, char** argv)
{
	ifstream file;
	file.open(argv[1]);
	string line;
	getline(file, line);
	cout << "reading:" << line << endl;
	string seq = read_genome(argv[1]);
	analyze_genome(seq);
	vector<Gene> gene = read_genes(argv[2]);
	
	cout << endl;
	cout << "num genes:" << gene.size() << endl;
	cout << "gene sizes: [" << smallest_gene(gene) << "," << largest_gene(gene) << "]" << endl;
	cout << "mean=" << find_mean(gene) << "bp" << endl;
	cout << "standard deviation=" << std_dev(gene, find_mean(gene)) << endl;
	cout << "genome fraction:" << genome_fraction(gene, seq) << "%" << endl;
	calculate_intergenic(gene);
	longest_position(gene, seq);
	print_seq(transcription(seq, argv[3], gene));
	cout << endl;
	cout << endl;
	print_seq(translation(transcription(seq, argv[3], gene)));
	
}
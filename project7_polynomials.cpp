#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class poly
{
	public:
	poly (string a);
	poly (string a, string b);
	vector<float> conversion (string p);
	void output();
	void print(vector<float> s);
	void sum();
	void prod();
	void deriv();
	void root(); 
	float eval(vector<float> c, float n);
	float eval_deriv(vector<float> f, float n);
	
	private:
	vector<float> coeff;
	vector<float> coeff2;
};

poly:: poly(string a)
{
	coeff = conversion(a);
}

poly:: poly(string a, string b)
{
	coeff = conversion(a);
	coeff2 = conversion(b);
}

//function to print polynomial if user enters only polynomial
void poly::output()
{
	print(coeff);
}

//format print resulting polynomial
void poly::print(vector<float> s)
{
	int index = 0;
	for(int i=0; i<s.size(); i++)
	{
		if(s[i]!=0)
			index = i;
	}
	
	for(int i=s.size()-1; i>=0; i--)
	{
		if(s[i]!=0)
		{
			int j = i;
			if(i==0)
			{
				if(s[i]>0 && i!=index)
					cout << '+' << s[i];
				else
					cout << s[i];
			}
			else if(i==1)
			{
				if(s[i]>0 && i!=index)
					cout << '+' << s[i] << 'x';
				else
					cout << s[i] << 'x';
			}
			else
			{
				if(s[i]>0 && i!=index)
					cout << '+' << s[i] << "x^" << i;
				else
					cout << s[i] << "x^" << i;
			}
		}
	}

}

//getting coefficients
vector<float> poly::conversion(string p)
{
	//separates polynomial into individual terms and into a vector of string
	for(int i=0; i<p.size(); i++)
	{
		if(p[i]=='+' || p[i]=='-')
		{	p.insert(i," ");
			i++;
		}
	}
	istringstream iss(p);
	string s;
	vector<string> term;
	while(iss >> s)
		term.push_back(s);
	
	//gets coefficients so that index corresponds to power
	vector<float> coeff;
	coeff.resize(10,0);
	float c;
	char x, sym, sign;
	int degree;
	for(int i=0; i<term.size(); i++)
	{
		string a = term[i];
		istringstream t(a);
		
		if(a.find("x^")!=string::npos)
		{
			if(a.find("x^")!=0)
			{	
				if(a[a.find('x')-1]!='+' && a[a.find('x')-1]!='-')
				{
					while(t >> c >> x >> sym >> degree)
						coeff[degree] = c;
				}
				else 
				{
					if(a[a.find("x^")-1]=='+')
					{
						while(t >> sign >> x >> sym >> degree)
							coeff[degree] = 1;
					}
					else
					{
						while(t >> sign >> x >> sym >> degree)
							coeff[degree] = -1;
					}
				}
				
			}
			else
			{
				while(t >> x >> sym >> degree)
					coeff[degree] = 1;
			}
		}
		else if(a.find('x')!=string::npos)
		{
			if(a.find('x')!=0 && a[a.find('x')-1]!='+' && a[a.find('x')-1]!='-')
			{
				while(t >> c >> x)
					coeff[1] = c;
			}
			else if (a[a.find('x')-1]=='+')
				coeff[1] = 1;
			else if(a[a.find('x')-1]=='-')
				coeff[1] = -1;
			else if(a.find('x')==0)
				coeff[1] = 1;
		}
		else
		{	
			while(t >> c)
				coeff[0] = c;
		}
	}
	
	return coeff;
}

void poly::sum()
{
	vector<float> s;
	int index = 0;
	for(int i=0; i<coeff.size(); i++)
		s.push_back(coeff[i]+coeff2[i]);
	cout << "SUM" << endl;
	cout << "P= ";
	print(coeff);
	cout << endl;
	cout << "Q= ";
	print(coeff2);
	cout << endl;
	cout << "P+Q= ";
	print(s);
	
}

void poly:: prod()
{
	vector<float> p;
	p.resize(12,0);
	for(int i=0; i<coeff.size();i++)
	{
		for(int j=0; j<coeff2.size();j++)
		{
			if(coeff[i]!=0 && coeff2[j]!=0)
			{
				p[i+j] += coeff[i]*coeff2[j];
			}
		}
	}
	cout << "PROD" << endl;
	cout << "P= ";
	print(coeff);
	cout << endl;
	cout << "Q= ";
	print(coeff2);
	cout << endl;
	cout << "P*Q= ";
	print(p);
}

void poly:: deriv()
{
	vector<float> d;
	d.resize(10,0);
	for(int i=0; i<coeff.size(); i++)
	{
		if(i!=0)
		{
			if(coeff[i]!=0)
				d[i-1] = coeff[i]*i;
		}
		else
			d[0] = 0;
	}
	cout << "DERIV" << endl;
	cout << "P= ";
	print(coeff);
	cout << endl;
	cout << "dP/dx= ";
	print(d);
}

//evaluating value of polynomial at a certain x value
float poly:: eval(vector<float> c, float n)
{
	float p = 0.0;
	for(int i=0; i<c.size(); i++)
	{
		if(c[i]!=0)
			p += c[i]*pow(n,i);
	}
	return p;
}

//evaluating the value of the derivative at a certain x value
float poly:: eval_deriv(vector<float> f, float n)
{
	vector<float> d;
	d.resize(10,0);
	for(int i=0; i<f.size(); i++)
	{
		if(i!=0)
		{
			if(f[i]!=0)
				d[i-1] = f[i]*i;
		}
		else
			d[0] = 0;
	}
	float p = 0.0;
	for(int i=0; i<d.size(); i++)
	{
		if(d[i]!=0)
			p += d[i]*pow(n,i);
	}
	return p;
	
}

//finding one root using the NewtonRaphson method
void poly:: root()
{
	float x = 10.0;
	float d = eval(coeff,x)/eval_deriv(coeff,x);
	while(abs(d)>=0.00001)
	{
		d = eval(coeff,x)/eval_deriv(coeff,x);
		x -= d;
	}
	cout << "ROOT" << endl;
	cout << "P="; 
	print(coeff);
	cout << endl;
	cout << "root(P)=r=" << x << ", P(r)=" << eval(coeff,x);
	
}

int main(int argc, char** argv)
{
	cout << "> ";
	string line;
	string user;
	
	//getting user input from command line
	while(getline(cin,line))
	{	
		vector<string> input;
		istringstream iss(line);
		if(line == "quit")
			break;
		
		while(iss >> user)
			input.push_back(user);
		
		if(input[0] == "sum")
		{
			poly P(input[1],input[2]);
			P.sum();
		}
		else if(input[0] == "prod")
		{
			poly P(input[1],input[2]);
			P.prod();
		}
		else if(input[0] == "deriv")
		{
			poly P(input[1]);
			P.deriv();
		}
		else if(input[0] == "root")
		{
			poly P(input[1]);
			P.root();
		}
		else if(input.size()==1 && input[0].find('x')!=string::npos)
		{
			poly P(input[0]);
			P.output();
		}
		// checking for invalid input
		else 
			cout << "invalid input";
		cout << endl;
		cout << endl;
		cout << "> ";
	}
}
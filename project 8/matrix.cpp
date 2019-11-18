#include "matrix.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#define _USE_MATH_DEFINE
using namespace std;

Matrix:: Matrix(int p, int q)
{
	a = new float*[p];
	for(int i=0; i<p; i++)
	{
		a[i] = new float[q];
		for(int j=0; j<q; j++)
			a[i][j] = 0.0;
	}
	r = p;
	c = q;
}

Matrix:: Matrix(const Matrix &obj)
{
	a = obj.a;
	r = obj.r;
	c = obj.c;
}

float Matrix:: get(int row, int col)
{
	return a[row][col];
}

void Matrix:: set(int row, int col, float val)
{
	a[row][col] = val;
}

void Matrix:: print()
{
	float** covar = covariance();
	float** corr = correlation();
	
	cout << "covariance matrix:" << endl;
	for(int i=0; i<c; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout << left;
			printf("%.3f", covar[i][j]);
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	cout << "correlation matrix:" << endl;
	for(int i=0; i<c; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout << left;
			printf("%.3f", corr[i][j]);
			cout << " ";
		}
		cout << endl;
	}	
}

void Matrix:: center()
{
	vector<float> mean;
	mean.resize(4);
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
			mean[j] += a[i][j];
	}
	for(int i=0; i<mean.size(); i++)
		mean[i] /= r; 
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			a[i][j] -= mean[j];
		}
	}
}

float** Matrix:: transpose()
{
	float** b = new float*[c];
	for(int i=0; i<c; i++)
	{
		b[i] = new float[r];
		for(int j=0; j<r; j++)
		{
			b[i][j] = 0.0;
		}
	}
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
			b[j][i] = a[i][j];
	}
	return b;	
}

float** Matrix:: prod(float** x, float** y, int r1, int c2, int c1)
{
	float** m = new float*[c];
	for(int i=0; i<r1; i++)
	{
		m[i] = new float[c2];
		for(int j=0; j<c2; j++)
		{
			m[i][j] = 0.0;
		}
	}
	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c2; j++)
		{
			for(int k=0; k<c1; k++)
				m[i][j] += x[i][k]*y[k][j];
		}
	}
	return m;
}

float** Matrix:: covariance()
{
	float** t = transpose();
	
	return prod(t,a,c,c,r);
	
	
}

float** Matrix:: correlation()
{
	float** p = covariance();
	float** corr = new float*[4];
	for(int i=0; i<4; i++)
	{
		corr[i] = new float[4];
		for(int j=0; j<4; j++)
		{
			corr[i][j] = p[i][j]/sqrt(p[i][i]*p[j][j]);
		}
	}
	return corr;
}


Point2D:: Point2D():Matrix(1,2){}

Rot2D:: Rot2D():Matrix(2,2)
{
	P = new float*[1];
	
	P[0] = new float[2];
	for(int j=0; j<2; j++)
		P[0][j] = 0.0;
	
}

void Rot2D:: set2(float one, float two)
{
	P[0][0] = one;
	P[0][1] = two;
}

void Rot2D:: rotation(float degree)
{
	float rad = M_PI/180*degree;
	set(0,0,cos(rad));
	set(0,1,-sin(rad));
	set(1,0,sin(rad));
	set(1,1,cos(rad));
	
}

void Rot2D:: hour(float d)
{
	rotation(d);
	float** rotated = prod(P,a,1,2,2);
	if(fabs(rotated[0][0])<0.000001)
	{
		printf("%.3f", 0);
		cout << " ";
	}
	if(fabs(rotated[0][0])>=0.000001)
	{
		printf("%.3f",rotated[0][0]);
		cout << " ";
	}
	if(fabs(rotated[0][1])<0.000001)
	{
		printf("%.3f", 0);
		cout << endl;
	}
	
	if(fabs(rotated[0][1])>=0.000001)
	{
		printf("%.3f", rotated[0][1]);
		cout << endl;
	}
}
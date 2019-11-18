#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
	//take month and year as command line arguments
    int month = atoi(argv[1]);
	int year = atoi(argv[2]);
	
	//checking if year is leap year		
	bool isLeapYear = true; 
	if((year%4==0 && year%100!=0) || (year%4==0 && year%400==0))
		isLeapYear;
	else

		isLeapYear = false;
	
	//finding what day the first day of the month falls on
	int temp = 0;
	int temp_y = year;
	if (month==1)
	{
		temp = 13;
		temp_y--;
	}
	else if (month==2)
	{	temp = 14;
		temp_y--;
	}
	else 
		temp = month;

	int n = 1 + 2*temp + 3*(temp+1)/5 + temp_y + temp_y/4 - temp_y/100 + temp_y/400 + 2;
	int firstDay = n%7;

	int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int numSpaces[7] = {6, 0, 1, 2, 3, 4, 5};
	
	if(isLeapYear)
		daysInMonth[1] = 29;
	
	//printing calendar 
	string allMonths[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	cout << allMonths[month-1] << " " << year << endl;
	printf("%30s \n","-------------------------------------------");
	printf("%4s %1s %3s %1s %3s %1s %3s %1s %3s %1s %3s %1s %3s %1s \n","|  Su","|","Mo","|", "Tu","|", "We","|", "Th","|", "Fr","|", "Sa","|");
	printf("%30s \n","-------------------------------------------");
	printf("%1s", "|");

	for (int i=0; i<numSpaces[firstDay]; i++)
	{
		printf("%4s %1s"," ","|");
	}

	for (int i=1; i<=daysInMonth[month-1]; i++)
	{	if(month==7 && i==4)
			printf("%4s %1s","*4", "|");
		else if(month==10 && i==31)
			printf("%4s %1s","*31", "|");
		else if(month==12 && i==25)
			printf("%4s %1s","*25","|");
		else
			printf("%4d %1s", i, "|");
		if((i+numSpaces[firstDay])%7==0 && i!=daysInMonth[month-1])
		{	
			cout << endl;
			printf("%30s \n","-------------------------------------------");
			printf("%1s", "|");
		}
			
		
	}
	int extra = 7-(numSpaces[firstDay] + daysInMonth[month-1])%7;
	for(int i=0; i<extra; i++)
		printf("%4s %1s"," ","|");
	cout << endl;
	printf("%30s \n","-------------------------------------------");
	
	
}

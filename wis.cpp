/*
 * wis.cpp
 *
 */

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

#define size 10

class INTERVAL
{
public:
	int start;
	int finish;
	double value;
	int ivalue;
	INTERVAL()
	{
		//srand(time(NULL));
		start = rand() % 100;
		finish = start + (rand() % 100);
		value = (double)(rand() % 100);// / 10.0;
		ivalue = rand() % 10;
	};
	int max_compatible;
};

INTERVAL interval[size];
int sorted [size];

void PrintSeq(int* obj, int sz)
{
	for(int i = 0; i < sz; i++)
		cout << obj[i] << " ";
	cout << "\n";
}

void PrintVal(INTERVAL* obj, int sz)
{
	for(int i = 0; i < sz; i++)
		cout << i << ":(" << obj[i].start << "," << obj[i].finish << "," << obj[i].value << ") ";
	cout << "\n";
}

void PrintComp(INTERVAL* obj, int sz)
{
	for(int i = 0; i < sz; i++)
		cout << obj[i].max_compatible << " ";
	cout << "\n";
}

void merge_sort(INTERVAL* obj, int from, int to, int* sorted)
{
	if(from == to)
	{
		sorted[from] = to;
		//sorted!
		//PrintSeq(sorted,size);
	}
	else
	{
		//for i -> sorted[i] = i; ???
		int mean = (from + to) / 2;
		merge_sort(obj, from, mean, sorted);
		merge_sort(obj, mean+1, to, sorted);
		//combine(obj, from, mean, to);
		//cout << from << " " << mean << " " << to << " \n";
		int aux[to - from + 1];
		int i = 0, j = 0;
		while( (i <= mean - from) || (j <= to - mean - 1) )
		{
			if((i <= mean - from) && (j <= to - mean - 1))
			{
				//if(obj[sorted[from+i]].value <= obj[sorted[mean+1+j]].value)
				if(obj[sorted[from+i]].finish <= obj[sorted[mean+1+j]].finish)
				{
					aux[i+j] = sorted[from+i];
					i++;
				}
				else
				{
					aux[i+j] = sorted[mean+1+j];
					j++;
				}
			}
			else if((i > mean - from) && (j <= to - mean - 1))
			{
				aux[i+j] = sorted[mean+1+j];
				j++;
			}
			else if((i <= mean - from) && (j > to - mean - 1))
			{
				aux[i+j] = sorted[from+i];
				i++;
			}
			//cout << i << " " << j << " \n";
		}
		for(int k = 0; k <= to - from; k++)
			sorted[from+k] = aux[k];
		//PrintVal(obj,size);
		//PrintSeq(sorted,size);
	}
}

int WIS(INTERVAL* interval, int* sorted, int sz)
{
	if(sz == -1)
		return 0.0;
	else
	{
		double v1 = WIS(interval, sorted, sz-1);
		double v2 = interval[sorted[sz-1]].value + WIS(interval, sorted, interval[sorted[sz-1]].max_compatible);
		//cout << v1 << " " << v2 << " \n";
		return (v1 > v2)?v1:v2;
	}
	//return 0.0;
}

int main()
{
	srand(time(NULL));

	merge_sort(interval,0,9,sorted);
	PrintVal(interval,size);
	PrintSeq(sorted,size);

	for(int i = 0; i < size; i++)
	{
		interval[sorted[i]].max_compatible = -1;
		for(int j = 0; j < i; j++)
		{
			if(interval[sorted[j]].finish <= interval[sorted[i]].start)
				interval[sorted[i]].max_compatible = sorted[j];
		}
	}
	PrintComp(interval,size);

	cout << WIS(interval,sorted,size) << " \n";
	return 0;
}

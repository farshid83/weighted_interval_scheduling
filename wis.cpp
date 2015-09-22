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
	int max_compatible;
	INTERVAL()
	{
		//srand(time(NULL));
		int i = rand()%100, j = rand()%100;
		if(i < j)
		{
			start = i;
			finish = j;
		}
		else
		{
			finish = i;
			start = j;
		}
		value = (double)(rand() % 100);// / 10.0;
		ivalue = rand() % 10;
		max_compatible = -1;
	};
};

void PrintSeq(int* obj, int sz)
{
	for(int i = 0; i < sz; i++)
		cout << obj[i] << ":(" << i << ")  ";
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
		cout << i << ":(" << obj[i].max_compatible << ")  ";
	cout << "\n";
}

void merge_sort(INTERVAL* obj, int prop_index, int from, int to, int* sorted)
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
		merge_sort(obj, prop_index, from, mean, sorted);
		merge_sort(obj, prop_index, mean+1, to, sorted);
		//combine(obj, from, mean, to);
		//cout << from << " " << mean << " " << to << " \n";
		int aux[to - from + 1];
		int i = 0, j = 0;
		while( (i <= mean - from) || (j <= to - mean - 1) )
		{
			if((i <= mean - from) && (j <= to - mean - 1))
			{
				int iv1 = 0, iv2 = 0;
				//int v1 = 0, v2 = 0;
				if(prop_index == 1)
				{
					iv1 = obj[sorted[from+i]].start;
					iv2 = obj[sorted[mean+1+j]].start;
				}
				else if(prop_index == 2)
				{
					iv1 = obj[sorted[from+i]].finish;
					iv2 = obj[sorted[mean+1+j]].finish;
				}
				else if(prop_index == 3)
				{
					iv1 = obj[sorted[from+i]].ivalue;
					iv2 = obj[sorted[mean+1+j]].ivalue;
				}
				//if(obj[sorted[from+i]].finish <= obj[sorted[mean+1+j]].finish)
				if(iv1 <= iv2)
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

int wis[size]; // For memoize!!!
int WIS(INTERVAL* interval, int* sorted, int sid) //sorted id
{
	//cout << "wis[index] = " << wis[sid] << ", sid = " << sid << "\n";
	if(wis[sid] != -1) // Memoization
		return wis[sid];
	if(sid < 0)
		return 0.0;
	else
	{
		double v1 = WIS(interval, sorted, sid-1);
		double v2 = interval[sorted[sid]].value
				  + WIS(interval, sorted, interval[sorted[sid]].max_compatible);
		//cout << "v1 = " << v1 << ", v2 = " << v2 << ", sid = " << sid << ", comp = " << interval[sorted[sid]].max_compatible << "\n";
		//int i = 0;
		//cin >> i;
		if(sid > 0)
			wis[sid] = (v1>v2)?v1:v2;
		return (v1 > v2)?v1:v2;
	}
	//return 0.0;
}

int main()
{
	srand(time(NULL));
	INTERVAL interval[size];
	int sorted [size];

	merge_sort(interval,2,0,size-1,sorted);
	PrintVal(interval,size);
	PrintSeq(sorted,size);

	for(int i = 0; i < size; i++)
	{
		interval[sorted[i]].max_compatible = -1;
		for(int j = 0; j < i; j++)
		{
			if(interval[sorted[j]].finish <= interval[sorted[i]].start)
				interval[sorted[i]].max_compatible = j;
		}
	}
	PrintComp(interval,size);

	for(int i = 0; i < size; i++)
		wis[i] = -1;
	//cout << WIS(interval,sorted,size-1) << " \n";

	for(int i = 0; i < size; i++)
		cout << WIS(interval,sorted,i) << " \n";

	return 0;
}




// O(nlog(n))

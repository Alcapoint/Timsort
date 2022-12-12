#include <iostream>
#include <vector>		
#include <algorithm>

using namespace std;

void printArr(int* arr, int num);
void swap(int* arr, int a, int b);
int  runMinrun(int n);
void insert(int* arr, int start, int end, int num);
void merge(int* arr, int start1, int dlina1, int start2, int dlina2, int num);
void timsort(int* arr, int N);

int runMinrun(int n) 
{
	int r = 0;
	while (n >= 64)
	{
		r = (n & 1)|r;
		n >>= 1;
	}
	return n + r;
}

void insert(int* arr, int start, int end, int num)
{
	for (int i = start + 1; i < end; ++i)
	{
		int curr = arr[i];
		int j = i - 1;
		while ((j >= start) && (curr < arr[j]))
		{
			swap(arr[j], arr[j + 1]);
			--j;
		}
	}
}

typedef struct def
{
	int start;
	int dlina;
} Range;


void swap(int* arr, int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void merge(int* arr, int start1, int dlina1, int start2, int dlina2, int num)
{
	int* tmp = new int[dlina1]; 
	memcpy(tmp, &arr[start1], sizeof(int) * (dlina1)); 
	int fIndex = 0;
	int sIndex = start2;
	int i = start1;
	while (i < start2 + dlina2 - 1)  
	{								
		if (arr[sIndex] > tmp[fIndex])
		{
			arr[i] = tmp[fIndex];
			++fIndex;
			fIndex = min(fIndex, dlina1);
		}
		else if (arr[sIndex] <= tmp[fIndex])
		{
			arr[i] = arr[sIndex];
			++sIndex;
			sIndex = min(sIndex, start2 + dlina2);
		}
		if (sIndex == start2 + dlina2)
		{
			if (fIndex != dlina1)
			{
				memcpy(&arr[i + 1], &tmp[fIndex], sizeof(int) * (dlina1 - fIndex));
				i = start2 + dlina2;
			}
		}
		if (fIndex == dlina1)
		{
			i = start2 + dlina2;
		}
		++i;
		
	}
	delete[] tmp;
}

void timsort(int* arr, int N)
{
	int minrun = runMinrun(N);
	vector <Range> Stack;
	int currIndex = 0;
	while (currIndex < N - 1)
	{
		int currRunIndex = currIndex;
		int nextIndex = currRunIndex + 1;
		if (arr[currRunIndex] > arr[nextIndex]) 
		{
			swap(arr[currRunIndex], arr[nextIndex]); 
		}

		bool nxt = true;
		while (nxt)
		{
			if (arr[currRunIndex] > arr[nextIndex]) 
			{
				nxt = false; 
			}
			if (!(nxt) && (currRunIndex - currIndex < minrun)) 
			{
				nxt = true;
			}
			if (currRunIndex == N - 1)
			{
				nxt = false;
			}
			if (nxt)
			{
				++currRunIndex;
				++nextIndex;
			}
		}
		insert(arr, currIndex, currRunIndex + 1, N);
		Range r;
		r.start = currIndex;
		r.dlina = currRunIndex - currIndex;
		Stack.push_back(r);
		currIndex = currRunIndex;
	}

	while (Stack.size() > 1)
	{
		Range x = Stack.at(0);
		Stack.erase(Stack.begin());
		Range y = Stack.at(0);
		Stack.erase(Stack.begin());
	
		if (x.start > y.start)
		{
			swap(x.start, y.start);
			swap(x.dlina, y.dlina);
		}
		if (y.start != x.start + x.dlina)
		{
			Stack.push_back(y);
			Stack.push_back(x);
			continue;
		}
		merge(arr, x.start, x.dlina, y.start, y.dlina, N); 
		x.dlina = x.dlina + y.dlina; 
		Stack.push_back(x);	
	}
}
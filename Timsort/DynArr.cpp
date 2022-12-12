#include <iostream>

using namespace std;

int* createArr(int*& arr, int num)
{
	arr = new int[num];
	return arr;
}

int* fillArrayRand(int*& arr, int num)
{
	for (int i = 0; i < num; i++)
	{
		arr[i] = rand() % 1000 + 1;
	}
	return arr;
}

void printArr(int* arr, int num)
{
	system("cls");
	for (int i = 0; i < num; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;
}

void deleteArr(int* arr)
{
	delete[] arr;
}
#include <iostream>

using namespace std;

int* createArr(int*& array, int num);
int* fillArrayRand(int*& array, int num);
void printArr(int* array, int num);
void deleteArr(int* array);
void timsort(int* array, int N);

int main()
{
	zanovo:
	setlocale(LC_ALL, "rus");
		clock_t start, end;
		std::system("cls");
		cout << "выборка" ;
		int num;
		int* array = NULL;
		cin >> num;
		createArr(array, num);
		fillArrayRand(array, num);
		cout << "Сортировка... \n";
		start = clock();
		timsort(array, num);
		end = clock();
		printf("Время: %.4f \n", ((double)end - start) / ((double)CLOCKS_PER_SEC));
		system("pause");
		goto zanovo;
	return 0;
}

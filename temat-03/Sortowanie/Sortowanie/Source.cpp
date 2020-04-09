#include <iostream>
#include <ctime>
using namespace std;

void buble(int T[], const int x);
void wybor(int T[], const int x);
void wstawianie(int T[], const int n);

int main()
{
	const int n = 10;
	int TAB[n];
	srand(time(0));
	cout << "Oto twoja tablica:" << endl;
	for (int i = 0;i < n;i++)
	{
		TAB[i] = rand() % 100;
		cout << TAB[i]<<endl;
	}


	//buble(TAB, n);
	wybor(TAB, n);
	//wstawianie(TAB, n);
	
		
	cout << "Posortowana tablica:" << endl;
	for (int i = 0;i < n;i++)
	{
		cout << TAB[i] << endl;
	}
	cin.get();
	return 0;
}


void buble(int TAB[], const int n)
{
	int k = n - 1;
	for (int j = 0; j < n - 1;j++)
	{
		for (int i = 0;i < k;i++)
		{
			if (TAB[i + 1] < TAB[i])
				swap(TAB[i + 1], TAB[i]);
		}
		k--;
	}
}

void wybor(int T[], const int n)
{
	for (int j = 0;j <n;j++)
	{
		int min = j;
		for (int i =1;i < n;i++)
		{
			if (T[i] < T[min])
				min = i;
		}
		if (T[j] > T[min])
			swap (T[j], T[min]);
	}

}

void wstawianie(int T[], const int n)
{
	for (int j = 1;j < n ;j++)
	{
		for (int i = j; i > 0;i--)
			if (T[i - 1]>T[i])	swap(T[i - 1], T[i]);


	}

}
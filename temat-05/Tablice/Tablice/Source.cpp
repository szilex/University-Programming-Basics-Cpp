#include <iostream>

void Buble(int T[], const int x);

using namespace std;

int main()
{
	cout << "Wprowadz wielkosc tablicy:" << endl;
	const int x=10;
	int TAB[x];
	cout << "Podaj liczby:" << endl;
	for (int i = 0; i < x; i++) 
		cin >> TAB[i];
	Buble(TAB, x);
	for (int i = 0; i < x; i++)
		cout << TAB[i];

	return 0;
}


void Buble(int T[], const int x)
{
	int k = x - 1;
	for (int i = 0;i < k; i++, k--)
	{
		if (T[i + 1] > T[i])
			swap(T[i + 1], T[i]);
	}


}

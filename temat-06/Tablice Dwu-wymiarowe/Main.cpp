#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	const int n = 4;
	int TAB[n][n] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	for (int j = 0;j < 4;j++) 
	{
		for (int i = 0;i < 4;i++)
		{
			cout << TAB[j][i] << '\t';
		}
		cout << endl;
	}
	cout << endl << endl;

	for (int j = 0;j < 4;j++)
	{
		for (int i = 0;i < 4;i++)
		{
			if (i > j)
				swap(TAB[j][i], TAB[i][j]);
		}
	}

	for (int j = 0;j < 4;j++)
	{
		for (int i = 0;i < 4;i++)
		{
			cout << TAB[j][i] << '\t';
		}
		cout << endl;
	}
	cout << endl << endl;

	srand(time(0));
	int T[n][n];
	for (int j = 0;j < 4;j++)
	{
		for (int i = 0;i < 4;i++)
		{
			T[j][i] = rand() % 100;
			cout << T[j][i] << '\t';
		}
		cout << endl;
	}


	int sumaw[n] = { 0,0,0,0 }, sumak[n] = { 0,0,0,0 }, maxw, maxk;
	for (int j = 0;j < 4;j++)
	{
		for (int i = 0;i < 4;i++)
		{
			sumaw[j] += T[j][i];
			sumak[j] += T[i][j];
		}
	}
	cout << endl;
	cout << "Suma wierszy:"<< endl;
	for (int j = 0;j < 4;j++)
	{
		cout << sumaw[j] << endl;
	}
	cout << endl;
	cout << "Suma kolumn:" << endl;
	for (int j = 0;j < 4;j++)
	{
		cout << sumak[j] << endl;
	}
	cout << endl;

	string TABLICA[7][3] = { "A","B", "A", "C", "A", "B", "A", "A", "B", "A", "B", "A", "B", "A", "C", "A", "A", "B", "C","A","B" };
	for (int j = 0;j < 7;j++)
	{
		for (int i = 0;i < 3;i++)
		{
			if (TABLICA[j][i]=="B")

		}
	}







	cin.get();
	return 0;
}

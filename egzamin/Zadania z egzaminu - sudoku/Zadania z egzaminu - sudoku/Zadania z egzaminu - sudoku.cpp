#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool check(string nazwa);

int main()
{
	string nazwa = "sudoku.txt";
	if (check(nazwa))
		cout << "Hurra";
	else "Niestety nie";
	cin.get();
    return 0;
}

bool check(string nazwa)
{
	ifstream plik;
	plik.open(nazwa);
	int sudoku[9][9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		string bufor;
		plik >> bufor;
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = (int)(bufor[j]-'0');	//Konwersja z char na int (liczby w ASCII od 48('0')
			cout << sudoku[i][j] << '\t';
		}
		cout << endl;
	}

	for (int i = 0; i < 9; i++)
	{
		bool kolumny[10] = { 0 };
		bool wiersze[10] = { 0 };
		kolumny[0] = wiersze[0] = 1;
		for (int j = 0; j < 9; j++)
		{
			kolumny[sudoku[j][i]] = 1;	//Jezeli liczba wystapi, to wpisujemy 1 do tablicy
			wiersze[sudoku[i][j]] = 1;	//Jak cos sie powtorzy, to gdzies bedzie 0;
		}
		for (int k = 1; k < 10; k++)
		{
			if (!kolumny[k] || !wiersze[k])
				return false;
		}
		for (int i = 0; i < 9; i += 3)
		{
			for (int j = 0; j < 9; j += 3)
			{
				bool liczby[10] = { 0 };
				for (int k = i; k < i + 3; k++)
				{
					for (int l = j; l < j + 3; l++)
						liczby[sudoku[k][l]] = 1;
				}
				for (int m = 1; m < 10; m++)
					if (!liczby[m])
						return false;
			}
		}
	}
	return true;
}
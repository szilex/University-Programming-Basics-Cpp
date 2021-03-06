#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool sprawdz(const string &nazwa);

int main()
{
	const string nazwa = "plansza.txt";
	if (sprawdz(nazwa))
		cout << "Correct!";
	else
		cout << "Wrong:(";

	cin.get();
    return 0;
}

bool sprawdz(const string &nazwa)
{
	ifstream plik;
	plik.open(nazwa);
	if (plik.is_open())
	{
		bool plansza[8][8] = { 0 };
		for (int j=0; j<8 && !plik.eof();j++)
		{
			string wiersz;
			plik >> wiersz;
			cout << wiersz <<endl;
			for (int i = 0; i < 8; i++)
			{
				if (wiersz[i] == 'H')
					plansza[j][i] = 1;
			}
		}
		plik.close();
		for (int j = 0; j < 8; j++)
		{
			int licznik_wiersz = 0, licznik_kolumna = 0;
			for (int i = 0; i < 8; i++)
			{
				if (plansza[j][i] == 1)
					licznik_wiersz++;
				if (plansza[i][j] == 1)
					licznik_kolumna++;
				int licznik_przekatna = 0;
				if (i == 0 || j == 0)
				{
					for (int k = 0; i + k < 8 && j + k < 8; k++)
					{
						if (plansza[j + k][i + k] == 1)
							licznik_przekatna++;
					}
				}
				if (licznik_przekatna > 1)//Może być 0 lub 1
					return false;

			}
			if (licznik_kolumna != 1 || licznik_wiersz != 1)
				return false;
		}
		return true;
	}
	else 
		return false;
}
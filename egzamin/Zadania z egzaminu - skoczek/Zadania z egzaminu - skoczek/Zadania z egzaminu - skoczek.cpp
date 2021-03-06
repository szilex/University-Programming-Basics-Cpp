#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool correct(string nazwa);


int main()
{
	string nazwa = "plansza.txt";
	if (correct(nazwa))
		cout << "Hurra";
	cin.get();
	return 0;
}

bool correct(string nazwa)
{
	ifstream plik;
	plik.open(nazwa);
	if (!plik.is_open())
		return false;
	else
	{
		int tablica[12][12] = { 0 };
		
		for (int i = 2; i < 10; i++)
			for (int j = 2; j < 10; j++)
			{
				char bufor[3];
				plik >> bufor;
				tablica[i][j]=atoi(bufor);
			}

		int liczba = 1;
		int wsp_1, wsp_2;
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				cout << tablica[i][j] << '\t';
				if (tablica[i][j] == liczba)
				{
					wsp_1 = i;		//Wsp beda przechowywac kordynaty elementu liczba-1
					wsp_2 = j;
					liczba++;
				}
			}
			cout << endl;
		}

		for (; liczba <= 64; liczba++)	//Szuka nastepnej liczby w jednym z 8 dozwolonych miejsc
		{								
			if (tablica[wsp_1 - 2][wsp_2 - 1] == liczba)
			{
				wsp_1 -= 2;
				wsp_2 -= 1;
			}
			else 
				if (tablica[wsp_1 - 2][wsp_2 + 1] == liczba)
				{
					wsp_1 -= 2;
					wsp_2 += 1;
				}
				else 
					if (tablica[wsp_1 - 1][wsp_2 - 2] == liczba)
					{
						wsp_1 -= 1;
						wsp_2 -= 2;
					}
					else
						if (tablica[wsp_1 - 1][wsp_2 + 2] == liczba)
						{
							wsp_1 -= 1;
							wsp_2 += 2;
						}
						else
							if (tablica[wsp_1 + 1][wsp_2 - 2] == liczba)
							{
								wsp_1 += 1;
								wsp_2 -= 2;
							}
							else
								if (tablica[wsp_1 + 1][wsp_2 + 2] == liczba)
								{
									wsp_1 += 1;
									wsp_2 += 2;
								}
								else
									if (tablica[wsp_1 + 2][wsp_2 - 1] == liczba)
									{
										wsp_1 += 2;
										wsp_2 -= 1;
									}
									else
										if (tablica[wsp_1 + 2][wsp_2 + 1] == liczba)
										{
											wsp_1 += 2;
											wsp_2 += 1;
										}
										else
											return false;
		}
	}
	return true;
}
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void sprawdz(const string &wejscie, const string &wyjscie);


int main()
{
	string nazwa1 = "wyrazy.txt";
	string nazwa2 = "wyniki.txt";
	sprawdz(nazwa1, nazwa2);
	cin.get();
    return 0;
}

void sprawdz(const string &wejscie, const string &wyjscie)
{
	ifstream plik_we;
	plik_we.open(wejscie);
	if (plik_we.is_open())
	{
		ofstream plik_wy;
		plik_wy.open(wyjscie);
		string podslowo, slowo;

		while (!plik_we.eof())
		{
			plik_we >> podslowo >> slowo;
			int dlugosc_podslowa = podslowo.length();
			int dlugosc_slowa = slowo.length();
			bool znaleziono(0);
			for (int i = 0; i < dlugosc_slowa&&!znaleziono; i++)
			{
				if (slowo[i] == podslowo[0])
				{
					if (i + dlugosc_podslowa <= dlugosc_slowa)
					{
						string kandydat = slowo.substr(i, dlugosc_podslowa);
						if (kandydat == podslowo)
						{
							plik_wy << "true" << endl;
							znaleziono = 1;
						}
					}
					else
						break;
				}
			}
			if (!znaleziono)
				plik_wy << "false" << endl;
		}
		plik_wy.close();
	}
	plik_we.close();
}
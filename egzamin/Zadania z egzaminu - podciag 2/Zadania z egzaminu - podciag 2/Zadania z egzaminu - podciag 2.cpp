#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void najdluzszy(const string &wejscie, const string &wyjscie);



int main()
{
	string nazwa = "wyrazy.txt";
	string wyjscie = "wyniki.txt";
	najdluzszy(nazwa, wyjscie);
	cin.get();
    return 0;
}

void najdluzszy(const string &wejscie, const string &wyjscie)
{
	ifstream plik_we;
	plik_we.open(wejscie);
	if (plik_we.is_open())
	{
		ofstream plik_wy;
		plik_wy.open(wyjscie);
		while (!plik_we.eof())
		{
			string slowo1, slowo2;
			plik_we >> slowo1 >> slowo2;
			int dlugosc1 = slowo1.length(), dlugosc2 = slowo2.length();
			int najdluzszy = 0, pozycja = 0;
			for (int i = 0; i < dlugosc1; i++)
			{
				int pozycja1 = 0, pozycja2 = 0, dlugosc_podciagu = 0;
				for (int j = 0; j < dlugosc2; j++)
				{
					if (slowo1[i] == slowo2[j])
					{
						pozycja1 = i;
						pozycja2 = j;
						dlugosc_podciagu = 1;
						if (dlugosc_podciagu > najdluzszy)	//Potrzebne jak najdluzszy==0, a wspolna jest jedna litera;
						{
							najdluzszy = dlugosc_podciagu; 
							pozycja = pozycja1;
						}
						while (true)
						{
							if (pozycja1 + dlugosc_podciagu <= dlugosc1 && pozycja2 + dlugosc_podciagu <= dlugosc2)
							{
								if (slowo1[pozycja1 + dlugosc_podciagu] == slowo2[pozycja2 + dlugosc_podciagu])
								{
									dlugosc_podciagu++;
									if (dlugosc_podciagu > najdluzszy)
									{
										najdluzszy = dlugosc_podciagu;
										pozycja = pozycja1;
									}
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
			}
			plik_wy << slowo1.substr(pozycja, najdluzszy) << endl;
		}
		plik_wy.close();
	}
	plik_we.close();
}
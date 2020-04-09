#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

void stats(ifstream& nazwa, string napis);

using namespace std;

int main()
{
	ifstream plik;
	plik.open("statystyka.txt", ios::in);
	string napis;
	stats(plik, napis);
	plik.close();
	cin.get();
    return 0;
}


void stats(ifstream& nazwa, string napis)
{
		while (!nazwa.eof())
		{
			getline(nazwa, napis);
			cout << napis << endl;
		}
}

/*
1. Funkcja(nazwa pliku)
Statystyka liter w pliku
2. Zliczenie najdluzszego ciagu tego samego znaku
3. Funkcja(nazwy 2 plikow txt)
Wypisac litery, ktorych sa w plik1, a nie ma w plik2
4. Funkcja (nazwy 3 plikow)
Plik1 i plik2 zawieraja posortowane liczby typu int
Polaczyc plik1 i plik2 i zapisac do plik 3 (liczby maja byc posortowane
*/


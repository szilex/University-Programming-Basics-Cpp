#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void stats(ifstream &nazwa, char tab[], int ilosc[]);
void zlicz(ifstream &nazwa, char tab[], int najw[]);
void jestaleniema(ifstream &nazwa,  char tab[], bool jest[]);

int main()
{
	/*ifstream plik;
	plik.open("C:/Users/Michał/Desktop/statystyka.txt", ios::in);
	char tablica[27];
	for (int i = 0; i<27; i++)
		tablica[i] = 97 + i;
	int ilosc[26] = { 0 };
	stats(plik, tablica, ilosc);
	plik.close();*/


	/*ifstream plik2;
	plik2.open("C:/Users/Michał/Desktop/ciagi.txt", ios::in);
	char tablica2[27];
	for (int i = 0; i<27; i++)
		tablica2[i] = 97 + i;
	int ilosc2[26] = { 0 };
	zlicz(plik2, tablica2, ilosc2);
	plik2.close();*/

	ifstream plik3;
	plik3.open("C:/Users/Michał/Desktop/tusa.txt", ios::in);
	char tablica3[27];
	for (int i = 0; i<27; i++)
		tablica3[i] = 97 + i;
	bool jest[26];
	for (int i = 0; i < 26; i++)
		jest[i] = false;
	jestaleniema(plik3, tablica3, jest);
	
	cin.get();
	return 0;
}


void stats(ifstream &nazwa, char tab[], int ilosc[])
{
	while (!nazwa.eof())
	{
		string napis;
		getline(nazwa, napis);
		cout << napis << endl;
		for (int i = 0; i < napis.length(); i++ )
			for (int j = 0; j < 26; j++)
			{
				if (napis[i] == tab[j])
					ilosc[j]+=1;
			}
	}
	for (int i = 0; i < 26; i++)
	{
		cout << tab[i] << "*" << ilosc[i] << ", ";
	}
}

void zlicz(ifstream &nazwa,char tab[], int najw[])
{
	while (!nazwa.eof())
	{
		string napis;
		getline(nazwa, napis);
		cout << napis << endl;
		for (int i = 0, licznik=1; i < napis.length(); i++)
		{
			int j = 0;
			for (; j < 26; j++)
			{
				if (napis[i] == tab[j])
					break;
			}
			if (i + 1 == napis.length())
			{
				if (licznik > najw[j])
					najw[j] = licznik;
				licznik = 1;
				break;
			}
			else
			{
				if (napis[i] == napis[i + 1])
				{
					licznik++;
				}
				else
				{
					if (licznik > najw[j])
						najw[j] = licznik;
					licznik = 1;
				}
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		cout << tab[i] << "*" << najw[i] << ", ";
	}
}

void jestaleniema(ifstream &nazwa,  char tab[], bool jest[])
{
	while (!nazwa.eof())
	{
		string napis;
		getline(nazwa, napis);
		cout << napis << endl;
		for (int i = 0; i < napis.length(); i++)
			for (int j = 0; j < 26; j++)
			{
				if (napis[i] == tab[j])
				{
					jest[j] = true;
					break;
				}
			}
	}
	
	cout << "Litery, ktorych nie ma w 1 pliku: ";
	for (int i = 0; i < 26; i++)
	{
		if (!jest[i])
			cout << tab[i] << ", ";
	}
	
	nazwa.close();
	ofstream plik4;
	plik4.open("C:/Users/Michał/Desktop/tuniema.txt", ios::out);
	plik4 << "Litery, ktorych nie ma w 1 pliku: ";
	for (int i = 0; i < 26; i++)
	{
		if (jest[i] == false)
			plik4 << tab[i] << ", ";
	}
	plik4.close();
}

/*
1. Funkcja(nazwa pliku)
Statystyka liter w pliku
2. Zliczenie najdluzszego ciagu tego samego znaku
3. Funkcja(nazwy 2 plikow txt)
Wypisac litery, ktorych sa w plik1, a nie ma w plik2
4. Funkcja (nazwy 3 plikow)
Plik1 i plik2 zawieraja posortowane liczby typu int
Polaczyc plik1 i plik2 i zapisac do plik 3 (liczby maja byc posortowane)
*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

struct Obiekt
{
	double wsp_x;
	double wsp_y;
	unsigned int etykieta;
};

int wczytajObiekty(const string& wejscie, Obiekt obiekty[]);
double odleglosc(double x1, double x2, double y1, double y2);
void knn(const Obiekt treningowy[], int n, Obiekt& Q, int k);

int main()
{
	const string wejscie = "liczby.txt";
	Obiekt obiekty[6];
	wczytajObiekty(wejscie, obiekty);
	cin.get();
	return 0;
}

int wczytajObiekty(const string& wejscie, Obiekt obiekty[])
{
	ifstream plik;
	plik.open(wejscie, ios::binary);
	if (!plik.is_open())
		return -1;

	plik.seekg(0, ios::end);
	bool not_empty = plik.tellg();
	plik.seekg(0, ios::beg);
	if (!not_empty)
		return 0;

	int counter = 0;
	for (int i = 0; !plik.eof(); i++, counter++)
	{
		double x, y;
		unsigned int val;
		plik >> x >> y >> val;
		obiekty[i] = { x,y,val };
		cout << obiekty[i].wsp_x << '\t' << obiekty[i].wsp_y << '\t' << obiekty[i].etykieta << endl;
	}
	plik.close();
	return counter;

}

double odleglosc(double x1, double x2, double y1, double y2) //Tylko wspolrzedne, etykiet nie trzeba
{
	double wynik;
	wynik = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	cout << wynik << endl;
	return wynik;
}

void knn(const Obiekt treningowy[], int n, Obiekt& Q, int k)
{
	double *odleglosci = new double[n];
	for (int i = 0; i < n; i++)
	{
		odleglosci[i] = odleglosc(Q.wsp_x, treningowy[i].wsp_x, Q.wsp_y, treningowy[i].wsp_y);
	}
	Obiekt *najblizsze = new Obiekt[k];
	for (int i = 0; i < k; i++)
	{
		double minimum = odleglosci[i];
		int indeks = i;
		for (int j = i; j < n; j++)
		{
			if (odleglosci[j] < minimum)
			{
				minimum = odleglosci[j];
				indeks = j;
			}
			odleglosci[indeks] = odleglosci[i];
			odleglosci[i] = minimum;
		}
		najblizsze[i] = treningowy[indeks];
	}

	unsigned int *etykiety = new unsigned int[k];
	for (int i = 0; i < k; i++)
	{
		etykiety[i] = najblizsze[i].etykieta;
	}

	for (int i = 0; i < k; i++)   //Sortowanie etykiet przez wybieranie (rosnaco)
	{
		unsigned int minimum = etykiety[i];
		int indeks = i;
		for (int j = i; j<k; j++)
		{
			if (etykiety[j] < minimum)
			{
				minimum = etykiety[j];
				indeks = j;
			}
		}
		etykiety[indeks] = etykiety[i];
		etykiety[i] = minimum;
	}

	unsigned int aktualna_etykieta = etykiety[0];
	int licznik = 0;
	int maks_wystapien = 0;
	unsigned int najczestsza_etykieta;
	for (int i = 0; i < k; i++)
	{
		if (etykiety[i] == aktualna_etykieta)
		{
			licznik++;
			if (licznik > maks_wystapien)
			{
				maks_wystapien = licznik;
				najczestsza_etykieta = etykiety[i];
			}
		}
		else
		{
			aktualna_etykieta = etykiety[i];
			licznik = 1;
		}
	}
	Q.etykieta = najczestsza_etykieta;
}
#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

bool przestepny(int rok)
{
	if (rok % 4 == 0 && rok % 100 != 0 || rok % 400 == 0)
		return true;
	else
		return false;
}
void kalendarz(int &rok, const string &plik_nazwa)
{
	string tydzien[7] = { "pn","wt","sr","cz","pt","sb","nd" };
	int numer_dnia_tygodnia;
	int il_dni_mies;
	ofstream plik;
	plik.open(plik_nazwa);
	for (int i = 1; i <= 12; i++)
	{
		plik << "miesiac"/*nazwa_miesiaca(i);*/ << " " << rok << endl;
		for (int j = 0; j < 7; j++)
		{
			plik << tydzien[j] << " ";
		}
		plik << endl;
		numer_dnia_tygodnia = 2;/*dzien_tygodnia(rok,i,1);*/
		switch (i)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			il_dni_mies = 31;
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11:
		{
			il_dni_mies = 30;
			break;
		}
		case 2:
		{
			if (przestepny)
				il_dni_mies = 29;
			else
				il_dni_mies = 28;
		}
		}
		for (int k = 1; k < numer_dnia_tygodnia; k++)
		{
			plik << "   ";
		}
		for (int l = 1; l <= il_dni_mies; l++)
		{
			plik << setw(2) << l << " ";
			if ((numer_dnia_tygodnia + l-1) % 7 == 0)
				plik << endl;
		}
		plik << endl << endl;
	}

	plik.close();

}

int main()
{
	int rok = 2018;
	string plik_nazwa = "kal";
	kalendarz(rok, plik_nazwa);
	cin.get();
	return 0;
}
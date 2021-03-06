#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct stGenom
{
	double gen;
	stGenom* pNast;
};

struct stBakteria
{
	string nazwa;
	stBakteria* pNast;
	stGenom* pGenom;
};

void dodaj(stGenom*&pGenom, stGenom* pFragment);
stGenom* wytnij(stGenom*&pGenom, int ile);
void znajdzNajlepszaNajgorszaBakterie(stBakteria*pGlowa, stBakteria*& pNajgorsza, stBakteria*&pNajlepsza);
void krzyzuj(stBakteria *pGronkowiec, stBakteria * pPaciorkowiec);
double ocen(stGenom *pGenom);
int ile(stGenom* pGenom);


int main()
{
	return 0;
}

void dodaj(stGenom*&pGenom, stGenom* pFragment)
{
	stGenom* tmp = pGenom;
	while (tmp->pNast != pGenom)
		tmp = tmp->pNast;
	tmp->pNast = pFragment;
	stGenom* tmp2 = tmp;
	while (tmp2->pNast != nullptr)
		tmp2 = tmp2->pNast;
	tmp2->pNast = pGenom;
	pGenom = tmp->pNast;
}

stGenom* wytnij(stGenom*&pGenom, int ile)
{
	//################# Sprawdzenie czy ile nie jst wieksze od dlugoci genomu
	int counter = 1;
	stGenom* tmp = pGenom;
	while (tmp->pNast != pGenom)
	{
		tmp = tmp->pNast;
		counter++;
	}
	if (counter <= ile)
		ile = counter - 1;
	//###################
	counter = 0;
	tmp = pGenom;
	while (counter < ile)
	{
		tmp = tmp->pNast;
		counter++;
	}
	stGenom* tmp2 = tmp->pNast;
	while (tmp2->pNast != pGenom)
		tmp2 = tmp2->pNast;
	tmp2->pNast = tmp->pNast;
	tmp2 = pGenom;
	pGenom = tmp->pNast;
	tmp->pNast = nullptr;
	return tmp2;
}

void znajdzNajlepszaNajgorszaBakterie(stBakteria* pGlowa, stBakteria* &pNajgorsza, stBakteria* &pNajlepsza)
{
	double maks = ocen(pGlowa->pGenom), min = ocen(pGlowa->pGenom);
	pNajgorsza = pNajlepsza = pGlowa;
	pGlowa = pGlowa->pNast;
	while (pGlowa != nullptr)
	{
		double ocena = ocen(pGlowa->pGenom);
		if (ocena < min)
		{
			min = ocena;
			pNajgorsza = pGlowa;
		}
		else
		{
			if (ocena > maks)
			{
				maks = ocena;
				pNajlepsza = pGlowa;
			}
		}
	}
}

void krzyzuj(stBakteria *pGronkowiec, stBakteria * pPaciorkowiec)
{
	int ilosc_gron = floor(ile(pGronkowiec->pGenom) / 2), ilosc_pacior = floor(ile(pPaciorkowiec->pGenom) / 2);
	stGenom* frag_gron = wytnij(pGronkowiec->pGenom, ilosc_gron);
	stGenom* frag_pacior = wytnij(pPaciorkowiec->pGenom, ilosc_pacior);
	dodaj(pGronkowiec->pGenom, frag_pacior);
	dodaj(pPaciorkowiec->pGenom, frag_gron);
}
double ocen(stGenom *pGenom)
{

}
int ile(stGenom* pGenom)
{

}
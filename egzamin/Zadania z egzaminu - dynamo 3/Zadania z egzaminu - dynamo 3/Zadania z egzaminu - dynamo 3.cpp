#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct Towar
{
	string nazwa;
	double cena;
	Towar *pPrev, *pNext;
};

struct Klient
{
	string imie, nazwisko;
	Towar *pZakupy;
	Klient *pLewy, *pPrawy;
};

void dodaj(double cena, string nazwa, Klient* &head, string imie, string nazwisko);
void wypisz_drzewo(Klient* head);

int main()
{

	Klient* head = new Klient;
	head->imie = "Marek";
	head->nazwisko = "Nowak";
	head->pZakupy = nullptr;
	head->pLewy = head->pPrawy = nullptr;
	dodaj(32.70, "Mleko", head, "Michał", "Szeler");
	wypisz_drzewo(head);
	cin.get();
	return 0;
}

void dodaj(double cena, string nazwa, Klient* &head, string imie, string nazwisko)
{
	Klient* pom = head;
	bool znaleziony = false;
	while (!znaleziony)
	{
		if (nazwisko < pom->nazwisko)
		{
			if (pom->pLewy != nullptr)
				pom = pom->pLewy;
			else
			{
				pom->pLewy = new Klient;
				pom = pom->pLewy;
				pom->imie = imie;
				pom->nazwisko = nazwisko;
				pom->pLewy = pom->pPrawy = nullptr;
				pom->pZakupy = new Towar;
				pom->pZakupy->nazwa = nazwa;
				pom->pZakupy->cena = cena;
				pom->pZakupy->pNext = pom->pZakupy->pPrev = nullptr;
				znaleziony = true;
			}
		}
		else
			if (nazwisko > pom->nazwisko)
				if (pom->pPrawy != nullptr)
					pom = pom->pPrawy;
				else
				{
					pom->pPrawy = new Klient;
					pom = pom->pPrawy;
					pom->imie = imie;
					pom->nazwisko = nazwisko;
					pom->pLewy = pom->pPrawy = nullptr;
					pom->pZakupy = new Towar;
					pom->pZakupy->nazwa = nazwa;
					pom->pZakupy->cena = cena;
					pom->pZakupy->pNext = pom->pZakupy->pPrev = nullptr;
					znaleziony = true;
				}
			else
			{
				if (imie < pom->imie)
				{
					if (pom->pLewy != nullptr)
						pom = pom->pLewy;
					else
					{
						pom->pLewy = new Klient;
						pom = pom->pLewy;
						pom->imie = imie;
						pom->nazwisko = nazwisko;
						pom->pLewy = pom->pPrawy = nullptr;
						pom->pZakupy = new Towar;
						pom->pZakupy->nazwa = nazwa;
						pom->pZakupy->cena = cena;
						pom->pZakupy->pNext = pom->pZakupy->pPrev = nullptr;
						znaleziony = true;
					}
				}
				else
				{
					if (imie > pom->imie)
					{
						if (pom->pPrawy != nullptr)
							pom = pom->pPrawy;
						else
						{
							pom->pPrawy = new Klient;
							pom = pom->pPrawy;
							pom->imie = imie;
							pom->nazwisko = nazwisko;
							pom->pLewy = pom->pPrawy = nullptr;
							pom->pZakupy = new Towar;
							pom->pZakupy->nazwa = nazwa;
							pom->pZakupy->cena = cena;
							pom->pZakupy->pNext = pom->pZakupy->pPrev = nullptr;
							znaleziony = true;
						}
					}
					else
					{
						if (pom->pZakupy == nullptr)
						{
							pom->pZakupy = new Towar;
							pom->pZakupy->nazwa = nazwa;
							pom->pZakupy->cena = cena;
							pom->pZakupy->pNext = pom->pZakupy->pPrev = nullptr;
						}
						else
						{
							Towar* pom2 = pom->pZakupy;
							while (pom2 != nullptr)
							{
								if (cena < pom2->cena)
									if (pom2->pPrev != nullptr)
										if (cena > pom2->pPrev->cena)
										{
											pom2->pPrev->pNext = new Towar;
											pom2->pPrev->pNext->pNext = pom2;
											pom2->pPrev->pNext->pPrev = pom2->pPrev;
											pom2 = pom2->pPrev->pNext;
											pom2->pNext->pPrev = pom2;
											znaleziony = true;
										}
										else
											pom2 = pom2->pPrev;
									else
									{
										pom2->pPrev = new Towar;
										pom2 = pom2->pPrev;
										pom2->cena = cena;
										pom2->nazwa = nazwa;
										pom2->pPrev = pom2->pNext = nullptr;
										znaleziony = true;
									}
								else
									if (pom2->pNext != nullptr)
										if (cena < pom2->pNext->cena)
										{
											pom2->pNext->pPrev = new Towar;
											pom2->pNext->pPrev->pPrev = pom2;
											pom2->pNext->pPrev->pNext = pom2->pNext;
											pom2 = pom2->pNext->pPrev;
											pom2->pPrev->pNext = pom2;
											znaleziony = true;
										}
										else
											pom2 = pom2->pNext;
							}
						}
						znaleziony = true;
					}
				}



			}
	}
}

void wypisz_drzewo(Klient* head)
{
	if (head != nullptr)
	{
		cout << head->imie << " " << head->nazwisko << endl;
		wypisz_drzewo(head->pLewy);
		wypisz_drzewo(head->pPrawy);
	}
}
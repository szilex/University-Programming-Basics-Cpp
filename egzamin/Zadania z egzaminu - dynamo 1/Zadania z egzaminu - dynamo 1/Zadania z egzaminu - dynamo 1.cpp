#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

struct Zadanie
{
	int priorytet;
	string tresc_zadania;
	Zadanie *pLewy, *pPrawy;
};

struct Pracownik
{
	string nazwisko;
	Pracownik *pPrev, *pNext;
	Zadanie *pZadania;
};

Pracownik* znajdzLubDodajPracownika(Pracownik* &pHead, Pracownik* &pTail, string surname);
void dodajZadanie(Zadanie* &pZadania, int priorytet, string tresc);
void dodajZadaniePracownikowi(string tresc, int priorytet, Pracownik* &pHead, Pracownik* &pTail, string surname);
void usunPracownikowBezZadan(Pracownik* &pHead, Pracownik* &pTail);
void odwrocKolejnoscPracownikow(Pracownik* &pHead, Pracownik* &pTail);

int main()
{
	Pracownik * pHead = new Pracownik;
	pHead->nazwisko = "Harmak";
	pHead->pPrev = nullptr;
	pHead->pZadania = nullptr;
	pHead->pNext = new Pracownik;
	pHead->pNext->nazwisko = "Nowak";
	pHead->pNext->pPrev = pHead;
	pHead->pNext->pZadania = nullptr;
	Pracownik * pTail = new Pracownik;
	pTail->nazwisko = "Szeler";
	pTail->pNext = nullptr;
	pTail->pZadania = nullptr;
	pTail->pPrev = pHead->pNext;
	pHead->pNext->pNext = pTail;

	Pracownik* pom = pHead;
	while (pom != nullptr)
	{
		cout << "Pracownik: " << pom->nazwisko << endl;
		pom = pom->pNext;
	}
	pom = pHead;

	Pracownik * tmp = znajdzLubDodajPracownika(pHead, pTail, "Kieslowski");
	dodajZadanie(tmp->pZadania, 4, "Rob cos");

	pom = pHead;
	while (pom != nullptr)
	{
		cout << "Pracownik: " << pom->nazwisko << endl;
		pom = pom->pNext;
	}


	dodajZadaniePracownikowi("Blbabla", 7, pHead, pTail, "Szeler");
	dodajZadaniePracownikowi("afsbsga", 3, pHead, pTail, "Szeler");
	odwrocKolejnoscPracownikow(pHead, pTail);
	pom = pHead;
	while (pom != nullptr)
	{
		cout << "Pracownik: " << pom->nazwisko << endl;
		if (pom->pZadania != nullptr)
			cout << pom->pZadania->tresc_zadania << endl;
		pom = pom->pNext;
	}


	usunPracownikowBezZadan(pHead, pTail);

	pom = pHead;
	while (pom != nullptr)
	{
		cout << "Pracownik: " << pom->nazwisko << endl;
		pom = pom->pNext;
	}


	cin.get();
	return 0;
}

Pracownik* znajdzLubDodajPracownika(Pracownik* &pHead, Pracownik* &pTail, string surname)
{
	Pracownik* tmp = pHead;
	while (tmp != nullptr)
	{
		if (tmp->nazwisko == surname)
			return tmp;
		else tmp = tmp->pNext;
	}
	//Funkcja nie znalazła pracownika o podanym nazwisku
	tmp = pHead;
	while (tmp != nullptr)
	{
		if (tmp->nazwisko < surname)
			tmp = tmp->pNext;
		else
		{
			if (tmp->pPrev != nullptr)
			{
				tmp->pPrev->pNext = new Pracownik;
				tmp->pPrev->pNext->pPrev = tmp->pPrev;
				tmp->pPrev->pNext->pNext = tmp;
				Pracownik* tmp2 = tmp->pPrev->pNext;
				tmp->pPrev = tmp2;
				tmp->pPrev->nazwisko = surname;
				tmp->pPrev->pZadania = nullptr;
				return tmp->pPrev;
			}
			else
			{
				pHead = new Pracownik;
				pHead->pNext = tmp;
				tmp->pPrev = pHead;
				tmp->pPrev->nazwisko = surname;
				tmp->pPrev->pZadania = nullptr;
				return tmp->pPrev;
			}
		}
	}
	//Nazwisko dodawanego pracownika jest wieksze niz dotychczasowe najwieksze
	tmp = pTail;
	tmp->pNext = new Pracownik;
	pTail = tmp->pNext;
	pTail->pPrev = tmp;
	tmp->nazwisko = surname;
	tmp->pZadania = nullptr;
	return tmp;
}

void dodajZadanie(Zadanie* &pZadania, int priorytet, string tresc)
{
	if (pZadania == nullptr)
	{
		pZadania = new Zadanie;
		pZadania->priorytet = priorytet;
		pZadania->tresc_zadania = tresc;
		pZadania->pLewy = pZadania->pPrawy = nullptr;
	}

	else
	{
		if (priorytet < pZadania->priorytet)
			dodajZadanie(pZadania->pLewy, priorytet, tresc);
		else
			dodajZadanie(pZadania->pPrawy, priorytet, tresc);
	}
}

void dodajZadaniePracownikowi(string tresc, int priorytet, Pracownik* &pHead, Pracownik* &pTail, string surname)
{
	Pracownik * tmp;
	tmp = znajdzLubDodajPracownika(pHead, pTail, surname);
	dodajZadanie(tmp->pZadania, priorytet, tresc);
}

void usunPracownikowBezZadan(Pracownik* &pHead, Pracownik* &pTail)
{
	if (pHead != nullptr)
	{
		Pracownik* tmp = pHead;
		while (tmp != nullptr)
		{
			if (tmp->pZadania == nullptr)
			{
				if (tmp->pPrev == nullptr)
				{
					if (tmp->pNext == nullptr)
					{
						delete tmp;
						tmp = pHead = pTail = nullptr;
					}
					else
					{
						pHead = tmp->pNext;
						pHead->pPrev = nullptr;
						Pracownik * tmp2 = tmp;
						tmp = tmp->pNext;
						delete tmp2;

					}
				}
				else
				{
					if (tmp->pNext == nullptr)
					{
						pTail = tmp->pPrev;
						delete tmp;
						pTail->pNext = tmp = nullptr;

					}
					else
					{
						tmp->pPrev->pNext = tmp->pNext;
						tmp->pNext->pPrev = tmp->pPrev;
						Pracownik * tmp2 = tmp;
						tmp = tmp->pNext;
						delete tmp2;
					}
				}
			}
			else
				tmp = tmp->pNext;
		}
	}
}

void odwrocKolejnoscPracownikow(Pracownik* &pHead, Pracownik* &pTail)
{
	Pracownik* poczatek = pHead;
	Pracownik* koniec = pTail;
	while (poczatek != koniec)
	{
		string tmp = koniec->nazwisko;
		koniec->nazwisko = poczatek->nazwisko;
		poczatek->nazwisko = tmp;
		Zadanie * tmp2 = koniec->pZadania;
		koniec->pZadania = poczatek->pZadania;
		poczatek->pZadania = tmp2;
		poczatek = poczatek->pNext;
		if (poczatek != koniec)
			koniec = koniec->pPrev;

	}
}
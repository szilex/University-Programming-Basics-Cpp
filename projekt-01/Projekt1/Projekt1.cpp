#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>

void welcome();
int choose_letter();
void range_of_letters(char first_letter, char range[], const int amount);
void draw_with_duplication(char board[], char letters[]);
void draw_without_duplication(char board[], char letters[]);
void you_won(int counter);
void you_lost(char board[], const int amount, const int six, char answer[], char tries[][6], char guessed_letters[][6]);

using namespace std;

int main()
{
	srand(time(NULL));

	welcome();

	char first_letter;
	first_letter=choose_letter();

	if (first_letter > 96)																									//Zamiana malej litery na duza
		first_letter -= 32;

	const int amount = 10;
	char range[amount + 1];
	range_of_letters(first_letter, range, amount);

	char answer[6];
	int choose_your_destiny = 0;
	while (choose_your_destiny != 1 && choose_your_destiny != 2)															//Wybor trybu gry
	{
		cout << "Co wybierasz?\n1.Tryb trudny(powtorzenia)\n2.Tryb latwy(bez powtorzen)\n\nWybierz 1 lub 2: ";
		cin >> choose_your_destiny;
		switch (choose_your_destiny)
		{
		case 1:	 draw_with_duplication(answer,range); choose_your_destiny = 1; break;										//Stworzenie odpowiedzi trudnej
		case 2:  draw_without_duplication(answer,range); choose_your_destiny = 2; break;									//Stworzenie odpowiedzi latwej
		default: cout << "Niepoprawny klawisz.\n\n"; break;																	//Powtórzenie pytania
		}
	}
	cin.get();
	cout << endl;

	const int six = 6;
	char tries[amount][six] = { 0 };																						//Tablica wprowadzonych znakow
	char guessed_letters[amount][six] = { 0 };																				//Tablica odgadnietych symboli
	for (int j=0;j<amount;j++)
		for (int i=0;i<six-1;i++)
			guessed_letters[j][i]='?';																						//Wypelnienie tablicy ? (moze byc cokolwiek)
	
	for (int counter=0; counter<amount ; counter++)																			//Petla 10 prob
	{
		cout << "Podaj "<< counter+1 << " kombinacje:   ";
		bool correct_try=false;																								//Zmienna blokujaca dalsze wykonywanie dzialan
		string combination;																									//String i getline zapobiegaja wprowadzeniu 
		getline(cin, combination);																							//blednych kombinacji 
		if (combination.length() == 5)																						//Poprawnosc sprawdzana dla 
		{																													//ciagu o dobrej dlugosci
			for (int i = 0; i < six - 1; i++)
			{
				tries[counter][i] = combination[i];																			
				if (tries[counter][i] < range[0] || tries[counter][i]>range[9] && tries[counter][i] < range[0]+32 || tries[counter][i]>range[9]+32)
				{																											//Sprawdzanie czy kombinacja sklada sie
					cout << "Kombinacja zawiera niedozwolone znaki:("<<endl;												//tylko z liter alfabetu(malych i duzych)
					counter--;
					break;
				}
				else
				{
					if (tries[counter][i] > 96)																				//Zamiana malych liter na duze
						tries[counter][i] -= 32;
				}
				if (i == 4)				
					correct_try = true;																						//Jezeli petla dojdzie do konca
			}																												//to kombinacja jest poprawna
		}
		else
		{
			cout << "Wprowadziles niepoprawna kombinacje"<<endl<<endl;
			counter--;
		}

		int dollars = 0;
		int hashes = 0;
		if (correct_try==true)																								//Sprawdzenie liter tylko dla dobrego ciagu
		{
			for (int j = 0; j < six - 1; j++)
			{
				for (int i = 0; i < six - 1; i++)
				{
					if (tries[counter][j] == answer[i])																		//Jezeli element wprowadzonego ciagu jest
					{																										//w odpowiedzi to:
						if (j == i)																							//dla tych samych pozycji w ciagu
						{																									//pojawi sie symbol $
							guessed_letters[counter][j] = '$';
							break;
						}
						else
						{
							if (guessed_letters[counter][j] == '?')															//Dla roznych pozycji i symbolu, ktory nie 
							{																								//zostal jeszze zmodyfikowany pojawi sie #
								guessed_letters[counter][j] = '#';
							}
						}
					}
				}	
			}
			for (int i = 0; i < six - 1; i++)
			{
				if (guessed_letters[counter][i] == '$')																		//Zliczenie $ i #
					dollars++;
				else
				{
					if (guessed_letters[counter][i] == '#')
						hashes++;
				}
			}
			cout << "Rezultat: "<<dollars<<"*$, "<<hashes<<"*#"<<endl<<endl;												//Wyswietlenie rezultatu proby		
		}	
		if (dollars == 5)																									//Zakonczenie programu, jezeli gracz 
		{																													//odgadl kombinacje
			you_won(counter);
			cin.get();
			return 0;
			cout << endl;
		}
	}

	you_lost(answer, amount, six, answer, tries, guessed_letters);
	cin.get();
	return 0;
}


void welcome()																												//Wyswietlanie powitania
{
	cout << "Witaj w grze Master Mind!\n\n" <<
		"Twoim zadaniem jest prawidlowe odgadniecie kombinacji 5 liter w poprawnej kolejnosci.\n" <<
		"Kombinacja jest losowana z ciagu 10 kolejnych liter z alfabetu (przykladowo od A do J)\n\n"<<
		"Przy podawaniu rezultatu dla podanej kombinacji moga pokazac sie nastepujace symbole:\n"<<
		"Symbol $ oznacza, ze litera jest poprawna i jest na wlasciwym miejscu\n" <<
		"Symbol # oznacza, ze litera jest poprawna, ale nie jest na wlasciwym miejscu\n\n";
}

int choose_letter()
{
	char first_letter = '\0';
	cout << "Od jakiej litery ma sie zaczynac ciag? Mozesz wybrac od A do Q: ";
	do
	{
		string letter_one;
		getline(cin, letter_one);
		if (letter_one.length() == 1)
		{
			first_letter = letter_one[0];																					//Wprowadzenie pierwszej littery ciagu
		}
		if (first_letter < 65 || first_letter>81 && first_letter < 97 || first_letter>113)
		{
			cout << "Bledna litera" << endl;																				//Sprawdzenie, czy litera jest z zakresu 
			first_letter = 0;																								//A-Q lub a-q w kodzie ASCII
		}
	} while (!first_letter);
	cout << endl;
	return first_letter;
}

void range_of_letters(char first_letter, char range[], const int amount)
{
	range[0] = first_letter;
	range[amount] = '\0';
	cout << "Przedzial liter to: " << range[0];																				//Wypisanie wybranego przedzialu
	for (int i = 1; i < amount; i++)
	{
		range[i] = first_letter + i;
		cout << ", " << range[i];
	}
	cout << endl << endl;

}

void draw_with_duplication(char board[], char letters[])																	//Losowanie z powtorzeniami 
{
	for (int i = 0,x; i <5; i++)
	{
		x = rand() % 10;
		board[i] = letters[x];
	}
	board[5] = '\0';
}

void draw_without_duplication(char board[], char letters[])																	//Losowanie bez powtorzen
{
	for (int i = 0, x; i <5; i++)
	{
		x = rand() % 10;
		board[i] = letters[x];
		for (int j = 0; j < i; j++)
		{
			if (board[i] == board[j])
			{
				i--;
				break;
			}
		}
	}
	board[5] = '\0';
}

void you_won(int counter)
{
	cout << "Gratulaje!!! Odgadles kombinacje w " << counter + 1 << " probach!!!\n"
		<< "Dziekuje, ze zagrales w gre MASTER MIND";
}

void you_lost(char board[], const int amount, const int six, char answer[], char tries [][6], char guessed_letters [][6] )
{
	cout << "Przykro mi, niestety nie udalo ci sie odgadnac kombinacji\n"													//Zakonczenie programu, jezeli gracz 
		<< "Poprawna kombinacja to: " << answer << endl << endl;																		//nie odgadl kombinacji

	cout << "Historia twoich prob:" << endl;
	for (int i = 0; i < amount; i++)
	{
		cout << "Proba" << i + 1 << ": \t";
		for (int j = 0; j < six-1; j++)
		{
			cout << tries[i][j];
		}
		cout << "\t";
		for (int j = 0; j < six-1; j++)
		{
			cout << guessed_letters[i][j];
		}
		cout << endl;
	}
	cout << endl << "Dziekuje, ze zagrales w gre MASTERMIND";
}
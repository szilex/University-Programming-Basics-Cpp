#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>
using namespace std;

enum days_of_week
{
	Error = 0,
	Monday = 1,
	Tuesday = 2,
	Wednesday = 3,
	Thursday = 4,
	Friday = 5,
	Saturday = 6,
	Sunday = 7,
	End_of_week = 8
};

struct date
{
	int hour;
	int minutes;
};

struct emission
{
	days_of_week day;
	date start;
	date end;
	int hall;
	int total_seats;
	int available_seats;
	emission* next;							//Te dwa wskaźniki łączą elementy tego samego filmu w kolejności puszczania z całego tygodnia;
	emission* prev;
	emission* next_hall;					//Te dwa wskaźniki łączą elementy z tej samej sali z całego tygodnia;
	emission* prev_hall;
	emission* next_week;					//Te dwa wskazniki łączą elementy z całego tygodnia w kolejnosci puszczania;
	emission* prev_week;
};

struct movie
{
	string name;
	double length;
	movie* next;
	movie* prev;
	emission* emissions;				//Każdy film zawiera listę swoich spektakli
};

typedef movie* wsk_movie;
typedef emission* wsk_emission;

void show_emissions(wsk_movie head, bool only_with_seats);
void show_hall(wsk_emission hall);
void show_free_halls(days_of_week day, wsk_emission week, bool *&free_halls, date current_time, double length);
void show_movie(wsk_emission emissions, bool only_with_seats);
void show_day(days_of_week day);
void show_dzien(days_of_week day);
bool correct_name(string name);
bool correct_hour(date current_time);
int* create_cinema(ifstream &file);
void create_from_file(wsk_movie &movies, wsk_emission *&wsk_halls, wsk_emission &week, string days[], int *&table);
void safe_to_file(wsk_movie &head, int *halls);
bool hall_is_free(wsk_emission &wsk_halls, days_of_week day, date start_of_emission, date end_of_emission);
days_of_week day_string_to_enum(string day, string table[]);
void add_movie(wsk_movie &head, string movie_title);
void add_length(wsk_movie &head, string length_word);
void add_emission(wsk_movie &head, string title, days_of_week day, date current_hour, int hall, int* table, wsk_emission &wsk_halls, wsk_emission &week, int available_seats);
void add_emission_before(wsk_emission &tmp2, days_of_week day, date current_hour, date end_of_emission, int hall, int* table, int available_seats);
void add_emission_after(wsk_emission &tmp2, days_of_week day, date current_hour, date end_of_emission, int hall, int* table, int available_seats);
void add_to_hall(wsk_emission &emission, wsk_emission &hall);
void add_to_week(wsk_emission &emission, wsk_emission &week);
void delete_list(wsk_movie &head);
void delete_movie(wsk_movie &head, wsk_emission *&table, wsk_emission &week);
void delete_emission(wsk_movie &head, wsk_emission *&table, wsk_emission &week, string days[], int *halls);
void buy_ticket(wsk_movie &head, string days[]);

int main()
{
	int choice = 1;
	wsk_movie movies = new movie;									//Lista movies posiada wartownika na koncu
	movies->next = movies->prev = nullptr;
	movies->emissions = nullptr;
	wsk_emission *wsk_halls;
	wsk_emission week;
	week = new emission;
	week->day = End_of_week;
	week->start = { 30,30 };
	week->next = week->prev = week->next_hall = week->prev_hall = week->next_week = week->prev_week = nullptr;
	string days[8] = { "Error","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
	int *table;
	while (choice != 0)
	{
		cout << "Witaj w Symulatorze kina 2.0. Co chcesz zrobic:" << endl << "1. Wczytac plan kina z pliku\n2. Utworzyc kino i repertuar recznie\n3. Zakonczyc dzialanie programu\nWybor: ";
		string protection;
		getline(cin, protection);
		if (protection.length() != 1)
		{
			cout << "Nie wpisuj niepoprawnych danych" << endl;
			continue;
		}
		choice = atoi(protection.c_str());
		switch (choice)
		{
		case 1:
		{
			create_from_file(movies, wsk_halls, week, days, table);
			choice = 0;
			break;
		}
		case 2:
		{
			cout << "Wprowadz ilosc sal w kinie: ";
			int amount = 0;
			cin >> amount;
			cin.get();
			table = new int[amount + 1];
			table[0] = amount;
			cout << "Teraz musisz wpisac liczbe miejsc w kazdej sali: " << endl;
			for (int i = 1; i <= table[0]; i++)
			{
				cout << "Sala " << i << ": ";
				cin >> amount;
				cin.get();
				table[i] = amount;
			}
			wsk_halls = new wsk_emission[table[0] + 1];
			for (int i = 0; i <= table[0]; i++)
			{
				wsk_halls[i] = nullptr;
			}
			choice = 0;
			break;
		}
		case 3: return 0;
		default: {cout << "Bledna liczba. Sprobuj jeszcze raz" << endl; choice = 1; }
		}
	}
	bool modified = 0;
	cout << endl << endl;
	choice = 1;
	while (choice != 0)
	{
		cout << "Co chcesz zrobic?\n1. Dodac film\n2. Usunac film\n3. Dodac seans\n4. Usunac seans\n5. Kupic bilet\n6. Wypisac seanse\n7. Wypisac seanse z wolnymi miejscami\n8. Przedstawic grafik konkretnej sali\n9. Zakonczyc program\nWybor: ";
		string protection;
		getline(cin, protection);
		if (protection.length() != 1)
		{
			cout << "Nie wpisuj niepoprawnych danych" << endl;
			continue;
		}
		choice = atoi(protection.c_str());
		cout << endl;
		switch (choice)
		{
		case 1:							//Dodawanie filmu
		{
			cout << "Wprowadz nazwe filmu: ";
			string movie_title;
			getline(cin, movie_title);
			add_movie(movies, movie_title);
			while (true)
			{
				cout << "Wprowadz dlugosc film: ";
				string length_word;
				getline(cin, length_word);
				if (length_word.length() > 4)
				{
					cout << "Film za dlugi" << endl;
					continue;
				}
				else
				{
					if (length_word[1] == '.')
					{
						add_length(movies, length_word);
						cout << endl;
						break;
					}
					else
					{
						if (length_word.length() == 1)
						{
							add_length(movies, length_word);
							cout << endl;
							break;
						}
						else
							cout << "Bledny format" << endl;
					}
				}
			}
			modified = 1;
			break;
		}
		case 2:							//Usuwanie filmu
		{
			delete_movie(movies, wsk_halls, week);
			modified = 1;
			break;
		}
		case 3:							//Dodawanie seanu
		{
			cout << "Lista aktualnych filmow:\n";
			wsk_movie tmp = movies;
			if (tmp->next == nullptr)
			{
				cout << "#Error: W repertuarze nie ma filmow, musisz je najpierw dodac" << endl << endl;
				break;
			}
			while (tmp->next != nullptr)
			{
				cout << tmp->name << endl;
				tmp = tmp->next;
			}
			tmp = movies;
			cout << endl << "Do ktorego filmu chcesz dodac seans?  ";
			string movie_title;
			bool correct = 0;
			while (!correct)
			{
				getline(cin, movie_title);
				while (tmp->next != nullptr)
				{
					if (tmp->name == movie_title)
					{
						correct = 1;
						break;
					}
					else
						tmp = tmp->next;
				}
				if (tmp->next == nullptr)
					cout << "Brak filmu o podanej nazwie\nWprowadz nazwe filmu: " << endl;
			}
			cout << endl;
			show_movie(tmp->emissions, 0);
			cout << endl;
			string day_name;
			days_of_week day;
			while (true)
			{
				cout << "Do jakiego dnia (Monday-Sunday) chcesz dodac seans? ";
				getline(cin, day_name);
				day = day_string_to_enum(day_name, days);
				if (day == Error)
					cout << "Blad. Sprobuj jeszcze raz" << endl;
				else
					break;
			}
			string time_word;
			date current_time;
			while (true)
			{
				cout << "O ktorej godzinie chcesz dodac seans: ";
				getline(cin, time_word);
				if (time_word[2] == ':')
				{
					string hour_word = time_word.substr(0, 2), minutes_word = time_word.substr(3, 2);
					current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
					if (correct_hour(current_time))
						break;
				}
				else
				{
					if (time_word[1] == ':')
					{
						string hour_word = time_word.substr(0, 1), minutes_word = time_word.substr(2, 2);
						current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
						if (correct_hour(current_time))
							break;
					}
				}
			}
			int hall;
			bool *free_halls = new bool[table[0] + 1];
			for (int i = 0; i <= table[0]; i++)
				free_halls[i] = 1;
			show_free_halls(day, week, free_halls, current_time, tmp->length);
			for (int i = 1; i <= table[0]; i++)
				if (free_halls[i])
					cout << "Sala " << i << " jest wolna " << endl;
			while (true)
			{
				cout << "Do ktorej sali chcesz dodac seans? ";
				string hall_word;
				getline(cin, hall_word);
				if (hall_word.length() < 3)
				{
					hall = atoi(hall_word.c_str());
					if (hall <= table[0])
						if (!free_halls[hall])
							cout << "Ta sala jest zajeta"<<endl;
						else
							break;
					else
						cout << "Numer sali jest za duzy"<<endl;
				}
				else
					cout << "Nie wpisuj glupot"<<endl;
			}
			int available_seats = table[hall];
			add_emission(movies, movie_title, day, current_time, hall, table, wsk_halls[hall], week, available_seats);
			cout << endl;
			modified = 1;
			break;
		}
		case 4:							//Usuwanie seansu
		{
			delete_emission(movies, wsk_halls, week, days, table);
			modified = 1;
			break;
		}
		case 5:							//Kupno biletu
		{
			buy_ticket(movies, days);
			modified = 1;
			break;
		}
		case 6:							//Wypisanie seansow
		{
			show_emissions(movies, 0);
			break;
		}
		case 7: 
		{
			show_emissions(movies, 1);
			break;
		}
		case 8: 
		{
			int hall;
			while (true)
			{
				cout << "Wprowadz numer sali: ";
				string hall_word;
				getline(cin, hall_word);
				if (hall_word.length() < 3)
				{
					hall = atoi(hall_word.c_str());
					if (hall <= table[0])
						break;
					else
						cout << "Numer sali jest za duzy" << endl;
				}
				else
					cout << "Nie wpisuj glupot" << endl;
			}
			show_hall(wsk_halls[hall]);
			break;
		}
		case 9: {choice = 0; break; }				//Koniec programu
		default: choice = 1;			//Ponowne wypisanie opcji(zabezpieczenie przed bledami)
		}
	}

	if (modified)
		safe_to_file(movies, table);
	delete[] table;
	delete_list(movies);

	cin.get();
	return 0;
}

void show_emissions(wsk_movie head, bool only_with_seats)
{
	if (head->next == nullptr)
		cout << "Brak filmow";
	else
	{
		while (head->next != nullptr)
		{
			cout << "Movie: " << head->name << endl;
			cout << "Length: " << head->length << endl;
			wsk_emission tmp2 = head->emissions;
			show_movie(tmp2, only_with_seats);
			cout << endl;
			head = head->next;
		}
	}
}

void show_hall(wsk_emission hall)
{
	if (hall != nullptr)
	{
		for (int j = 1; j < 8; j++)
		{
			if (hall != nullptr)
			{
				if (hall->day == days_of_week(j))
				{
					show_day(hall->day);		//Funkcja wyswietla dzien tygodnia
					while (hall != nullptr&&hall->day == days_of_week(j))
					{
						cout << hall->start.hour << ":";
						if (hall->start.minutes != 0)
							cout << hall->start.minutes << " - s." << hall->hall << " (" << hall->available_seats << ")" << '\t';
						else
							cout << "OO" << " - s." << hall->hall << " (" << hall->available_seats << ")" << '\t';
						hall = hall->next_hall;
					}
					cout << endl;
				}
			}
		}
		cout << endl;
	}
	else
		cout << "Film nie ma seansow" << endl;
}

void show_free_halls(days_of_week day, wsk_emission week, bool *&free_halls, date start_of_emission, double length)
{
	if (week != nullptr)
	{
		int length_hours = (int)floor(length);
		int length_minutes = (int)((length - length_hours) * 60);
		date end_of_emission = { start_of_emission.hour + length_hours, start_of_emission.minutes + length_minutes };
		if (end_of_emission.minutes >= 60)
		{
			end_of_emission.minutes -= 60;
			end_of_emission.hour++;
		}
		for (int j = 1; j < 8; j++)
		{
			if (week->day == day)
			{
				while (week != nullptr&&week->day == day)
				{
					if ((end_of_emission.hour == week->start.hour && end_of_emission.minutes > week->start.minutes) ||
						(start_of_emission.hour < week->end.hour && end_of_emission.hour >= week->end.hour)||
						(start_of_emission.hour <= week->end.hour && end_of_emission.hour > week->end.hour) ||
						(start_of_emission.hour >= week->end.hour && end_of_emission.hour <= week->end.hour)||
						(start_of_emission.hour > week->start.hour && end_of_emission.hour <= week->end.hour)||
						(start_of_emission.hour == week->end.hour && start_of_emission.minutes < week->end.minutes) ||
						start_of_emission.hour == week->start.hour|| end_of_emission.hour == week->end.hour)
						
						free_halls[week->hall] = 0;

					week = week->next_week;
				}
				cout << endl;
			}
		}

	}
	else
		cout << "Brak seansow w kinie" << endl;
}

void show_movie(wsk_emission emissions, bool only_with_available_seats)
{
	if (emissions != nullptr)
	{
		for (int j = 1; j < 8; j++)
		{
			if (emissions->day == days_of_week(j))
			{
				show_day(emissions->day);		//Funkcja wyswietla dzien tygodnia
				while (emissions != nullptr&&emissions->day == days_of_week(j))
				{
					if (only_with_available_seats)
					{
						if (emissions->available_seats != 0)
						{
							cout << emissions->start.hour << ":";
							if (emissions->start.minutes != 0)
								cout << emissions->start.minutes << " - s." << emissions->hall << " (" << emissions->available_seats << ")" << '\t';
							else
								cout << "OO" << " - s." << emissions->hall << " (" << emissions->available_seats << ")" << '\t';
						}
						emissions = emissions->next;
					}
					else
					{
						cout << emissions->start.hour << ":";
						if (emissions->start.minutes != 0)
							cout << emissions->start.minutes << " - s." << emissions->hall << " (" << emissions->available_seats << ")" << '\t';
						else
							cout << "OO" << " - s." << emissions->hall << " (" << emissions->available_seats << ")" << '\t';
						emissions = emissions->next;
					}
				}
				cout << endl;
			}
		}
		cout << endl;
	}
	else
		cout << "Film nie ma seansow" << endl;
}

void show_day(days_of_week day)
{
	switch (day)
	{
	case 1: cout << "Monday:" << '\t' << '\t'; break;
	case 2: cout << "Tuesday:" << '\t'; break;
	case 3: cout << "Wednesday:" << '\t'; break;
	case 4: cout << "Thursday:" << '\t'; break;
	case 5: cout << "Friday:" << '\t' << '\t'; break;
	case 6: cout << "Saturday:" << '\t'; break;
	case 7: cout << "Sunday:" << '\t' << '\t'; break;
	default: cout << "Bledna nazwa dnia";
	}
}

void show_dzien(days_of_week day)
{
	switch (day)
	{
	case 1: cout << " Poniedzialek "; break;
	case 2: cout << " Wtorek "; break;
	case 3: cout << " Srode "; break;
	case 4: cout << " Czwartek "; break;
	case 5: cout << " Piatek "; break;
	case 6: cout << " Sobote "; break;
	case 7: cout << " Niedziele "; break;
	default: cout << " Bledna nazwa dnia ";
	}

}

bool correct_name(string name)
{
	int i = name.length() - 4;
	if (i < 1)
	{
		cout << "Bledna nazwa pliku. Sprobuj jeszcze raz: ";
		return 0;
	}
	string extension = name.substr(i, 4);
	if (extension == ".txt")
		return 1;
	else
	{
		cout << "Plik ma bledne rozszerzenie. Sprobuj jeszcze raz: ";
		return 0;
	}
}

bool correct_hour(date current_time)
{
	if (current_time.hour >= 0 && current_time.hour < 24)
		if (current_time.minutes >= 0 && current_time.minutes < 60)
			return 1;
		else
		{
			cout << "Bledny format minut" << endl;
			return 0;
		}
	else
	{
		cout << "Bledna godzina" << endl;
		return 0;
	}

}

int* create_cinema(ifstream &file)
{
	string halls;
	file >> halls;
	int number_of_halls = atoi(halls.c_str());
	int* table = new int[number_of_halls + 1];
	table[0] = number_of_halls;
	cout << "Ilosc sal: " << table[0] << endl;
	file >> halls;
	for (int i = 1; i < number_of_halls + 1 && halls != "\n"; i++)
	{
		file >> halls;
		if (halls == ",")
		{
			i--;
			continue;
		}
		else
		{
			int total_seats = atoi(halls.c_str());
			table[i] = total_seats;
			cout << "Sala " << i << " ma " << total_seats << " miejsc" << endl;
		}
	}
	return table;
}

void create_from_file(wsk_movie &movies, wsk_emission *&wsk_halls, wsk_emission &week, string days[], int *&table)
{
	string file_name;
	ifstream file;
	do
	{
		do
		{
			cout << "Wprowadz nazwe pliku z rozszerzeniem .txt: ";
			getline(cin, file_name);
		} while (!correct_name(file_name));
		file.open(file_name);
		if (!file.is_open())
			cout << "Brak pliku o podanej nazwie. Sprobuj jeszcze raz" << endl;
	} while (!file.is_open());

	cout << "Pobieram repertuar..." << endl;
	string word;
	char space;
	file.seekg(0, ios::end);
	bool size = file.tellg();
	file.seekg(0, ios::beg);
	if (!size)
	{
		cout << "Plik jest pusty. Musisz wprowadzic dane recznie :(" << endl;
	}
	else
	{
		file >> word;
		if (word != "Cinema:")
		{
			cout << "Plik ma niepoprawny plan kina.";
			cout << "Wprowadz ilosc sal w kinie: ";
			int amount = 0;
			cin >> amount;
			cin.get();
			table = new int[amount + 1];
			table[0] = amount;
			cout << "Teraz musisz wpisac liczbe miejsc w kazdej sali: " << endl;
			for (int i = 1; i <= table[0]; i++)
			{
				cout << "Sala " << i << ": ";
				cin >> amount;
				cin.get();
				table[i] = amount;
			}
			wsk_halls = new wsk_emission[table[0] + 1];
			for (int i = 0; i <= table[0]; i++)
			{
				wsk_halls[i] = nullptr;
			}
			cin.get();
		}
		else
		{
			table = create_cinema(file);
			wsk_halls = new wsk_emission[table[0] + 1];
			for (int i = 0; i <= table[0]; i++)
			{
				wsk_halls[i] = nullptr;
			}
			string movie_title;
			file >> word;
			while (!file.eof())
			{

				if (word == "Movie:")
				{

					file.get(space);
					getline(file, movie_title);
					add_movie(movies, movie_title);
					file >> word;

				}
				else if (word == "Length:")
				{
					string length_word;
					file >> length_word;
					add_length(movies, length_word);
					file >> word;
				}
				else if (word == "Emission:")
				{
					while (!file.eof())
					{
						string day_name;
						file >> day_name;
						if (day_name == "Movie:")
						{
							word = day_name;
							break;
						}
						day_name = day_name.substr(0, day_name.length() - 1);
						days_of_week current_day;
						current_day = day_string_to_enum(day_name, days);
						date current_time = { 0,0 };
						string time_word;
						file >> time_word;
						while (time_word != ";")
						{
							if (time_word.length() == 4 || time_word.length() == 5)
							{
								if (time_word[2] == ':')
								{
									string hour_word = time_word.substr(0, 2), minutes_word = time_word.substr(3, 2);
									current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
								}
								else
									if (time_word[1] == ':')
									{
										string hour_word = time_word.substr(0, 1), minutes_word = time_word.substr(2, 2);
										current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
									}
									else
									{
										if (time_word == "hall")
										{
											file >> time_word;
											int hall_number = atoi(time_word.c_str());
											file >> time_word;
											if (time_word[0] == '('&&time_word[time_word.length() - 1] == ')')
											{
												time_word = time_word.substr(1, time_word[time_word.length() - 2]);
												int available_seats = atoi(time_word.c_str());
												if (available_seats > table[hall_number])
													add_emission(movies, movie_title, current_day, current_time, hall_number, table, wsk_halls[hall_number], week, table[hall_number]);
												else
													add_emission(movies, movie_title, current_day, current_time, hall_number, table, wsk_halls[hall_number], week, available_seats);
											}
											else
												add_emission(movies, movie_title, current_day, current_time, hall_number, table, wsk_halls[hall_number], week, table[hall_number]);
											continue;
										}
										else cout << "Zle przedstawiona godzina emisji" << endl;
									}
							}
							else
							{
								file >> time_word;
								continue;
							}
							file >> time_word;
						}
					}
				}
			}
			file.close();
		}
	}

}

void safe_to_file(wsk_movie &head, int *halls)
{
	string file_name;
	ofstream file;
	do
	{
		do
		{
			cout << "Wprowadz nazwe pliku do ktorego chcesz zapisac nowy repertuar: ";
			getline(cin, file_name);
		} while (!correct_name(file_name));
		file.open(file_name);
		if (!file.is_open())
			cout << "Brak pliku o podanej nazwie. Sprobuj jeszcze raz: ";
	} while (!file.is_open());
	char space = ' ';
	file << "Cinema: ";
	string hall = to_string(halls[0]);
	file << hall << " halls: ";
	for (int i = 1; i < halls[0]; i++)
	{
		hall = to_string(halls[i]);
		file << hall << " , ";
	}
	hall = to_string(halls[halls[0]]);
	file << hall;

	if (head->next != nullptr)
	{
		file << '\n';
		while (head->next != nullptr)
		{
			file << "Movie: " << head->name << endl;
			file << "Length: " << head->length << endl;
			file << "Emissions: " << endl;
			wsk_emission tmp2 = head->emissions;
			if (tmp2 != nullptr)
			{
				for (int j = 1; j < 8; j++)
				{
					if (tmp2->day == days_of_week(j))
					{
						switch (tmp2->day)
						{
						case 1: file << "Monday: "; break;
						case 2: file << "Tuesday: "; break;
						case 3: file << "Wednesday: "; break;
						case 4: file << "Thursday: "; break;
						case 5: file << "Friday: "; break;
						case 6: file << "Saturday: "; break;
						case 7: file << "Sunday: "; break;
						}
						while (tmp2->next != nullptr&&tmp2->day == days_of_week(j))
						{
							file << tmp2->start.hour << ":";
							if (tmp2->start.minutes != 0)
							{
								file << tmp2->start.minutes << " - hall " << tmp2->hall << " (" << tmp2->available_seats << ") ";
								if (tmp2->next->day != 8)
									file << ", ";
							}
							else
							{
								file << "OO" << " - hall " << tmp2->hall << " (" << tmp2->available_seats << ") ";
								if (tmp2->next->day != 8)
									file << ", ";
							}
							tmp2 = tmp2->next;
						}
						file << endl;
					}
				}
				file << endl;
			}
			cout << endl;
			head = head->next;

		}
	}
	cout << "Pomyslnie zapisano repertuar do pliku" << endl;
	file.close();
}

days_of_week day_string_to_enum(string day, string table[])
{
	for (int i = 1; i < 8; i++)
	{
		if (day == table[i])
			return days_of_week(i);
	}
	return days_of_week(0);
}

bool hall_is_free(wsk_emission &wsk_halls, days_of_week day, date start_of_emission, date end_of_emission)
{
	wsk_emission tmp = wsk_halls;
	if (tmp == nullptr)
		return true;
	else
	{
		while (tmp != nullptr)
		{
			if (tmp->day != day)
				if (tmp->next_hall != nullptr)
					tmp = tmp->next_hall;
				else return true;
			else
			{
				if (tmp->end.hour < start_of_emission.hour)
				{
					if (tmp->next_hall == nullptr)
						return true;
					else
					{
						if (tmp->next_hall->day != day)
							return true;
						else
							if (tmp->next_hall->start.hour > end_of_emission.hour)
								return true;
							else tmp = tmp->next_hall;
					}
				}
				else
				{
					if (tmp->end.hour == start_of_emission.hour)
					{
						if (tmp->end.minutes < start_of_emission.minutes)
						{
							if (tmp->next_hall == nullptr)
								return true;
							else
							{
								if (tmp->next_hall->day != day)
									return true;
								else
								{
									if (tmp->next_hall->start.hour >= end_of_emission.hour)
									{
										if (tmp->next_hall->start.minutes >= end_of_emission.minutes)
											return true;
										else
											tmp = tmp->next_hall;;
									}
									else tmp = tmp->next_hall;
								}
							}
						}
					}
					else
					{
						if (tmp->start.hour > end_of_emission.hour)
							if (tmp->prev_hall != nullptr)   //&&&&tmp->prev->end.minutes < start_of_emission.minutes)
								if (tmp->prev_hall->day != day)
									return true;
								else
								{
									if (tmp->prev_hall->end.hour <= start_of_emission.hour)
									{
										if (tmp->prev_hall->end.minutes < start_of_emission.minutes)
											return true;
										else
											return false;
									}
									else
										return false;
								}
							else return true;
						else
						{
							if (tmp->start.hour == end_of_emission.hour)
							{
								if (tmp->start.minutes >= end_of_emission.minutes)
									return true;
								else
									return false;
							}
							else tmp = tmp->next_hall;
						}
					}
				}
			}
		}
		return false;
	}
}

void add_movie(wsk_movie &head, string movie_title)
{
	wsk_movie tmp = head;
	while (tmp->next != nullptr)
	{
		tmp = tmp->next;
	}
	tmp->name = movie_title;
	tmp->length = 0;
	tmp->next = new movie;
	tmp->next->prev = tmp;
	tmp = tmp->next;
	tmp->next = nullptr;
	tmp->emissions = nullptr;
}

void add_length(wsk_movie &head, string length_word)
{
	double length = atof(length_word.c_str());
	wsk_movie tmp = head;
	while (tmp->next->next != nullptr)
		tmp = tmp->next;
	tmp->length = length;
}

void add_emission(wsk_movie &head, string title, days_of_week day, date start_of_emission, int hall, int* table, wsk_emission &wsk_halls, wsk_emission &week, int available_seats)
{
	wsk_movie tmp = head;
	while (tmp->next != nullptr)
	{
		if (tmp->name == title)
		{
			break;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	double length = tmp->length;
	int length_hours = (int)floor(length);
	int length_minutes = (int)((length - length_hours) * 60);
	date end_of_emission = { start_of_emission.hour + length_hours, start_of_emission.minutes + length_minutes };
	if (end_of_emission.minutes >= 60)
	{
		end_of_emission.minutes -= 60;
		end_of_emission.hour++;
	}

	if (hall_is_free(wsk_halls, day, start_of_emission, end_of_emission))
	{
		wsk_emission tmp2 = tmp->emissions;
		if (tmp2 == nullptr)
		{
			tmp->emissions = new emission; 						//Kazda lista emissions posiada wartownika na koncu
			tmp2 = tmp->emissions;
			tmp2->next = tmp2->prev = tmp2->next_hall = tmp2->prev_hall = tmp2->next_week = tmp2->prev_week = nullptr;
			tmp2->start = tmp2->end = { 30,30 };
			tmp2->day = End_of_week;								//Dla ulatwienia przeszukiwania na koncu tygodnia jest ustawiony dzien o numerze 8
		}

		if (tmp2->next == nullptr)
		{
			tmp->emissions = new emission;
			tmp->emissions->next = tmp2;
			tmp2->prev = tmp->emissions;
			tmp2 = tmp2->prev;
			tmp2->day = day;
			tmp2->start = start_of_emission;
			tmp2->end = end_of_emission;
			tmp2->hall = hall;
			tmp2->total_seats = table[hall];
			tmp2->available_seats = available_seats;
			tmp2->prev = tmp2->next_hall = tmp2->prev_hall = tmp2->next_week = tmp2->prev_week = nullptr;
			add_to_hall(tmp2, wsk_halls);
			add_to_week(tmp2, week);

		}
		else
		{
			while (tmp2->next != nullptr)
			{
				if (tmp2->day < day)
					if (tmp2->next->day > day)
					{
						add_emission_after(tmp2, day, start_of_emission, end_of_emission, hall, table, available_seats);
						add_to_hall(tmp2, wsk_halls);
						add_to_week(tmp2, week);
						break;
					}
					else
						tmp2 = tmp2->next;
				else
				{
					if (tmp2->day > day)
						if (tmp2->prev == nullptr)
						{
							tmp->emissions = new emission;
							tmp->emissions->next = tmp2;
							tmp2->prev = tmp->emissions;
							tmp2 = tmp2->prev;
							tmp2->day = day;
							tmp2->start = start_of_emission;
							tmp2->end = end_of_emission;
							tmp2->hall = hall;
							tmp2->total_seats = table[hall];
							tmp2->available_seats = available_seats;
							//tmp2->next = tmp2;
							tmp2->prev = tmp2->next_hall = tmp2->prev_hall = tmp2->next_week = tmp2->prev_week = nullptr;
							add_to_hall(tmp2, wsk_halls);
							add_to_week(tmp2, week);
							break;
						}
						else
						{
							add_emission_before(tmp2, day, start_of_emission, end_of_emission, hall, table, available_seats);
							add_to_hall(tmp2, wsk_halls);
							add_to_week(tmp2, week);
							break;
						}
					else                  //tmp2->day==day
					{
						if (tmp2->start.hour <= start_of_emission.hour)
						{
							if (tmp2->next->start.hour < start_of_emission.hour)
								tmp2 = tmp2->next;
							else		
							{
								if (tmp2->start.hour == start_of_emission.hour)
								{
									if (tmp2->start.minutes <= start_of_emission.minutes)
									{
										add_emission_after(tmp2, day, start_of_emission, end_of_emission, hall, table, available_seats);
										add_to_hall(tmp2, wsk_halls);
										add_to_week(tmp2, week);
										break;
									}
									else
									{
										if (tmp2->prev == nullptr)
										{
											tmp->emissions = new emission;
											tmp->emissions->next = tmp2;
											tmp2->prev = tmp->emissions;
											tmp2 = tmp2->prev;
											tmp2->day = day;
											tmp2->start = start_of_emission;
											tmp2->end = end_of_emission;
											tmp2->hall = hall;
											tmp2->total_seats = table[hall];
											tmp2->available_seats = available_seats;
											//tmp2->next = tmp2;
											tmp2->prev = tmp2->next_hall = tmp2->prev_hall = tmp2->next_week = tmp2->prev_week = nullptr;
											add_to_hall(tmp2, wsk_halls);
											add_to_week(tmp2, week);
											break;
										}
										else
										{
											add_emission_before(tmp2, day, start_of_emission, end_of_emission, hall, table, available_seats);
											add_to_hall(tmp2, wsk_halls);
											add_to_week(tmp2, week);
											break;
										}
									}
								}
								else
								{
									add_emission_after(tmp2, day, start_of_emission, end_of_emission, hall, table, available_seats);
									add_to_hall(tmp2, wsk_halls);
									add_to_week(tmp2, week);
									break;
								}
							}
						}
						else
						{
							if (tmp2->prev == nullptr)			//tmp2->end.hour > start_of_emission.hour
							{
								tmp->emissions = new emission;
								tmp->emissions->next = tmp2;
								tmp2->prev = tmp->emissions;
								tmp2 = tmp2->prev;
								tmp2->day = day;
								tmp2->start = start_of_emission;
								tmp2->end = end_of_emission;
								tmp2->hall = hall;
								tmp2->total_seats = table[hall];
								tmp2->available_seats = available_seats;
								//tmp2->next = tmp2;
								tmp2->prev = tmp2->next_hall = tmp2->prev_hall = tmp2->next_week = tmp2->prev_week = nullptr;
								add_to_hall(tmp2, wsk_halls);
								add_to_week(tmp2, week);
								break;
							}
							else
							{
								add_emission_before(tmp2, day, start_of_emission, end_of_emission, hall, table, available_seats);
								add_to_hall(tmp2, wsk_halls);
								add_to_week(tmp2, week);
								break;
							}
						}
					}
				}
			}
		}

	}
	else
	{
		cout << "Seans nie zostal dodany, poniewaz sala jest w tym czasie zajeta" << endl;
	}
}

void add_emission_before(wsk_emission &tmp2, days_of_week day, date current_hour, date end_of_emission, int hall, int* table, int available_seats)
{
	tmp2->prev->next = new emission;
	tmp2->prev->next->next = tmp2;
	tmp2->prev->next->prev = tmp2->prev;
	tmp2 = tmp2->prev;
	tmp2->next->next->prev = tmp2->next;
	tmp2 = tmp2->next;
	tmp2->day = day;
	tmp2->start = current_hour;
	tmp2->end = end_of_emission;
	tmp2->hall = hall;
	tmp2->total_seats = table[hall];
	tmp2->available_seats = available_seats;
	tmp2->next_hall = tmp2->prev_hall = tmp2->next_week = tmp2->prev_week = nullptr;
}

void add_emission_after(wsk_emission &tmp2, days_of_week day, date current_hour, date end_of_emission, int hall, int* table, int available_seats)
{
	tmp2->next->prev = new emission;
	tmp2->next->prev->prev = tmp2;
	tmp2->next->prev->next = tmp2->next;
	tmp2 = tmp2->next;
	tmp2->prev->prev->next = tmp2->prev;
	tmp2 = tmp2->prev;
	tmp2->day = day;
	tmp2->start = current_hour;
	tmp2->end = end_of_emission;
	tmp2->hall = hall;
	tmp2->total_seats = table[hall];
	tmp2->available_seats = available_seats;
	tmp2->next_hall = tmp2->prev_hall = tmp2->next_week = tmp2->prev_week = nullptr;
}

void add_to_hall(wsk_emission &emission, wsk_emission &hall)
{
	wsk_emission tmp = hall;
	if (tmp == nullptr)
	{
		hall = emission;
		emission->next_hall = emission->prev_hall = nullptr;
	}
	else
	{
		if (tmp->next_hall == nullptr)
		{
			if (tmp->day < emission->day)
			{
				emission->next_hall = nullptr;
				emission->prev_hall = hall;
				hall->next_hall = emission;
			}
			else
			{
				if (tmp->day > emission->day)
				{
					emission->prev_hall = nullptr;
					emission->next_hall = hall;
					hall->prev_hall = emission;
					hall = emission;
				}
				else      //tmp->day==emission->day
				{

					if (tmp->end.hour < emission->start.hour)
					{
						emission->next_hall = nullptr;
						emission->prev_hall = hall;
						hall->next_hall = emission;
					}
					else
					{
						if (tmp->end.hour == emission->start.hour)
						{
							emission->next_hall = hall;
							emission->prev_hall = tmp->prev_hall;
							hall->prev_hall->next_hall = emission;
							hall->prev_hall = emission;
						}
						else
						{
							emission->next_hall = tmp;
							emission->prev_hall = nullptr;
							hall->next_hall = emission;
						}
					}
				}
			}
		}
		else
		{
			while (tmp->next_hall != nullptr)
			{
				if (tmp->day < emission->day)
				{
					if (tmp->next_hall->day > emission->day)
					{
						emission->next_hall = tmp->next_hall;
						emission->prev_hall = tmp;
						tmp->next_hall = emission;
						emission->next_hall->prev_hall = emission;
						break;
					}
					else
						if (tmp->next_hall->day == emission->day)
						{
							if (tmp->next_hall->next_hall == nullptr)
							{
								if (tmp->next_hall->start.hour >= emission->end.hour)
								{
									emission->next_hall = tmp->next_hall;
									emission->prev_hall = tmp;
									tmp->next_hall = emission;
									emission->next_hall->prev_hall = emission;
									break;
								}
								else
									tmp = tmp->next_hall;
							}
							else tmp = tmp->next_hall;
						}
						else
							tmp = tmp->next_hall;
				}
				else
				{
					if (tmp->day > emission->day)
					{
						if (tmp->prev_hall == nullptr)
						{
							emission->prev_hall = nullptr;
							emission->next_hall = tmp;
							tmp->prev_hall = emission;
							hall = emission;
							break;
						}
						else
						{
							emission->prev_hall = tmp->prev_hall;
							emission->next_hall = tmp;
							tmp->prev_hall->next_hall = emission;
							tmp->prev_hall = emission;
							break;

						}
					}
					else			//tmp->day == emission->day
					{
						if (tmp->start.hour >= emission->end.hour)
						{
							if (tmp->prev_hall == nullptr)
							{
								emission->prev_hall = nullptr;
								emission->next_hall = hall;
								hall->prev_hall = emission;
								hall = emission;
							}
							else
							{
								emission->prev_hall = tmp->prev_hall;
								emission->next_hall = tmp;
								tmp->prev_hall->next_hall = emission;
								tmp->prev_hall = emission;
								break;
							}
						}
						else
						{
							if (tmp->end.hour <= emission->start.hour)
							{
								if (tmp->next_hall->start.hour <= emission->end.hour)
								{
									emission->next_hall = tmp->next_hall;
									emission->prev_hall = tmp;
									tmp->next_hall = emission;
									emission->next_hall->prev_hall = emission;
									break;
								}
								else
									tmp = tmp->next_hall;
							}

						}
					}
				}
			}
			if (emission->next_hall == emission->prev_hall)		//Wskazuja na to samo, jesli oba sa nullptr (czyli nie wpisano ich do listy)
			{
				emission->next_hall = nullptr;
				emission->prev_hall = tmp;
				tmp->next_hall = emission;
			}
		}

	}

}

void add_to_week(wsk_emission &emission, wsk_emission &week)
{
	wsk_emission tmp = week;
	if (tmp->next_week == nullptr)
	{
		tmp->prev_week = emission;
		emission->next_week = tmp;
		week = emission;
	}
	else
	{
		while (tmp->next_week != nullptr)
		{
			if (tmp->day < emission->day)
			{
				tmp = tmp->next_week;
			}
			else
			{
				if (tmp->day > emission->day)
				{
					if (tmp->prev_week == nullptr)
					{
						tmp->prev_week = emission;
						emission->next_week = tmp;
						week = emission;
						break;
					}
					else
						break;
				}
				else				//tmp->day == emission->day
				{
					if (tmp->start.hour < emission->start.hour)
					{
						if (tmp->next_week->day == emission->day)
						{
							if (tmp->next_week->start.hour > emission->start.hour)
							{
								tmp = tmp->next_week;
								break;
							}
							else
								tmp = tmp->next_week;
						}
						else
						{
							tmp = tmp->next_week;
							break;
						}
					}
					else
					{
						if (tmp->start.hour > emission->start.hour)
						{
							if (tmp->prev_week == nullptr)
							{
								tmp->prev_week = emission;
								emission->next_week = tmp;
								week = emission;
								break;
							}
							else
								break;
						}
						else				//tmp->start.hour==emission->start.hour
						{
							if (tmp->start.minutes <= emission->start.minutes)
							{
								tmp = tmp->next_week;
								break;
							}
							else
								break;
						}
					}
				}
			}
		}
		if (emission->next_week == emission->prev_week)   //Oba sa nullptr
		{
			if (tmp ->prev_week!= nullptr)
			{
				tmp->prev_week->next_week = emission;
				emission->prev_week = tmp->prev_week;
				emission->next_week = tmp;
				tmp->prev_week = emission;
			}
			else
			{
				tmp->prev_week = emission;
				emission->prev_week = nullptr;
				emission->next_week = tmp;
				week = emission;
			}
		}
	}
}

void delete_list(wsk_movie &head)
{
	if (head != nullptr)
	{
		while (head->next != nullptr)
		{
			if (head->emissions != nullptr)
			{
				while (head->emissions != nullptr)
				{
					wsk_emission tmp = head->emissions->next;
					head->emissions->next = head->emissions->prev = head->emissions->next_hall = head->emissions->prev_hall = head->emissions->next_week = head->emissions->prev_week = nullptr;
					delete head->emissions;
					head->emissions = tmp;
				}
				delete head->emissions;
			}
			wsk_movie tmp = head->next;
			head->next = head->prev = nullptr;
			delete head;
			head = tmp;
		}
		delete head;
	}

}

void delete_movie(wsk_movie &head, wsk_emission *&table, wsk_emission &week)
{
	cout << "Lista aktualnych filmow:\n";
	wsk_movie tmp = head;
	if (tmp->next != nullptr)
	{
		while (tmp->next != nullptr)
		{
			cout << tmp->name << endl;
			tmp = tmp->next;
		}
		cout << endl;
		bool deleted = 0;
		while (!deleted)
		{
			cout << "Wprowadz tytul filmu, ktory chcesz usunac:  ";
			tmp = head;
			string movie_title;
			getline(cin, movie_title);
			while (tmp->next != nullptr)
			{
				if (tmp->name == movie_title)
				{
					if (tmp->emissions == nullptr)
					{
						if (tmp->prev != nullptr)
						{
							tmp->prev->next = tmp->next;
							tmp->next->prev = tmp->prev;
							delete tmp;
						}
						else
						{
							tmp->next->prev = nullptr;
							head = tmp->next;
							wsk_movie tmp2 = tmp;
							tmp = tmp->next;
							delete tmp2;
						}
					}
					else		//Film zawiera seanse do usuniecia
					{
						while (tmp->emissions->next != nullptr)
						{
							if (tmp->emissions == table[tmp->emissions->hall])
							{
								if (tmp->emissions->next_hall == nullptr)
									table[tmp->emissions->hall] = nullptr;
								else
								{
									table[tmp->emissions->hall] = tmp->emissions->next_hall;
									tmp->emissions->next_hall->prev_hall = nullptr;
									tmp->emissions->next_hall = nullptr;
								}
							}
							else
							{
								if (tmp->emissions->next_hall == nullptr)
								{
									tmp->emissions->prev_hall->next_hall = nullptr;
									tmp->emissions->prev_hall = nullptr;
								}
								else
								{
									tmp->emissions->prev_hall->next_hall = tmp->emissions->next_hall;
									tmp->emissions->next_hall->prev_hall = tmp->emissions->prev_hall;
									tmp->emissions->next_hall = tmp->emissions->next_hall = nullptr;
								}
							}

							if (tmp->emissions == week)
							{
								if (tmp->emissions->next_week == nullptr)
									week = nullptr;
								else
								{
									week = tmp->emissions->next_week;
									tmp->emissions->next_week->prev_week = nullptr;
									tmp->emissions->next_week = nullptr;
								}
							}
							else
							{
								if (tmp->emissions->next_week == nullptr)
								{
									tmp->emissions->prev_week->next_week = nullptr;
									tmp->emissions->prev_week = nullptr;
								}
								else
								{
									tmp->emissions->prev_week->next_week = tmp->emissions->next_week;
									tmp->emissions->next_week->prev_week = tmp->emissions->prev_week;
									tmp->emissions->next_week = tmp->emissions->next_week = nullptr;
								}
							}
							wsk_emission tmp2 = tmp->emissions;
							tmp->emissions = tmp->emissions->next;
							delete tmp2;
						}
					}


					deleted = 1;
					break;
				}
				else
					tmp = tmp->next;
				if (tmp->next == nullptr)
					cout << "Bledna nazwa, sprobuj jeszcze raz." << endl;
			}
		}

		if (tmp->prev == nullptr)
		{
			head = tmp->next;
			tmp->next = nullptr;
			delete tmp;
		}
		else
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
		}
	}
	else
		cout << "#ERROR : Brak filmow w repertuarze" << endl << endl;
}

void delete_emission(wsk_movie &head, wsk_emission *&table, wsk_emission &week, string days[], int *halls)
{
	cout << "Lista aktualnych filmow:\n";
	wsk_movie tmp = head;
	if (tmp->next != nullptr)
	{
		while (tmp->next != nullptr)
		{
			cout << tmp->name << endl;
			tmp = tmp->next;
		}
		tmp = head;
		cout << endl << "Dla ktorego filmu chceszc usunac seans? ";
		string movie_title;
		bool correct = 0;
		while (!correct)
		{
			getline(cin, movie_title);
			while (tmp->next != nullptr)
			{
				if (tmp->name == movie_title)
				{
					correct = 1;
					break;
				}
				else
					tmp = tmp->next;
			}
			if (tmp->next == nullptr)
				cout << "Brak filmu o podanej nazwie\nWprowadz nazwe filmu: " << endl;
		}
		if (tmp->emissions != nullptr)
		{
			show_movie(tmp->emissions, 0);
			cout << endl;
			string day_name;
			days_of_week day = End_of_week;
			while (true)
			{
				cout << "Dla jakiego dnia (Monday-Sunday) chcesz usunac seans? ";
				getline(cin, day_name);
				day = day_string_to_enum(day_name, days);
				if (day == Error)
					cout << "Blad. Sprobuj jeszcze raz" << endl;
				else
					break;
			}
			string time_word;
			date current_time;
			while (true)
			{
				cout << "O ktorej godzinie chcesz usunac seans: ";
				getline(cin, time_word);
				if (time_word[2] == ':')
				{
					string hour_word = time_word.substr(0, 2), minutes_word = time_word.substr(3, 2);
					current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
					break;
				}
				else
					if (time_word[1] == ':')
					{
						string hour_word = time_word.substr(0, 1), minutes_word = time_word.substr(2, 2);
						current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
						break;
					}
					else
						cout << "Bledna godzina. Sprobuj jeszcze raz" << endl;
			}
			int hall;
			while (true)
			{
				cout << "W ktorej sali chcesz usunac seans? ";
				string hall_word;
				getline(cin, hall_word);
				if (hall_word.length() < 3)
				{
					hall = atoi(hall_word.c_str());
					if (hall < halls[0])
						break;
					else
						cout << "Numer sali jest za duzy";
				}
				else
					cout << "Nie wpisuj glupot";
			}

			wsk_emission tmp2 = tmp->emissions;
			while (tmp2->next != nullptr)
			{
				if (day == tmp2->day)
				{
					if (current_time.hour == tmp2->start.hour&&current_time.minutes == tmp2->start.minutes)
					{
						if (hall == tmp2->hall)
						{
							if (tmp2 == table[tmp->emissions->hall])
							{
								if (tmp2->next_hall == nullptr)
									table[tmp2->hall] = nullptr;
								else
								{
									table[tmp2->hall] = tmp2->next_hall;
									tmp2->next_hall->prev_hall = nullptr;
									tmp2->next_hall = nullptr;
								}
							}
							else
							{
								if (tmp2->next_hall == nullptr)
								{
									tmp2->prev_hall->next_hall = nullptr;
									tmp2->prev_hall = nullptr;
								}
								else
								{
									tmp2->prev_hall->next_hall = tmp2->next_hall;
									tmp2->next_hall->prev_hall = tmp2->prev_hall;
									tmp2->next_hall = tmp2->next_hall = nullptr;
								}
							}

							if (tmp2 == week)
							{
								if (tmp2->next_week == nullptr)
									week = nullptr;
								else
								{
									week = tmp2->next_week;
									tmp2->next_week->prev_week = nullptr;
									tmp2->next_week = nullptr;
								}
							}
							else
							{
								if (tmp2->next_week == nullptr)
								{
									tmp2->prev_week->next_week = nullptr;
									tmp2->prev_week = nullptr;
								}
								else
								{
									tmp2->prev_week->next_week = tmp2->next_week;
									tmp2->next_week->prev_week = tmp2->prev_week;
									tmp2->next_week = tmp2->next_week = nullptr;
								}
							}

							if (tmp2->prev == nullptr)
							{
								tmp->emissions = tmp2->next;
								tmp2->next = nullptr;
								delete tmp2;
								break;
							}
							else
							{
								tmp2->prev->next = tmp2->next;
								tmp2->next->prev = tmp2->prev;
								tmp2->next = tmp2->prev = nullptr;
								delete tmp2;
								break;
							}
							break;
						}
						else tmp2 = tmp2->next;
					}
					else tmp2 = tmp2->next;
				}
				else tmp2 = tmp2->next;
			}
		}
		else
			cout << "#ERROR : Film nie ma seansow" << endl << endl;
	}
	else
		cout << "#ERROR : Brak filmow w repertuarze" << endl << endl;

}

void buy_ticket(wsk_movie &head, string days[])
{
	cout << "Lista aktualnych filmow:\n";
	wsk_movie tmp = head;
	if (tmp->next != nullptr)
	{
		while (tmp->next != nullptr)
		{
			cout << tmp->name << endl;
			tmp = tmp->next;
		}
		tmp = head;
		cout << endl << "Na jaki film chcesz kupic bilet? ";
		string movie_title;
		bool correct = 0;
		while (!correct)
		{
			getline(cin, movie_title);
			while (tmp->next != nullptr)
			{
				if (tmp->name == movie_title)
				{
					correct = 1;
					break;
				}
				else
					tmp = tmp->next;
			}
			if (tmp->next == nullptr)
				cout << "Brak filmu o podanej nazwie\nWprowadz nazwe filmu: " << endl;
		}
		if (tmp->emissions != nullptr)
		{
			show_movie(tmp->emissions, 0);
			cout << endl;
			string day_name;
			days_of_week day = End_of_week;
			while (true)
			{
				cout << "Na jaki dzien (Monday-Sunday) chcesz kupic bilet? ";
				getline(cin, day_name);
				day = day_string_to_enum(day_name, days);
				if (day == Error)
					cout << "Blad. Sprobuj jeszcze raz" << endl;
				else
					break;
			}
			string time_word;
			date current_time;
			while (true)
			{
				cout << "Na jaka godzine chcesz kupic bilety? ";
				getline(cin, time_word);
				if (time_word[2] == ':')
				{
					string hour_word = time_word.substr(0, 2), minutes_word = time_word.substr(3, 2);
					current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
					break;
				}
				else
					if (time_word[1] == ':')
					{
						string hour_word = time_word.substr(0, 1), minutes_word = time_word.substr(2, 2);
						current_time = { atoi(hour_word.c_str()), atoi(minutes_word.c_str()) };
						break;
					}
					else
						cout << "Bledna godzina. Sprobuj jeszcze raz" << endl;
			}
			wsk_emission tmp2 = tmp->emissions;
			bool sold = 0;
			while (tmp2->next != nullptr)
			{
				if (day == tmp2->day)
				{
					if (current_time.hour == tmp2->start.hour&&current_time.minutes == tmp2->start.minutes)
					{
						if (tmp2->available_seats == 0)
							tmp2 = tmp2->next;
						else
						{
							cout << "Ilosc dostepnych biletow: " << tmp2->available_seats << ". Ile biletow chcialbys kupic?\n";
							while (true)
							{
								cout << "Ilosc:";
								int amount;
								cin >> amount;
								cin.get();
								if (amount > tmp2->available_seats)
									cout << "Podales za duzo ilosc. Sprobuj jeszcze raz\n";
								else
								{
									tmp2->available_seats -= amount;
									cout << "Dziekujemy za zakup. Kupiles " << amount << " bilety na " << tmp->name << " w";
									show_dzien(tmp2->day);
									cout << "na " << tmp2->start.hour << ":" << tmp2->start.minutes << " w sali " << tmp2->hall << endl << endl;
									tmp2 = tmp2->next;
									sold = 1;
									break;
								}
							}
						}
					}
					else tmp2 = tmp2->next;
				}
				else tmp2 = tmp2->next;
			}
			if (!sold)
			{
				cout << "Przepraszamy, nie ma seansu o wskazanej godzinie lub sala jest juz pelna" << endl << endl;
			}
		}
		else
			cout << "#ERROR : Film nie ma seansow" << endl << endl;
	}
	else
		cout << "#ERROR : Brak filmow w repertuarze" << endl << endl;

}

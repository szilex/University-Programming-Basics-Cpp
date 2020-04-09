#include <iostream>
#include "stdafx.h"

using namespace std;

int main()
{
	int menu, r, pole, pod1, pod2, wys;
	cout << "Menu:/n1. Oblicz pole kola/n2. Oblicz pole prostokata/n3. Oblicz pole trojkata/n4. Oblicz pole trapezu/n";
	cin >> menu;
	switch (menu) {
		case 1: {
			cout << "Wprowadz promien kola:";
			cin >> r;
			pole = 3, 14 * r*r;
			cout << "Pole wynosi: " << pole;
			break;}
		case 2: {
			cout << "Wprowadz boki prostokata:";
			cin >> pod1>>pod2;
			pole = pod1*pod2;
			cout << "Pole wynosi: " << pole;
			break;}
		case 3: {
			cout << "Wprowadz podstawe i wysokosc trojkata:";
			cin >> pod1 >> wys;
			pole = pod1*wys/2;
			cout << "Pole wynosi: " << pole;
			break;}
		case 4: {
			cout << "Wprowadz podstawy oraz wysokosc:";
			cin >> pod1 >>pod2 >> wys;
			pole = (pod1+pod2)*wys / 2;
			cout << "Pole wynosi: " << pole;
			break;}
		default: cout << "Umiesz liczyc?";
		}
	
	return 0;
}


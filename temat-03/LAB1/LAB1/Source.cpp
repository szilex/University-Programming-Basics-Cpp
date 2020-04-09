#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int menu;
	do
	{
		cout << "Menu:" << endl << "1. Oblicz pole kola" << endl << "2. Oblicz pole prostokata" << endl << "3. Oblicz pole trojkata" << endl << "4. Oblicz pole trapezu" << endl << "5. Zakoncz program" << endl;
		do {
			cout << "Ktora opcje wybierasz?"<<endl;
			cin >> menu;
		} while (menu<1||menu>5);
		switch (menu) {
		case 1: {
			int  r;
			double pole, pi = 3.14;
			cout << "Wprowadz promien kola:" << endl;
			cin >> r;
			pole = pi*r*r;
			cout << "Pole wynosi: " << pole << endl<<endl;
			break;}
		case 2: {
			int pod1, pod2;
			double pole;
			cout << "Wprowadz boki prostokata:" << endl;
			cin >> pod1 >> pod2;
			pole = pod1*pod2;
			cout << "Pole wynosi: " << pole << endl << endl;
			break;}
		case 3: {
			int pod1, wys;
			double pole;
			cout << "Wprowadz podstawe i wysokosc trojkata:" << endl;
			cin >> pod1 >> wys;
			pole = pod1*wys / 2;
			cout << "Pole wynosi: " << pole << endl << endl;
			break;}
		case 4: {
			int pod1, pod2, wys;
			double pole;
			cout << "Wprowadz podstawy oraz wysokosc:" << endl;
			cin >> pod1 >> pod2 >> wys;
			pole = (pod1 + pod2)*wys / 2;
			cout << "Pole wynosi: " << pole << endl << endl;
			break;}
		case 5: break;
		default: cout << "Umiesz liczyc?" << endl << endl; break;
		}
	} while (menu != 5);
	cout << "Zakonczyles program" << endl;
	return 0;
}
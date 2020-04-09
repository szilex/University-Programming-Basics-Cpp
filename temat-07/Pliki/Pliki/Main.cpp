#include <iostream>
#include <fstream>
using namespace std;

struct punkt
{
	int x, y, z;
};


int main()
{
	/*ofstream str;
	str.open("plik.txt", ios::out);
	str.good();
	str << 123 << endl;
	str << "ABC" << endl;
	str.close();*/


	/*fstream str;
	str.open("pliki.txt", ios::out);
	str.good();
	int  x;
	while (str >> x)
		cout << x << endl;
	str.close();
	cin.get();*/


	/*fstream str;
	str.open("plik.bin", ios::out | ios::binary);
	str.good();
	punkt P;
	str.write((char*)&P, sizeof(punkt));*/                   //konwersja wartoœci na char


	/*int x = 20;
	cout << x << endl;
	cout << &x << endl;*/
	
	/*char c = 'A';
	cout << c << endl;
	cout << (int)c << endl;*/

	/*ifstream str;
	str.open("plik.bin", ios::in / ios::binary);
	str.good();
	punkt P = { 10,20,30 };
	while (str.read((char*)&P, sizeof(punkt)))
		cout << P.x << P.y << P.z;*/

	//Zad1
	fstream str;
	str.open("C:/U¿ytkownicy/Student/Pulpit/szilexpliki.txt", ios::in);
	str.good();
	int x;
	while (str >> x)
		cout << x << endl;
	str.close();
	cin.get();
	return 0;
}



//	ifstream- czytanie,	ofstream- wpisywanie
//	int *w  -  wskaŸnik adresu
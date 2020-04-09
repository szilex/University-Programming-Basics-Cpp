#include "stdafx.h"
#include "iostream"
using namespace std;

int main()
{	
	double delta=0,p1=0,p2=0,x,y,z;
	cout << "Podaj wspolczynniki a,b,c:" << endl;
	cin >> x >> y >> z;
	if (x == 0)
	{
		if (y == 0)
		{
			if (z == 0)
				cout << "Rownanie tozsame :(((((("<<endl;
			else
				cout << "Nawet nie probuj!?"<<endl;
		}
		else
			cout << "Pierwiastkiem jest: " << -z / y<<endl;
	}
	else
	{
		delta = y*y - 4 * x * z;
		if (delta > 0)
		{
			p1 = (0 - y - sqrt(delta)) / (2 * x);
			p2 = (0 - y + sqrt(delta)) / (2 * x);
			cout << "Pierwiastki to: " <<  endl << p1 << endl << p2<<endl;
		}
		else
		{
			if (delta == 0)
			{
				p1 = (-y) / (2 * x);
				cout << "Pierwiastkiem jest: " << p1<<endl;
			}
			else
				cout << "Rownanie nie ma pierwiastkow"<<endl;
		}
	}
	cin.get();
    return 0;
}


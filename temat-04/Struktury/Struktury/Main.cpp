#include <iostream>

using namespace std;

struct punkt
{
	int x, y, z;
};

int main()
{
	punkt p = { 10,20,30 };
	cout << p.x << endl << p.y << endl << p.z;
	cin.get();
	return 0;
}



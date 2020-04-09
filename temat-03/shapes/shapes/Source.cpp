#include <stdio.h>

int main()
{
	double sqrt;
		double x;
		double prevx;
		prevx = 2000.0;
		x = 1000.0;
		while (1)
		{
			prevx = x;
			x = (x + (1000.0)/ x) / 2;

			printf("Square root of %d\n", x);


		}
		getchar();
		return 0;
}
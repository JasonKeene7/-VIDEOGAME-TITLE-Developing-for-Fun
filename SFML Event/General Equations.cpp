#include <cstdio>
#include "General Equations.h"
using namespace std;

void General_Equ::geEq_picker(float* coeff_a, float x_input, int gen_equa)
{
	x_in = x_input;
	for(int assign = 0; assign < gen_equa + 2; assign++)
	{
		printf("Array value %d: %f", assign, x_in);
	}

	switch(gen_equa)
	{
	case LINE: line(); break;
	default: output = 0; break;
	}
}

void General_Equ::line()
{
	output = coeff[0] + coeff[1] * x_in;
}
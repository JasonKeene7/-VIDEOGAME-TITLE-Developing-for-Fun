#pragma once
#ifndef GENERALEQUATIONS_H
#define GENERALEQUATIONS_H

class General_Equ
{
	enum eq_mode {LINE = 0};		//Sets the equation being picked
	float coeff[2];		//Equation coefficients
	float x_in;			//Input X position
	float output;		//Resilting Y poutput

	void line();
public:
	void geEq_picker(float*, float, int);
};

#endif
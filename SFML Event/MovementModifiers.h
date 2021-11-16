#pragma once
using namespace std;

#ifndef MOVEMENTMODIFIERS_H
#define MOVEMENTMODIFIERS_H

class MovMod
{
	enum codition {NORMAL = 0, SLIDE};		//Ground conditions
	float x_modifier = 0, y_modifier = 0;	//Vector modifier values
	float rad_modifier = 0;					//Dx modifier value

public:
	void moveCondition(int, float);		//Get current ground condition
	//Get vector modifiers
	float get_xMod(); float get_yMod(); float get_radMod();
};

#endif
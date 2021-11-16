#include "MovementModifiers.h"
#include <cmath>
using namespace std;

float MovMod::get_xMod() { return x_modifier; }		//Get X vector modifier
float MovMod::get_yMod() { return y_modifier; }		//Get Y vector modifier
float MovMod::get_radMod() { return rad_modifier; }	//Get Dx vector modifier

//Change player movement characteristics based on actions
void MovMod::moveCondition(int moveType, float slope)
{
	rad_modifier = tanh(slope);	//Calculate radian from slope
	switch (moveType)
	{
	case NORMAL:	//Normal/Walking ground movement
		x_modifier = .5 * (1 + tanh(-5 * (abs(rad_modifier) - 1)));
		y_modifier = sin(rad_modifier);
		break;
	case SLIDE:		//Sliding movement
		x_modifier = cos(rad_modifier);
		y_modifier = sin(rad_modifier);
	default: break;
	}
}
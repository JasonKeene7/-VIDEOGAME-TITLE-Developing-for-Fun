#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Collision.h"
using namespace std;

Collision::Collision(int points)
{
	ground_grapher.setPrimitiveType(sf::LinesStrip); ground_grapher.resize(points);
	groundGrapher_p = &ground_grapher;
	level1(points);
}

sf::VertexArray* Collision::ground_p() { return groundGrapher_p; }

/*
* Prepare coordinates to graph the ground.
* Stores ground information so it can be graphed.
* Return collision coordinates.
*/
void Collision::prep_ground(float x_in) { graph_gnd = true;  equ_picker(x_in, 0); }
void Collision::calc_ground(int get_xCoord, int get_yCoord)
{
	save_xCoord = get_xCoord; save_yCoord = get_yCoord;
	graph_gnd = false;
}
sf::Vector2f Collision::get_graphPoints() { return sf::Vector2f(save_xCoord, save_yCoord); }

//Return y collision
float Collision::get_yPos() { return output; }

//Calculates player collision
float Collision::coll_checkY(float x_in)
{
	equ_picker(x_in, 0);
	return output;
}

//Chooses which equation to use based on x coordinate
void Collision::equ_picker(float x_in, bool equSet)
{
	for (int coord_poll = 0; coord_poll < sizeof(equ_arrayX)/sizeof(int) - 1; coord_poll++)
	{
		if (equ_arrayX[coord_poll] <= x_in &&
			equ_arrayX[coord_poll + 1] > x_in) 
		{
			if (equSet == 0) equ_set(coord_poll, x_in);
			else if (equSet == 1) equDx_set(coord_poll, x_in);
			break;
		}
	}
}

//Takes equation number and x coordinate to calculate y vertex/collision
void Collision::equ_set(int equNum, float x_in)
{
	switch (equNum)
	{
	case 0:	output = x_in / 4 + 150; break;
	case 1: output = 250; break;
	case 2: output = -x_in / 4 + 400; break;//200 * sin(x_in/60) + 300; break;
	default: break;
	}
	
	if (graph_gnd) calc_ground(x_in, output);
}
//Calculate derivative of position to affect player speed when on ground
void Collision::equDx_set(int equNum, float x_in)
{
	switch (equNum)
	{
	case 0:	outputDx = .25; break;
	case 1: outputDx = 0; break;//10 / 3 * cos(x_in / 60); break;
	case 2: outputDx = -.25; break;
	default: break;
	}
}
float Collision::get_Dx() { return outputDx; }

void Collision::level1(int points)
{
	for (int input = 0; input < points; input++)
	{
		prep_ground(float(input * 1000 / points));
		ground_grapher[input].position = get_graphPoints();
		if (input > 600) ground_grapher[input].color = sf::Color::Transparent;
		else ground_grapher[input].color = sf::Color::Red;
	}
}
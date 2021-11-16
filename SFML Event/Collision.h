#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

#ifndef COLLISION_H
#define COLLISION_H

class Collision
{
	//Members
	sf::VertexArray ground_grapher;
	sf::VertexArray* groundGrapher_p;

	bool graph_gnd = false;					//Used to switch between Fx graphing and player collision
	float x_offset = 0;						//Stores player boundary box information
	float save_xCoord = 0, save_yCoord = 0;	//Stores player cordinates to be used in collision Fx's
	bool save_airBorne = false;				//Save player's airborne state
	int equ_arrayX[4] = { 0, 400, 600, 1000};	//X coordnates used to determine which equation to use
	float output = 0, outputDx = 0;			//Stores equation and slope output
	/*
	* If Im going to have more than one player, then it will 
	* be best if I store these variables in arrays
	*/


	//Methods
	void level1(int);
	void equ_set(int, float);	//A set of equations
	void equDx_set(int, float);	//A set of equations
	void calc_ground(int, int);	//Calculaues ground collision

public:
	Collision(int);
	sf::VertexArray* ground_p();
	float get_yPos();				//Returns current y collision value
	void prep_ground(float);		//Takes in x coordinates and prepares for ground graphing
	float coll_checkY(float);	//Checks if player coordinates intersect with the ground
	sf::Vector2f get_graphPoints();	//Returns vertes points for to graph the ground
	void equ_picker(float, bool);			//Picks which equation to run based on x coordinate	
	float get_Dx();				//get the equation's current slope
};

#endif
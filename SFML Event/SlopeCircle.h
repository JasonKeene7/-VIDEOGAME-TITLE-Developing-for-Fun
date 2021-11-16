#pragma once
#include <SFML/Graphics.hpp>

#ifndef SLOPECIRCLE_H
#define SLOPECIRCLE_H

class SlopeCircle
{
	sf::CircleShape display;			//Display object
	sf::CircleShape *display_p = NULL;	//Display pointer

	sf::VertexArray VectorX;			//X vector object
	sf::VertexArray *xVector_p = NULL;	//X vector line pointer
	sf::Vertex *xVector_pa[2];			//X vector vertex pointers
	
	sf::VertexArray VectorY;			//Y vector object
	sf::VertexArray *yVector_p = NULL;	//Y vector line pointer
	sf::Vertex *yVector_pa[2];			//Y vector vertex pointers
	
	sf::VertexArray VectorDx;			//Dx object
	sf::VertexArray *dxVector_p = NULL;	//Dx vector line pointer
	sf::Vertex *dxVector_pa[2];			//Dx vector vertex pointers

	
	float radius = 50;					//Circle radius
	float x_pos = 0, y_pos = 0;			//Position of cicle
	float lineRad = 0;					//Line angle in radians
	float x_vector = 0, y_vector = 0;	//Vector endpoint positions
	float x_max = 0, y_max = 0;			//Maximum (expected) vector values
	
	sf::Vector2f location();	//Get display location
	float get_radius();			//Get display radius
	sf::Vector2f line_center();	//Get display location

	sf::Vector2f xVector_pos();		//Calculate X vector endpoint
	sf::Vector2f yVector_pos();		//Calculate Y vectr endpoint
	sf::Vector2f dxVector_pos();	//Calculate Dx vector endpoint
	
public:
	sf::CircleShape* display_circle();	//Return display pointer
	sf::VertexArray* get_xVector();		//Return X vector
	sf::VertexArray* get_yVector();		//Return Y vector
	sf::VertexArray* get_dxVector();	//Return Dx vector

	SlopeCircle(float, float, float, float);	//Setup vector dislpay
	void set_parameters(float, float, float);	//Store vector parameters
	void update();								//Update display
};

#endif
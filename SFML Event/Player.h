#pragma once
#include <SFML/Graphics.hpp> 
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	//Members
	sf::VertexArray player;					//SFML player object
	sf::VertexArray* player_p = nullptr;	//Player pointer
	sf::Vertex *playerV_a[4];				//Player vertex pointer array

	float frame_speed = 0;			//Adjust movement speed based on framerate
	float width = 20, height = 30;	//Player box size

	//Enum for all usable buttons and a variable to save the last button pressed
	enum buttons {NALR = -1, LEFT, RIGHT, NADU, UP, DOWN};
	int last_buttons[3];	//Input buffer

	//Parametric variables, used to alter the player's position
	float x_pos = 500, y_pos = 0;				//Player coordinates
	float x_vel = 0, y_vel = 0;					//Player velocity
	const int max_xVel = 10, min_xVel = -10;	//Horizantal movement bounds
	const int max_yVel = 20;					//Max fall speed
	const float x_acc = 1.2, y_acc = 1;			//Player acceleration constant
	float x_velSde = 0;							//Player sliding velocity
	const int max_xSld = 30, min_xSld = -30;	//Sliding velocity bounds

	float radian = 0;			//Used to calculate sliding speed
	float x_mod = 0, y_mod = 0;	//Vector adjustment based on current slope

	int direction = 1;			//Saves if player is moving left (-1), right (1), or neither (0)
	bool is_airborne = false;	//Player's airborne state
	bool is_sliding = false;	//Player's sliding state
	bool stop_sliding = false;	//Stop sliding flag
	float slide_start = 0;		//Initial slide height

	float HS_friction = 0.7, LS_friction = 1.1;	//Player friction
	const int grinding = 2, drag = 10;			//Friction modifiers

	const float gravity = 3;	//Player gravity
	float valley = 0;			//Lowest sliding height
	const float stick = 3;		//Maximum height off ground where player can still be seen as 'grounded'

	//Methods
	void player_position(int);			//Get player
	void set_xPos(); void set_yPos();	//Sets player position
	void jump();						//Changes player's Y position if airborne

public:
	Player(int);						//Set player seed based on framerate
	sf::VertexArray* player_pointer();	//Get player pointer
	sf::Vector2f player_vertex(int);	//Get player vertex coordinates
	
	void update();				//Update player
	void player_action(int);	//Handles the player's keyboard inputs

	float get_height(); float get_width();	//Get player's height and width
	float get_xCoord(); float get_yCoord();	//Get coordinates of player
	int get_xVel(bool); int get_yVel();	//Get velocity of player
	
	//Set all vector modifications
	void set_xMod(float); void set_yMod(float);	void set_radian(float);
	void reset_yCoord(float); void reset_xCoord(float);	//Resets player's position is they are too low
	void change_xVel(); void change_yVel();				//Change player's velocity
	void set_xAcc(int); void set_yAcc(int);				//Update player velocity

	bool player_airborne();	//Get player's airborne state
	bool player_slide();	//Get player's slide state
	void air_check(float);	//Checks if the player is airborne or not
};

#endif
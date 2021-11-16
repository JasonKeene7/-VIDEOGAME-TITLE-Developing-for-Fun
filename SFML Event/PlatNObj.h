#include <SFML/Graphics.hpp>

#ifndef PLATFORMSNOBJECTS_H
#define PLATFORMSNOBJECTS_H

class Platforms_and_Objects
{
	/*Arrays are split into even intervals: i.e. 100 200 etc,
	* and whatever platforms and objects (collisions) are within
	* those bounds are drawn if within window or collision checked
	* if player is within area
	*/
	sf::VertexArray plat1;
	sf::VertexArray* plat_onScreen_pa[5];
	enum coll_type {LINE = 0, QUAD};
	float x_offset_a[5];
	float y_offset_a[5];
	float dx_a[5];
	float ddx_a[5];
	float dddx_a[5];

	int division = 0;					//Length of each quadrant
	float x_pos = 0;
	int player_quad = 0, prev_quad = 0;	//Get and store the quad of player

	int PnA_collision = 0;	//Point to collision fx
	int PnA_position = 0;	//Point to location fx

	float y_pos = 0;

	float line(int, float);

	int quad_finder();
	float collision_calc(float, float, float);
	void pointer_null(int);
	void level1();
public:
	Platforms_and_Objects(int);
	float equ_picker(int, float);
	int get_quad();
	int onScreen_buffer();
	sf::VertexArray* quad_loader(float);
	float collision_loader(float, float);
};

#endif
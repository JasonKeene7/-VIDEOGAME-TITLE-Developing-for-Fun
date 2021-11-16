#include <cstdio>
#include <SFML/Graphics.hpp>
#include "Developer_Tools.h"
using namespace std;

DevTools::DevTools(bool activate):slopeDisplay(850, 550, 1, 1), playerVectors(850, 450, 10, 30),
equ(sf::LineStrip, 2), equ1(sf::LineStrip, 2)
{
	printf("\n-----DEELOPER TOOLS-----\n");
	if (activate)
	{
		//Lists active tools
		for (int tool = 0; tool < sizeof(dev_toolBox) / sizeof(bool); tool++)
		{
			switch (tool)
			{
			case GVER: 
				printf("Ground Vectors"); 
				//Store adresses to ground slope vectors
				ground_vectors = slopeDisplay.display_circle();
				groundX_vector = slopeDisplay.get_xVector();
				groundY_vector = slopeDisplay.get_yVector();
				groundDx_vector = slopeDisplay.get_dxVector();
				break;
			case PVER: printf("Player Vectors"); 
				//Store adresses to player movement vectors
				player_vectors = playerVectors.display_circle();
				playerX_vector = playerVectors.get_xVector();
				playerY_vector = playerVectors.get_yVector();
				playerDx_vector = playerVectors.get_dxVector();
				break;
			case PLINE: printf("Player Pointer");
				//Set up player pointers
				equ[0].position = sf::Vector2f(500.f, 350.f); equ[0].color = sf::Color::Magenta; equ[1].color = sf::Color::Red;
				equ1[0].position = sf::Vector2f(500.f, 350.f); equ1[0].color = sf::Color::Magenta; equ1[1].color = sf::Color::Red;
				break;
			case VALCOMP: printf("Loop States"); break;
			default: break;
			}
			//Display develeoper tool state
			if (dev_toolBox[tool]) printf("\t: ACTIVE\n");
			else printf("\t: DISABLED\n");
		}
	}
	else printf("ALL TOOLS DISABLED\n");
}

bool DevTools::open_toolbox(uint8_t use_tool) 
{
	//Ensure use_tool does not exceed array size
	if (use_tool >= max_loop) { printf("No developer tool there!"); return false; }
	else return dev_toolBox[use_tool]; 
}
void DevTools::window_pointer(sf::RenderWindow* p_window) { p_gWindow = p_window; }
void DevTools::movMod_pointer(MovMod* p_player1) { p_slopeP1 = p_player1; }
void DevTools::player_pointer(Player* p_player1) { character = p_player1; }
void DevTools::set_now(float now_value, uint8_t block)
{
	//Ensure block does not exceed array size
	if (block >= max_loop) block = max_loop - 1;
	now_val[block] = now_value; 
}

//Only display activ developer tools
void DevTools::draw_tools()
{
	if (dev_toolBox[GVER]) ground_vector();
	if (dev_toolBox[PVER]) player_vector();
	if (dev_toolBox[PLINE]) position_vectors();
	if (dev_toolBox[VALCOMP]) loop_values();
}

void DevTools::ground_vector()
{
	slopeDisplay.update();			//Update vectors positions
	slopeDisplay.set_parameters(p_slopeP1->get_xMod(), p_slopeP1->get_yMod(), p_slopeP1->get_radMod());
	p_gWindow->draw(*ground_vectors); p_gWindow->draw(*groundX_vector);
	p_gWindow->draw(*groundY_vector); p_gWindow->draw(*groundDx_vector);
}

void DevTools::player_vector()
{
	playerVectors.update();		//Update vector positions
	playerVectors.set_parameters(character->get_xVel(1), character->get_yVel(), 0);
	p_gWindow->draw(*player_vectors); p_gWindow->draw(*playerX_vector);
	p_gWindow->draw(*playerY_vector); p_gWindow->draw(*playerDx_vector);
}

void DevTools::position_vectors()
{
	equ[1].position = character->player_vertex(0);
	equ1[1].position = character->player_vertex(1);
	p_gWindow->draw(equ); p_gWindow->draw(equ1);
}

void DevTools::loop_values()
{
	//Process current and previous values
	//Check if previous and current values are different
	first_display = true;
	for (int comp_iter = 0; comp_iter < 5; comp_iter++)
	{
		if (now_val[comp_iter] == prev_val[comp_iter]) continue;    //If current value equals the previous value: skip
		//Print all different values
		else
		{
			if (first_display) { printf("---NEW LOOP---\n"); first_display = false; }
			printf("VALUE %d: %.3f --> %.3f\n", comp_iter, prev_val[comp_iter], now_val[comp_iter]);
			prev_val[comp_iter] = now_val[comp_iter];
		}
		if (comp_iter = 4) printf("\n");    //Add extra line for readability
	}
}
#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MovementModifiers.h"
#include "SlopeCircle.h"
using namespace std;

#ifndef DEVELOPERTOOLS_H
#define DEVELOPERTOOLS_H
class DevTools
{
   /*
   * Currently available developer tools.
   * 0: Display ground vertecies
   * 1: Display player vertecies
   * 2: Point to player's current position
   * 3: Store, display, and process values from previous loops
   */
    enum dev_lebels { GVER = 0, PVER, PLINE, VALCOMP };
    bool dev_toolBox[4] = { 0, 1, 1, 0 };               //Toggle specific deeloper tools on/off

    sf::RenderWindow* p_gWindow = nullptr;              //Game window pointer

    //Ground slope display
    MovMod* p_slopeP1;                                  //Movement modifier ponter 
    SlopeCircle slopeDisplay;                           //Set display X&Y-coord and maximum expected X&Y value input
    sf::CircleShape* ground_vectors = nullptr;          //Get and set display background
    sf::VertexArray* groundX_vector = nullptr;          //Get and set X vector
    sf::VertexArray* groundY_vector = nullptr;          //Get and set Y vector
    sf::VertexArray* groundDx_vector = nullptr;         //Get and set derivative vector
    void ground_vector();                               //Draw ground slope vectors

    //Player vector display
    Player* character = nullptr;
    SlopeCircle playerVectors;                          //Set display X&Y-coord and maximum expected X&Y value input
    sf::CircleShape* player_vectors = nullptr;          //Get and set display background
    sf::VertexArray* playerX_vector = nullptr;          //Get and set X vector
    sf::VertexArray* playerY_vector = nullptr;          //Get and set Y vector
    sf::VertexArray* playerDx_vector = nullptr;         //Get and set derivative vector
    void player_vector();                               //Draw player vectors

    //Vectors pointing to player position
    sf::VertexArray equ; sf::VertexArray equ1;          //Pointer line coordinates
    void position_vectors();                            //Draw player ponter lines

    bool first_display = true;                          //Notifies if new loop values are displayed
    float now_val[5] = { 0, 0, 0, 0, 0 };               //Store current loop value. 
    float prev_val[5] = { 0, 0, 0, 0, 0 };              //Store previous loop value.
    const uint8_t max_loop = sizeof(now_val) / sizeof(float);
    void loop_values();                                 //Display loop value changes
public:
	DevTools(bool);
    bool open_toolbox(uint8_t);                 //Return developer tool values to skip setup
    void window_pointer(sf::RenderWindow*);     //Store window pointer
    void movMod_pointer(MovMod*);               //Store movement modifier pointer
    void player_pointer(Player*);               //Store player pointer
    void set_now(float, uint8_t);               //Set loop values
    void draw_tools();
};

#endif

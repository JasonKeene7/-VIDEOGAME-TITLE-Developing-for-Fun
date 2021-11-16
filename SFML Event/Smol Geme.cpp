#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <SFML/Graphics.hpp> 
#include "Developer_Tools.h"
#include "Event Clock.h"
#include "Player.h"
#include "Collision.h"
#include "General Equations.h"
#include "SlopeCircle.h"
#include "MovementModifiers.h"
#include "PlatNObj.h"
using namespace std;

int main()
{
#pragma region Variables
    //Variables
    int width = 1000, height = 700;                         //Window widthand height
    int frames = 60;                                        //Window update rate
    const int points = 500;                                 //Number of points used to graph the ground
    enum inputs { NALR = -1, LEFT, RIGHT, NADU, UP, DOWN }; //Stores Keyboard inputs. Matches with player class inputs
    bool input_flag = false;                                //Saves general player input state
    enum codition { NORMAL = 0, SLIDE };                    //Ground friction states
#pragma endregion

#pragma region Player&Back
    //Prepares and graphs the ground
    Collision ground(points);                               //Set the roughness of the ground line
    sf::VertexArray* ground_pointer = ground.ground_p();    //Get and set pointer to ground SFML object
    float collision_height = 0;                             //Stores the closest collision below the player
    float next_ground = 0;                                  //Stors the ground coordinates
    MovMod slope_p1;                                        //Ground friction conditions
    //Could I consilidate the collision height and next ground since they both check for the closest ground collision below player?
    //Yes, but only if the object collision class works like the ground collision one

    //Starts platNobj class
    Platforms_and_Objects obsticles(100);                   //Set division width for (un)loading obsticles
    int onScreen_buffer = obsticles.onScreen_buffer();      //Get the size of the platform pointer array
    sf::VertexArray* object_onscreen = NULL;                //Get pointers to all onscreen objects
    //object_onscreen should become an array when object class is properly made

    //Player setup
    Player player1(frames);                                 //Set the player framerate
    sf::VertexArray* player1_p = player1.player_pointer();  //Get and setplayer char pointer
    sf::Vector2f* player1V_p = NULL;                        //Get player vertex pointer
#pragma endregion

#pragma region GameWindow
    //Create window environment
	sf::RenderWindow game_window(sf::VideoMode(width, height), "SFML Event");       //Create game window
    //Set window parameters
    game_window.setKeyRepeatEnabled(false); game_window.setFramerateLimit(frames); 
    game_window.setPosition(sf::Vector2i(350, 0));          //Set window positions
    sf::Event close_flag;                                   //Check if window is closing

    //Create skybox
    sf::VertexArray sky(sf::Quads, 4);
    sky[0].position = sf::Vector2f(0.f, 0.f); sky[0].color = sf::Color::Color(0, 10, 255, 255);
    sky[1].position = sf::Vector2f(float(width), 0.f); sky[1].color = sf::Color::Color(0, 10, 255, 255);
    sky[2].position = sf::Vector2f(float(width), 150.f); sky[2].color = sf::Color::Color(0, 90, 255, 255);
    sky[3].position = sf::Vector2f(0.f, 400.f); sky[3].color = sf::Color::Color(0, 90, 255, 255);
#pragma endregion

#pragma region Devtools
    DevTools tools(true);
    tools.window_pointer(&game_window);
    if (tools.open_toolbox(0)) tools.movMod_pointer(&slope_p1);
    if (tools.open_toolbox(1) || tools.open_toolbox(2)) tools.player_pointer(&player1);
#pragma endregion
    
    //Game window. Could store all other draws in their respective classes, much less fetching shoud occur
    while (game_window.isOpen())
    {
        //Close window if CLOSE button is clicked
        while (game_window.pollEvent(close_flag))
        {
            if (close_flag.type == sf::Event::Closed) game_window.close();
            //Should place class deconstructors here
        }

        //Values to be calculated before player movement to determine HOW the player should move
        ground.equ_picker(player1.get_xCoord(), 1);             //Set current ground position
        slope_p1.moveCondition(NORMAL, ground.get_Dx());        //Set current ground condition
        //Should change ground conditions if player is on an object
        player1.set_radian(ground.get_Dx());                    //Set the player's current ground slope
        player1.set_xMod(slope_p1.get_xMod());                  //Modify the player's X vector
        player1.set_yMod(slope_p1.get_yMod());                  //Modify the player's Y vector

        //Takes horizantal inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player1.player_action(LEFT);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player1.player_action(RIGHT);
        else player1.player_action(NALR);

        //Takes Vertical inputs.
        //A new if statement is started so the player can slide and jump at the same time.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { player1.player_action(UP); input_flag = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { player1.player_action(DOWN); input_flag = true; }
        if (!input_flag) player1.player_action(NADU);   //Only run if neither of the above are pressed
        input_flag = false;                             //Return flag to strting state
        //Being able to jump and slide at the same time lowers max jump height b/c jump method is called twice, a very intresting outcome.

        //Change the object collision check if the object class works like the ground collision class
        //Check which object collision is the player closest above
        collision_height = obsticles.collision_loader(player1.get_xCoord(), player1.get_yCoord());
        if (collision_height < 0)
        {
            //Get ground collision if player is below all objects
            next_ground = ground.coll_checkY(player1.get_xCoord());
        }
        //Get the object collision
        else next_ground = obsticles.equ_picker(0, player1.get_xCoord());

        //Update player properties
        player1.update();                           //Update player position
        player1.air_check(next_ground);             //Check if player is airborne
        player1.reset_yCoord(next_ground);          //Reset player height if it's within a collision

        game_window.clear();    //Clear game window
        //Draw the game environments
        game_window.draw(sky); game_window.draw(*ground_pointer);

        //Get pointers to all onscreen objects
        object_onscreen = obsticles.quad_loader(player1.get_xCoord());
        if (object_onscreen != NULL)
        {
            game_window.draw(*object_onscreen); //Display first object since it's known that it exists
            //Cycle through and display all remaining platforms in the array
            /*for (int object_count = 1; object_count < onScreen_buffer; object_count++)
            {
                if(object_onscreen == NULL) break;  //If element is NULL breal loop, last object has already been reached
                game_window.draw(*object_onscreen); //Display object
            }*/
        }

        if (tools.open_toolbox(3)) tools.set_now(player1.get_xCoord(), 0);
        tools.draw_tools();                 //Draw active developer tools
        game_window.draw(*player1_p);       //Draw player and player
        game_window.display();              //Display window elements
    }
	return 0;
}
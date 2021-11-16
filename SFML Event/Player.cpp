#include "Player.h"
#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;

//Setup player
Player::Player(int fps) 
{ 
    frame_speed = 40 / float(fps);  //Set player framerate
    
    //Set SFML type and number of veriecies for the player
    player.setPrimitiveType(sf::Quads); player.resize(4); player_p = &player;
    //Prepare player vertecies
    for (int p_ver = 0; p_ver < 4; p_ver++)
    {
        playerV_a[p_ver] = &player[p_ver];      //Declares player pointer
        player_position(p_ver);                 //Initializes player position
        player[p_ver].color = sf::Color::Red;   //Initialize player color
    }
}

sf::VertexArray* Player::player_pointer() { return player_p; }  //Return player pointer
float Player::get_height() { return height; }                //Return player height
float Player::get_width() { return width; }                  //Return player width

//All of the player's available actions
void Player::player_action(int action)
{
    switch (action)
    {
    //Left and Right
    case NALR: direction = 0; change_xVel(); break;
    case LEFT: direction = -1; change_xVel(); break;
    case RIGHT: direction = 1; change_xVel(); break;
    
    //Up and Down
    case NADU:
        if (is_sliding) { is_sliding = false; stop_sliding = true; }
        if (is_airborne) jump();
        change_yVel(); break;
    case UP:
        //Start jump if player is grounded
        if (!is_airborne) { is_airborne = true; y_vel = -20; }
        jump();     //This can be placed outside of air check b/c player will jump if not in the air
        change_yVel(); break;
    case DOWN:
        if (is_airborne) jump();
        is_sliding = true; slide_start = y_pos;
        change_yVel(); break;

    default: break;
    }
}

//Update player properties for drawing
void Player::update()
{
    //Update X and Y position
    set_xPos(); set_yPos();
    //Update each of the player vertecies
    for (int playerV = 0; playerV < 4; playerV++)
    {
        player_position(playerV);   //Update player position

        //Change player color based on player action
        if (is_sliding) playerV_a[playerV]->color = sf::Color::Cyan;
        else if (is_airborne) playerV_a[playerV]->color = sf::Color::Yellow;
        else playerV_a[playerV]->color = sf::Color::Red;
    }
}
bool Player::player_airborne() { return is_airborne; }  //Return player's airborne state
bool Player::player_slide() { return is_sliding; }      //Return player's sliding state
void Player::air_check(float y_check)
{
    //Calculate player's stickiness to the ground
    float stickiness = y_pos + height + stick + 3 * (-tanh(.5 * abs(x_vel) - 2) + 1);
    //Player sticks to ground if sliding
    if (is_sliding && !is_airborne) y_pos = y_check - height;
    //If the player is traveling at low enough speeds, player will stick to ground
    else if (y_check < stickiness && !is_airborne) y_pos = y_check - height;
    //Check if either clipping or is airborne
    else
    {
        if (y_check <= y_pos + height) { is_airborne = false; y_vel = 0; }
        else is_airborne = true;
    }
}

//Return player box coordinates
void Player::player_position(int vertex)
{
    switch (vertex)
    {
    case 0: playerV_a[0]->position = sf::Vector2f(x_pos, y_pos + height); break;
    case 1: playerV_a[1]->position = sf::Vector2f(x_pos + width, y_pos + height); break;
    case 2: playerV_a[2]->position = sf::Vector2f(x_pos + width, y_pos); break;
    case 3: playerV_a[3]->position = sf::Vector2f(x_pos, y_pos); break;
    default: break;
    }
}
//Get player vertex positions
sf::Vector2f Player::player_vertex(int vertex)
{
    switch (vertex)
    {
    case 0: return playerV_a[0]->position; break;   //Return vertex0 coord
    case 1: return playerV_a[1]->position; break;   //Return vertex1 coord
    case 2: return playerV_a[2]->position; break;   //Return vertex2 coord
    case 3: return playerV_a[3]->position; break;   //Return vertex3 coord
    default: return sf::Vector2f(0.f, 0.f); break;  //Return a coord @ (0,0) just in case
    }
}

//Return X or Y coordinate
float Player::get_xCoord() { return x_pos + x_velSde + x_vel; }
float Player::get_yCoord() { return y_pos + height; }
//Return X or Y velocity
int Player::get_xVel(bool entire) { if (!entire) return x_vel; else return x_vel + x_velSde; }
int Player::get_yVel() { return y_vel; }

//Set X, Y, or radian vector modifiers
void Player::set_xMod(float in_xMod) { x_mod = in_xMod * frame_speed; }
void Player::set_yMod(float in_yMod) { y_mod = in_yMod * frame_speed; }
void Player::set_radian(float in_radian) { radian = in_radian; }
//Set player's X or Y position
void Player::set_xPos()
{
    x_pos += x_vel + x_velSde;
    //Make a player camera class/method and move the two lines below there
    if (x_pos > 1000) x_pos = 0; else if (x_pos < 0) x_pos = 1000;
}
void Player::set_yPos() { y_pos += y_vel; }
//Change X or Y coordinate
void Player::reset_xCoord(float change_x) { x_pos = change_x; }
void Player::reset_yCoord(float change_y){ if (y_pos >= change_y - height) y_pos = change_y - height; }
//Set X or Y acceleration
void Player::set_xAcc(int change_xA) { x_vel = change_xA; }
void Player::set_yAcc(int change_yA) { y_vel = change_yA; }

//Change player's X or Y velocity
void Player::change_xVel()
{
    //Apply high speed friction to player's X vector
    if (direction == 1) { (x_vel <= max_xVel) ? x_vel += x_acc * x_mod : x_vel = max_xVel; }
    else if (direction == -1) { (x_vel >= min_xVel) ? x_vel += -x_acc * x_mod : x_vel = min_xVel; }
    //Apply low speed friction to player
    else
    {
        if (x_vel > 0.5) x_vel += -LS_friction * x_mod;     
        else if (x_vel < -0.5) x_vel += LS_friction * x_mod;
        else x_vel = 0; //Stop player if they are going slow enough
    }
}
void Player::change_yVel()
{
    if (is_sliding && !stop_sliding && !is_airborne)
    {
        //Get initial height of player so they can't slide back up to their origional height
        //If the player's height is exceeded by external means, then their slide start value should change
        float potential = pow(slide_start - y_pos, 2);                          
        
        //If the Y position is lower than a known valley depth, the position becones the new valley
        if (valley < y_pos) valley = y_pos;                                     

        x_velSde += gravity * sin(radian) * x_mod * (pow(-2, - potential) + 1); //Calculate player's X velocity
        
        //Friction always points in the oposite direction as the player's velocity
        if (x_velSde > 0.8) x_velSde -= HS_friction; else if (x_velSde < -0.8) x_velSde += HS_friction;
        
        //If the object is going slow, the low speed friction will take over
        else 
        { 
            if (x_velSde > 0.5) x_velSde -= LS_friction;
            else if (x_velSde < -0.5) x_velSde += LS_friction;
            //Brings the player to a stop if the turnaround height is close to the valley
            else if (valley - y_pos <= 7) { x_velSde = 0; valley = 0; stop_sliding = true; }
        }
        //Cap player's sliding velocity
        if (x_velSde >= max_xSld) x_velSde = max_xSld; else if (x_velSde <= min_xSld) x_velSde = min_xSld;
    }

    //Sliding mechanics when player lets go of slide button
    else if (stop_sliding)
    {
        //Slow down player's slide velocity with high speed friction
        if (x_velSde > 2) x_velSde -= HS_friction * grinding; else if (x_velSde < -2) x_velSde += HS_friction * grinding;
        //Slow down player's sliding velocity with low speed friction
        else 
        {
            if (x_velSde > 1.3) x_velSde -= LS_friction * grinding;
            else if (x_velSde < -1.3) x_velSde += LS_friction * grinding;
            //Stop player if slide velocity is too low
            else { x_velSde = 0; valley = 0; stop_sliding = false; }
        }
    }

    //Slightly slow down player if airborne
    else if (is_sliding && is_airborne)
    {
        if (x_velSde > 0.3) x_velSde -= HS_friction / drag;
        else if (x_velSde < -0.3) x_velSde += HS_friction / drag;
        else x_velSde = 0;
    }
}
//change player's Y velocity when airborne
void Player::jump()
{
    y_vel += gravity * frame_speed;         //Change Y velocity from gravity
    if (y_vel > max_yVel) y_vel = max_yVel; //Terminal velocity
}
#include "SlopeCircle.h"
#include <cmath>
#include <cstdio>
#include <SFML/Graphics.hpp>
using namespace std;

SlopeCircle::SlopeCircle(float x_in, float y_in, float in_maxX, float in_maxY)
{
    //Set display position
	x_pos = x_in; y_pos = y_in;
    //Set maximum vector length
	x_max = in_maxX; y_max = in_maxY;

    //Declare display object
    display.setRadius(radius); display_p = &display;
    display.setFillColor(sf::Color(255, 255, 255, 100));
    display.setPosition(location());

    //X vector
    VectorX.setPrimitiveType(sf::Lines); VectorX.resize(2); xVector_p = &VectorX;
    xVector_pa[0] = &VectorX[0]; xVector_pa[1] = &VectorX[1];
    VectorX[0].position = line_center(); VectorX[0].color = sf::Color::Blue;
    VectorX[1].color = sf::Color::Blue;
    //Y vector
    VectorY.setPrimitiveType(sf::Lines); VectorY.resize(2); yVector_p = &VectorY;
    yVector_pa[0] = &VectorY[0]; yVector_pa[1] = &VectorY[1];
    VectorY[0].position = line_center(); VectorY[0].color = sf::Color::Green;
    VectorY[1].color = sf::Color::Green;
    //Current Slope
    VectorDx.setPrimitiveType(sf::Lines); VectorDx.resize(2); dxVector_p = &VectorDx;
    dxVector_pa[0] = &VectorDx[0]; dxVector_pa[1] = &VectorDx[1];
    VectorDx[0].position = line_center(); VectorDx[0].color = sf::Color::Red;
    VectorDx[1].color = sf::Color::Red;
}

//Reurn all vector pointers
sf::CircleShape *SlopeCircle::display_circle() { return display_p; }
sf::VertexArray *SlopeCircle::get_xVector() { return xVector_p; }
sf::VertexArray *SlopeCircle::get_yVector() { return yVector_p; }
sf::VertexArray *SlopeCircle::get_dxVector() { return dxVector_p; }

//Update vector positions
void SlopeCircle::set_parameters(float in_x, float in_y, float in_radian) 
{ 
    lineRad = in_radian; x_vector = in_x; y_vector = in_y; 
}
//Update vector positions
void SlopeCircle::update()
{
    xVector_pa[1]->position = xVector_pos();    //X vevtor
    yVector_pa[1]->position = yVector_pos();    //Y vector
    dxVector_pa[1]->position = dxVector_pos();  //Dx vector
}

//Get static circle positions
float SlopeCircle::get_radius() { return radius; }
sf::Vector2f SlopeCircle::location() { return sf::Vector2f(x_pos, y_pos); }
sf::Vector2f SlopeCircle::line_center() { return sf::Vector2f(x_pos + radius, y_pos + radius); }

//Get vector line endings
sf::Vector2f SlopeCircle::xVector_pos() { return sf::Vector2f(x_pos + radius * (1 + x_vector/x_max), y_pos + radius); }
sf::Vector2f SlopeCircle::yVector_pos() { return sf::Vector2f(x_pos + radius, y_pos + radius * (1 + y_vector/y_max)); }
sf::Vector2f SlopeCircle::dxVector_pos() { return sf::Vector2f(x_pos + radius * (1 + x_vector / x_max), y_pos + radius * (1 + y_vector/y_max)); }
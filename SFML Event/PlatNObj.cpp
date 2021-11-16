#include "PlatNObj.h"
#include <stdio.h>
using namespace std;

Platforms_and_Objects::Platforms_and_Objects(int div_length) 
{
    division = div_length; 
    level1();
}
int Platforms_and_Objects::onScreen_buffer() { return sizeof(plat_onScreen_pa); }

int Platforms_and_Objects::quad_finder()
{
	player_quad = int(x_pos / division);
	//if (player_quad != prev_quad) printf("Player quadrant: %d\n", player_quad);	//Print player quad: DEV
	//prev_quad = player_quad;
	//Use this mx to load all necessary obsticles
    return player_quad;
}
int Platforms_and_Objects::get_quad() { return player_quad; }

float Platforms_and_Objects::equ_picker(int selection, float x_in)
{
    switch (selection)
    {
    case LINE: return line(0, x_in); break;
    default: return 0; break;
    }
}

float Platforms_and_Objects::line(int selection, float x_in)
{
	return dx_a[selection] * (x_in - x_offset_a[selection]) + y_offset_a[selection];
}

//Is there a way to otomize this?
sf::VertexArray* Platforms_and_Objects::quad_loader(float player_xPos)
{
    switch (player_quad)
    {
    case 0:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 1:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 2: 
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 3:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 4:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 5:
        plat_onScreen_pa[0] = &plat1;  pointer_null(1); return plat_onScreen_pa[0]; break;
    case 6:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 7:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 8:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 9:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 10:
        plat_onScreen_pa[0] = &plat1; pointer_null(1); return plat_onScreen_pa[0]; break;
    case 11:
        pointer_null(0); return NULL; break;
    default:
        pointer_null(0); return NULL; break;
    }
}
float Platforms_and_Objects::collision_loader(float player_xPos, float player_yPos)
{
    x_pos = player_xPos;
    //draw nessesary platforms/objects
    switch (quad_finder())
    {
    case 0:
        plat1[0].color = sf::Color::Red; plat1[1].color = sf::Color::Red;
        return -1; break;
    case 1:
        plat1[0].color = sf::Color::Red; plat1[1].color = sf::Color::Red;
        return -1; break;
    case 2:
        plat1[0].color = sf::Color::Yellow; plat1[1].color = sf::Color::Yellow;
        if (player_xPos < plat1[0].position.x - 20.f) { return -1; break; }
        else { return collision_calc(player_xPos, player_yPos, plat1[0].position.y); break; }
    case 3:
        plat1[0].color = sf::Color::Yellow; plat1[1].color = sf::Color::Yellow;
        return collision_calc(player_xPos, player_yPos, plat1[0].position.y); break;
    case 4:
        plat1[0].color = sf::Color::Yellow; plat1[1].color = sf::Color::Yellow;
        return collision_calc(player_xPos, player_yPos, plat1[0].position.y); break;
    case 5:
        plat1[0].color = sf::Color::Yellow; plat1[1].color = sf::Color::Yellow; 
        return collision_calc(player_xPos, player_yPos, plat1[0].position.y); break;
    case 6:
        plat1[0].color = sf::Color::Yellow; plat1[1].color = sf::Color::Yellow;
        if (player_xPos > plat1[1].position.x) { return -1; break; }
        else { return collision_calc(player_xPos, player_yPos, plat1[0].position.y); break; }
    case 7:
        plat1[0].color = sf::Color::Red; plat1[1].color = sf::Color::Red;
        return -1; break;
    case 8:
        plat1[0].color = sf::Color::Red; plat1[1].color = sf::Color::Red;
        return -1; break;
    case 9:
        plat1[0].color = sf::Color::Red; plat1[1].color = sf::Color::Red;
        return -1; break;
    case 10:
        plat1[0].color = sf::Color::Red; plat1[1].color = sf::Color::Red;
        return -1; break;
    case 11:
        plat1[0].color = sf::Color::Red; plat1[1].color = sf::Color::Red;
        return -1; break;
    default:
        return 0; break;
    }
}
float Platforms_and_Objects::collision_calc(float player_xPos, float player_yPos, float threashold)
{
    if (player_yPos <= threashold) return line(0, player_xPos);
    else return -1;
}
void Platforms_and_Objects::pointer_null(int leftover)
{
    for (leftover; leftover < sizeof(plat_onScreen_pa) / sizeof(sf::VertexArray); leftover++)
    {
        plat_onScreen_pa[leftover] = NULL;
    }
}

void Platforms_and_Objects::level1()
{
    plat1.setPrimitiveType(sf::Lines); plat1.resize(2); plat_onScreen_pa[0] = &plat1;
	plat1[0].position = sf::Vector2f(260.0f, 180.0f); plat1[0].color = sf::Color::Red;
	plat1[1].position = sf::Vector2f(660.0f, 180.0f); plat1[1].color = sf::Color::Red;

    x_offset_a[0] = 0.f; y_offset_a[0] = plat1[0].position.y;
    dx_a[0] = 0.f; ddx_a[0] = 0.f; dddx_a[0] = 0.f;
}
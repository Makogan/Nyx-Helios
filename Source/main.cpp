//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Main file to start execution of the program
 * 
 * @file main.cpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//========================================================================================
/*                                                                                      *
 *                                  Includes and Macros                                 *
 *                                                                                      */
//========================================================================================
#include "Nyx.hpp"
#include "Helios.hpp"
#include <glm/glm.hpp>

#include "example.hpp"

using namespace std;
using namespace glm;
//########################################################################################


//========================================================================================
/*                                                                                      *
 *                                         Main                                         *
 *                                                                                      */
//========================================================================================

Helios::Mesh *mesh;
Helios::Camera c;
Helios::Shading_Program *v;
void render()
{
    glClearColor(0,0.035,0.035,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update();
    c.load_to_program(v);

    mesh->draw();
}

int main()
{
   /* Nyx::NyxInit(NYX_TOLERANCE_HIGH);
    Nyx::Nyx_Window w = Nyx::Nyx_Window("Example", render, NULL, true);

    w.set_callback(key_callback);
    w.set_callback(cursor_position_callback);
    w.disable_cursor();

    c.setPosition(vec3(0,0,-2));

    Helios::HeliosInit();
    v = new Helios::Shading_Program("Helios-Shaders/Basic-Vertex.glsl", "",
        "", "", "Helios-Shaders/Basic-Fragment.glsl", "");

    v->use();

    mesh = new Helios::Mesh("Assets/dragon.obj");
    Helios::Texture t = Helios::Texture("Assets/tiled_texture.png", GL_TEXTURE_2D);
    t.load_to_program(v, "testing");
    w.start_loop();*/
}
//########################################################################################

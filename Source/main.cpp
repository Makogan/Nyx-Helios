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

using namespace std;
using namespace glm;
//########################################################################################


//========================================================================================
/*                                                                                      *
 *                                         Main                                         *
 *                                                                                      */
//========================================================================================

GLuint tvao;
GLuint tvbo1;
GLuint tvbo2;

Helios::Mesh *mesh;
void render()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mesh->draw();
}
int main()
{
    Nyx::NyxInit(NYX_TOLERANCE_HIGH);
    Nyx::Nyx_Window w = Nyx::Nyx_Window("Example", render, NULL, true);

    Helios::HeliosInit();
    Helios::Shading_Program v = Helios::Shading_Program(
        "Helios-Shaders/Basic-Vertex.glsl", "",
        "", "", "Helios-Shaders/Basic-Fragment.glsl", "");

    v.use();

    mesh = new Helios::Mesh();
    w.start_loop();
}
//########################################################################################

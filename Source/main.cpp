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

using namespace std;
//########################################################################################


//========================================================================================
/*                                                                                      *
 *                                         Main                                         *
 *                                                                                      */
//========================================================================================

void render()
{
    /*glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);*/
}
int main()
{
    Nyx::NyxInit(NYX_TOLERANCE_HIGH);
    Nyx::Nyx_Window w = Nyx::Nyx_Window("Example", render, NULL, true);

    Helios::HeliosInit();
    Helios::Shading_Program v = Helios::Shading_Program("Helios-Shaders/minimum-vertex.glsl", "",
        "", "", "Helios-Shaders/minimum-fragment.glsl", "");

    w.start_loop();
}
//########################################################################################

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

Helios::Mesh *mesh;
Helios::Camera c;
void render()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    c.load();
    //c.rotateH(0.01);
    //c.translate(vec3(0,0,-0.01));
    mesh->draw();
}

bool first = true;
vec2 c_pos;
void static cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width/2, height/2);

    c.rotateH(0.001*(width/2 - xpos));
    c.rotateV(0.001*(height/2 - ypos));
}
#define CAM_SPEED 0.05f
void static key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if(key == GLFW_KEY_F11 && action == GLFW_PRESS)
    {
    	//Get the primary monitor and the monitor attached to the current window
    	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    	GLFWmonitor* monitor = glfwGetWindowMonitor(window);

    	//If no monitor is attached to the window attach the primary monitor
    	//This makes the window full screen
    	if(monitor==NULL)
    		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0,
    			mode->width, mode->height, mode->refreshRate);

    	//If a monitor is attached, detach it and set the dimensions to that of
    	//The primary's monitor resolution. This makes the window windowed
    	else
    		glfwSetWindowMonitor(window, NULL, 0, 0,
    			mode->width, mode->height-1, mode->refreshRate);
    			//subtract 1 to prevent it from going into full screen mode

    	glfwMaximizeWindow(window);
    }

    vec3 hSide = c.getSide();
    if(key == GLFW_KEY_W)
    {
        c.translateForward(CAM_SPEED);
    }
    if(key == GLFW_KEY_S)
    {
        c.translateForward(-CAM_SPEED);
    }
    if(key == GLFW_KEY_A)
    {
        c.translateSideways(-CAM_SPEED);
    }
    if(key == GLFW_KEY_D)
    {
        c.translateSideways(CAM_SPEED);
    }
}
int main()
{
    Nyx::NyxInit(NYX_TOLERANCE_HIGH);
    Nyx::Nyx_Window w = Nyx::Nyx_Window("Example", render, NULL, true);

    glfwSetInputMode(w.getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    w.set_callback(key_callback);
    w.set_callback(cursor_position_callback);

    c.setPosition(vec3(0,0,-2));

    Helios::HeliosInit();
    Helios::Shading_Program v = Helios::Shading_Program(
        "Helios-Shaders/Basic-Vertex.glsl", "",
        "", "", "Helios-Shaders/Basic-Fragment.glsl", "");

    v.use();

    mesh = new Helios::Mesh("Assets/untitled.obj");
    w.start_loop();
}
//########################################################################################

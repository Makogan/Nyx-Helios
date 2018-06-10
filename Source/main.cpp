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
Nyx::Nyx_Keyboard* kbd;

void render()
{
    glClearColor(0,0.5,0.5,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    kbd->updateAllKeys();
    c.load_to_program(v);

    v->use();
    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    mesh->draw();
}
#define CAM_SPEED 0.001f
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width/2, height/2);

    c.rotateH(0.001*(width/2 - xpos));
    c.rotateV(0.001*(height/2 - ypos));
}
void static key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    else if(key == GLFW_KEY_F11 && action == GLFW_PRESS)
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

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0,0, width, height);
    }

    else if(key == GLFW_KEY_F12 && action == GLFW_PRESS)
    	cout << glfwGetVersionString() << endl;
}

int main()
{
    Nyx::NyxInit(NYX_TOLERANCE_HIGH);
    Nyx::Nyx_Window w = Nyx::Nyx_Window("Example", render, NULL, true);

    w.disable_cursor();
    w.set_callback(cursor_position_callback);
    w.set_callback(key_callback);

    c.setPosition(vec3(0,0,0));

    Helios::HeliosInit();
    v = new Helios::Shading_Program("Helios-Shaders/Basic-Vertex.glsl", "",
        "", "", "Helios-Shaders/Basic-Fragment.glsl", "");

    kbd = new Nyx::Nyx_Keyboard(&w);
    kbd->set_w_func([]()->void{c.translateForward(CAM_SPEED);});
    kbd->set_s_func([]()->void{c.translateForward(-CAM_SPEED);});
    kbd->set_d_func([]()->void{c.translateSideways(CAM_SPEED);});
    kbd->set_a_func([]()->void{c.translateSideways(-CAM_SPEED);});
    kbd->set_shift_func([]()->void{c.translate(vec3(0,-1,0)*CAM_SPEED);});
    kbd->set_space_func([]()->void{c.translate(vec3(0,1,0)*CAM_SPEED);});

    mesh = new Helios::Mesh("Assets/dragon.obj");
    Helios::Texture t = Helios::Texture("Assets/tiled_texture.png", GL_TEXTURE_2D);

    w.start_loop();
}
//########################################################################################

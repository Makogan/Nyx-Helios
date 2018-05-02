#include "example.hpp"

#define CAM_SPEED 0.2f

using namespace std;
using namespace glm;

bool E_SHIFT=false, E_SPACE=false, E_W=false, E_S=false, E_A=false, E_D = false;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width/2, height/2);

    c.rotateH(0.001*(width/2 - xpos));
    c.rotateV(0.001*(height/2 - ypos));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

    if(key == GLFW_KEY_W)
    {
        if(action==GLFW_PRESS)
            E_W=true;
        if(action==GLFW_RELEASE)
            E_W=false;
    }
    if(key == GLFW_KEY_S)
    {
        if(action==GLFW_PRESS)
            E_S=true;
        if(action==GLFW_RELEASE)
            E_S=false;
    }
    if(key == GLFW_KEY_A)
    {
        if(action==GLFW_PRESS)
            E_A=true;
        if(action==GLFW_RELEASE)
            E_A=false;
    }
    if(key == GLFW_KEY_D)
    {
        if(action==GLFW_PRESS)
            E_D=true;
        if(action==GLFW_RELEASE)
            E_D=false;
    }
    if(key == GLFW_KEY_SPACE)
    {
        if(action==GLFW_PRESS)
            E_SPACE=true;
        if(action==GLFW_RELEASE)
            E_SPACE=false;
    }
    if(key == GLFW_KEY_LEFT_SHIFT)
    {
        if(action==GLFW_PRESS)
            E_SHIFT=true;
        if(action==GLFW_RELEASE)
            E_SHIFT=false;
    }
}

void update()
{
    if(E_W)
        c.translateForward(CAM_SPEED);
    if(E_S)
        c.translateForward(-CAM_SPEED);
    if(E_A)
        c.translateSideways(-CAM_SPEED);
    if(E_D)
        c.translateSideways(CAM_SPEED);
    if(E_SHIFT)
        c.translate(vec3(0,-1,0)*CAM_SPEED);
    if(E_SPACE)
        c.translate(vec3(0,1,0)*CAM_SPEED);
}
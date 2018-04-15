//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Implementation of a Wrapper class to abstract GLFW Nyx_Windows
 * 
 * @file Nyx-Window.cpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: I N C L U D E   F I L E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
#include "Nyx-Window.hpp"

using namespace std;
// ────────────────────────────────────────────────────────────────────────────────

//
// ────────────────────────────────────────────────────────────── I ──────────
//   :::::: N O N   E X P O S E D : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────
//
//Empty function, used as a place holder to enable default construction of Nyx_Windows
void static empty_func(){}

//Default error callback
void error_callback(int error, const char* description)
{
    cerr << "Error: " << description << endl;
    Nyx::record_log("Error: " + string(description));
}

//Default key callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

    	//If a monitor is attached, detach it and set the dimesnions to that of
    	//The primary's monitor resolution. This makes the window windowed
    	else
    		glfwSetWindowMonitor(window, NULL, 0, 0,
    			mode->width, mode->height-1, mode->refreshRate);
    			//subtract 1 to prevent it from going into full screen mode

    	glfwMaximizeWindow(window);
    }

    else if(key == GLFW_KEY_F12 && action == GLFW_PRESS)
    	cout << glfwGetVersionString() << endl;
}
// ────────────────────────────────────────────────────────────────────────────────

//
// ──────────────────────────────────────────────────────────────── I ──────────
//   :::::: W I N D O W   C L A S S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────
//

//
// ─── STATIC ─────────────────────────────────────────────────────────────────────
//
namespace Nyx{
    
void Nyx_Window::init_glfw()
{
    //Initialize GLFW and check for errors
	if (!glfwInit())
	{
        //If errors occurred record log information and print error message
		cerr<< "Failed to initialize GLFW.\nTerminating program." << endl;
        record_log("GLFW could not be initialized.\n Program was terminated");
        record_log_time("Program ended: ");
        //Terminate program
		exit(EXIT_FAILURE);
	}

    //Record version information onto the log
    record_log("\tGLFW intialized \t\t [✓]");
    int major, minor, rev;
    glfwGetVersion(&major,&minor, &rev);

    string version_num = to_string(major)+"."+to_string(minor)+"."+to_string(rev);
    record_log("\t\tGLFW Version: " + version_num);
}

void Nyx_Window::init_glew()
{
    // Initialize GLEW for cross platform compilation
    glewExperimental = GL_TRUE;
    // Glew sets errors in OpenGL when initialized, 
    // they can be safely discarded however
    if(glewInit()!=GLEW_OK)
    {
        //If errors occurred record log information and print error message
        cerr<< "Failed to initialize GLEW.\nTerminating program." << endl;
        record_log("GLEW was not properly initialized.\n Program was terminated");
        record_log_time("Program ended: ");
        //Terminate program
		exit(EXIT_FAILURE);
    }
    //Discard the errors set by GLEW
    glGetError();

    //Record version information onto the log
    record_log("\tGLEW initialized \t\t [✓]");
    record_log("\t\tGLEW version: " + string((char *)glewGetString(GLEW_VERSION)));
}
// ────────────────────────────────────────────────────────────────────────────────

//
// ─── CONSTRUCTORS ───────────────────────────────────────────────────────────────
//
Nyx_Window::Nyx_Window() : Nyx_Window("", empty_func, NULL, GL_TRUE){}

Nyx_Window::Nyx_Window(string name, void(*w_func)(), GLFWwindow* s_window, bool visible)
{
    //Set the window hints (its properties)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//OpenGL major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);//OpenGL minor version
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//Set Forward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Use GLFW defaults
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);//Make the window decorated
	if(!visible)
	    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);//Make the window visible

    //Get the primiray monitor of the current system
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//Create a GLFW window with the main monitors width, reduced height, 
	//name, on windowed mode, not sharing resources with any context
	window = glfwCreateWindow(mode->width, mode->height-40, 
		name.c_str(), NULL, s_window);

	if (!window)//Check for errors
	{
		cerr<< "Failed to glfwCreatewindow.\nTerminating program." << endl;
        record_log("Could not create a GLFW window.");
        record_log_time("Program ended: ");
		exit(EXIT_FAILURE);
	}

	//Set the current window to be the current OpenGL context
	glfwMakeContextCurrent(window);

    //Set this windows render function
    window_function = w_func;

    Nyx_Window::init_glew();

    set_callback(error_callback);
    set_callback(key_callback);
}
// ────────────────────────────────────────────────────────────────────────────────

//
// ─── MEMBER FUNCTIONS ───────────────────────────────────────────────────────────
//
void Nyx_Window::start_loop()
{
    //Make this window the current context
    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))
    {
        //GLFW update
	    glfwPollEvents();
	    glfwSwapBuffers(window);

        //Call render function
        window_function();
    }
}

void Nyx_Window::set_callback(void(*callback_f)(int, const char*))
{
    glfwSetErrorCallback(callback_f);
}

void Nyx_Window::set_callback(void (*callback_f)(GLFWwindow*, double, double))
{
    glfwSetCursorPosCallback(window, callback_f);
}

void Nyx_Window::set_callback(void (*callback_f)(GLFWwindow*, int, int, int))
{
    glfwSetMouseButtonCallback(window, callback_f);
}
 
void Nyx_Window::set_callback(void (*callback_f)(GLFWwindow*, int, int, int, int))
{
    glfwSetKeyCallback(window, callback_f);
}
}
// ────────────────────────────────────────────────────────────────────────────────

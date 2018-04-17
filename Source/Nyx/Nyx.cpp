//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Implementation of important library functions
 * 
 * @file Nyx.cpp
 * @author Camilo Talero
 * @date 2018-04-15
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: I N C L U D E   F I L E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
#include "Nyx.hpp"
#define NYX_LIB

#ifdef __unix__
#define NYX_OS "Linux"
#endif
#ifdef __APPLE__
#define NYX_OS "Mac OS"
#endif
#ifdef _WIN32
#define NYX_OS "Mac OS"
#endif

using namespace Log;
using namespace std;
// ────────────────────────────────────────────────────────────────────────────────

//
// ────────────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: L I B R A R Y   G L O B A L   V A L U E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────────
//
namespace Nyx{
int NYX_TOLERANCE = NYX_TOLERANCE_LOW;
bool NYX_STARTED = false;

GLint OpenGL_Major = 0;
GLint OpenGL_Minor = 0;
std::string OpenGL_Vendor = "Nyx Not Started";
std::string OpenGL_Renderer = "Nyx Not Started";
std::string OpenGL_Driver = "Nyx Not Started";
// ────────────────────────────────────────────────────────────────────────────────

//
// ────────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: N Y X   I M P L E M E N T A T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────
//
bool init_glfw()
{
    //Initialize GLFW and check for errors
	if (!glfwInit())
	{
        //If errors occurred record log information and print error message
		cerr<< "Failed to initialize GLFW.\nTerminating program." << endl;
        record_log("\tGLFW initialized \t\t[x]");

        if(NYX_TOLERANCE == NYX_TOLERANCE_LOW)
        {
            record_log(string(80,'-'));
		    exit(EXIT_FAILURE);
        }
        
        return false;
	}

    //Record version information onto the log
    record_log("\tGLFW intialized \t\t [✓]");
    int major, minor, rev;
    glfwGetVersion(&major,&minor, &rev);

    string version_num = to_string(major)+"."+to_string(minor)+"."+to_string(rev);
    record_log("\t\tGLFW Version: " + version_num);

    return true;
}

bool init_glew()
{
    // Initialize GLEW for cross platform compilation
    glewExperimental = GL_TRUE;
    // Glew sets errors in OpenGL when initialized, 
    // they can be safely discarded however
    if(glewInit()!=GLEW_OK)
    {
        //If errors occurred record log information and print error message
        cerr<< "Failed to initialize GLEW.\nTerminating program." << endl;
        record_log("\tGLEW initialized \t\t[x]");

        if(NYX_TOLERANCE == NYX_TOLERANCE_LOW)
            //Terminate program
		    exit(EXIT_FAILURE);
        
        return false;
    }
    //Discard the errors set by GLEW
    glGetError();

    //Record version information onto the log
    record_log("\tGLEW initialized \t\t [✓]");
    record_log("\t\tGLEW version: " + string((char *)glewGetString(GLEW_VERSION)));
    return true;
}

void static inline record_end()
{
    Log::record_log_time("Program ended: ");
}

bool NyxInit(int level)
{
    //Set the tolerance level. 
    //NYX_TOELRANCE_HIGH for simply recording problems
    //NYX_TOLERANCE_LOW to terminate execution if a problem is found
    NYX_TOLERANCE = level;
    NYX_STARTED = true;

    //Set the log file used for runtime recording
    Log::set_log_file("log/.log");
    //Begin recording
    Log::record_log(std::string(80, '='));//Separator to improve readability
    Log::record_log_time("Nyx started: ");
    Log::record_log("On OS: " NYX_OS);
    Log::record_log("Library Linking and initialization checks for Nyx:\n");

    bool success_value = Nyx::init_glfw(); //Attempt to initialize GLFW
    if(success_value==true)
    {
        //Create an invisible dummy window to test GLFW and get some OpenGL information
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        GLFWwindow* window = glfwCreateWindow(1, 1, "", NULL, NULL);
        //Check the window was initialized properly. GLFW check
        if(!window)
        {
            cerr << "Nyx GLFW check failed!" << endl;
            record_log("\tError in initial GLFW check");
            record_log("\tNyx initilized \t\t\t [x]");
            if(NYX_TOLERANCE==NYX_TOLERANCE_LOW)
            {
                Log::record_log(std::string(80, '='));//Separator to improve readability
                exit(EXIT_FAILURE);
            }
        }
        glfwMakeContextCurrent(window);

        init_glew();//Initialize GLEW
        //Set Nyx OpenGL info
        glGetIntegerv(GL_MAJOR_VERSION, &OpenGL_Major);
        glGetIntegerv(GL_MINOR_VERSION, &OpenGL_Minor);
        OpenGL_Vendor = (char *)glGetString(GL_VENDOR);
        OpenGL_Renderer = (char *)glGetString(GL_RENDERER);
        OpenGL_Driver = (char *)glGetString(GL_VERSION);

        glfwDestroyWindow(window);//destroy the window since we don't need it anymore
    }

    if(OpenGL_Major < 3)
        Log::record_log("\tModern OpenGL: \t\t[x]"
            "\n\t\tLegacy OpenGL. Many features may not work!");
    else
        Log::record_log("\tModern OpenGL: \t\t\t [✓]");
    Log::record_log("\t\tVersion: "+to_string(OpenGL_Major)+"."+to_string(OpenGL_Minor)+".0");
    Log::record_log("\t\tFrom Vendor:\n\t\t\t" + OpenGL_Vendor);
    Log::record_log("\t\tRender Device:\n\t\t\t" + OpenGL_Renderer);
    Log::record_log("\t\tDriver Version:\n\t\t\t" + OpenGL_Driver);

    if(success_value)
        record_log("\tNyx initilized \t\t\t [✓]\n\t\tNyx version: " NYX_VERSION);
    else
        record_log("\tNyx initilized \t\t\t [x]");

    Log::record_log(std::string(80, '='));//Separator to improve readability

    //Call a function to record the exit time upon program termination
    atexit(record_end);
    return success_value;
}

}// Close Nyx namespace
// ────────────────────────────────────────────────────────────────────────────────

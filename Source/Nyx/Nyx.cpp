//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Implementation of important library functions
 * 
 * @file Nyx.cpp
 * @author Camilo Talero
 * @date 2018-04-15
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================

#include "Nyx.hpp" 

//Set the operating system string
#ifdef __unix__
#define NYX_OS "Linux" 
#endif
#ifdef __APPLE__
#define NYX_OS "Mac OS"
#endif
#ifdef _WIN32
#define NYX_OS "Windows"
#endif

#define N_ALIGN 50      //Level of alignment for messages
#define N_H_CHAR '-'    //Character for horizontal line
#define N_V_CHAR '|'    //Character for vertical line

using namespace Log;
using namespace std;
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                               Hidden Library Variables                               *
 *                                                                                      */
//========================================================================================
namespace Nyx{
///@{
/**
 * @name Hidden Nyx Global Values
 * @brief Values used by the library that should not be exposed
 *
 * These values are global to the library and should not be accessed by other programs
 *
*/
int NYX_TOLERANCE = NYX_TOLERANCE_LOW;  // Error tolerance of the library
bool NYX_STARTED = false;               // Whether the library has been initialized

GLint OpenGL_Major = 0;                             // The OpenGL Major version
GLint OpenGL_Minor = 0;                             // The OpenGL Minor version
std::string OpenGL_Vendor = "Nyx Not Started";      // Vendor provifing OpenGL
std::string OpenGL_Renderer = "Nyx Not Started";    // Graphics card
std::string OpenGL_Driver = "Nyx Not Started";      // Driver version
///@}
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                             Nyx Function Implementations                             *
 *                                                                                      */
//========================================================================================

//Initialize GLFW
bool init_glfw()
{
    //Initialize GLFW and check for errors
	if (!glfwInit())
	{
        //If errors occurred record log information and print error message
		cerr<< "Failed to initialize GLFW.\nTerminating program." << endl;
        record_log("\tGLFW initialized", "[x]", N_ALIGN, N_H_CHAR);

        if(NYX_TOLERANCE == NYX_TOLERANCE_LOW)
        {
            record_log(string(80,N_H_CHAR));
		    exit(EXIT_FAILURE);
        }

        return false;
	}

    //Record version information onto the log
    record_log("\tGLFW intialized", "[✓]", N_ALIGN, N_H_CHAR);
    int major, minor, rev;
    glfwGetVersion(&major,&minor, &rev);

    string version_num = to_string(major)+"."+to_string(minor)+"."+to_string(rev);
    record_log("\t\tGLFW Version: " + version_num, "|", N_ALIGN-2);

    return true;
}

//Initialize GLEW
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
        record_log("\tGLEW initialized", "[x]", N_ALIGN, N_H_CHAR);

        if(NYX_TOLERANCE == NYX_TOLERANCE_LOW)
            //Terminate program
		    exit(EXIT_FAILURE);
        
        return false;
    }
    //Discard the errors set by GLEW
    glGetError();

    //Record version information onto the log
    record_log("\tGLEW initialized", "[✓]", N_ALIGN, N_H_CHAR);
    record_log("\t\tGLEW version: " + string((char *)glewGetString(GLEW_VERSION)), "|", N_ALIGN-2);
    return true;
}

//Helping function to record the time when the program terminated
void static inline record_end()
{
    Log::record_log_time("Program ended: ");
}

//Initialize the Nyx library. Should be called before creating a Nyx Window
bool NyxInit(int level)
{
    //Set the tolerance level.
    //NYX_TOLERANCE_HIGH for simply recording problems
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
            record_log("\tNyx initialized", "[x]", N_ALIGN, N_H_CHAR);
            if(NYX_TOLERANCE==NYX_TOLERANCE_LOW)
            {
                Log::record_log(std::string(80, '='));//Separator to improve readability
                exit(EXIT_FAILURE);
            }
        }
        glfwMakeContextCurrent(window);

        init_glew();//Initialize GLEW
        //Set OpenGL Global info
        glGetIntegerv(GL_MAJOR_VERSION, &OpenGL_Major);
        glGetIntegerv(GL_MINOR_VERSION, &OpenGL_Minor);
        OpenGL_Vendor = (char *)glGetString(GL_VENDOR);
        OpenGL_Renderer = (char *)glGetString(GL_RENDERER);
        OpenGL_Driver = (char *)glGetString(GL_VERSION);

        glfwDestroyWindow(window);//destroy the window since we don't need it anymore
    }

    //See if we can find a modern version of OpenGL
    if(OpenGL_Major < 3)
    {
        Log::record_log("\tModern OpenGL", "[x]",N_ALIGN, N_H_CHAR);
        Log::record_log("\n\t\tLegacy OpenGL. Many features may not work!");
    }
    else
    {
        Log::record_log("\tModern OpenGL", "[✓]", N_ALIGN, N_H_CHAR);
    }

    //Record opengl information
    Log::record_log("\t\tVersion: "+to_string(OpenGL_Major)+"."+to_string(OpenGL_Minor)+".0", "|", N_ALIGN-2);
    Log::record_log("\t\tFrom Vendor: " + OpenGL_Vendor, "|", N_ALIGN-2);
    Log::record_log("\t\tRender Device: " + OpenGL_Renderer, "|", N_ALIGN-2);
    Log::record_log("\t\tDriver Version: " + OpenGL_Driver, "|", N_ALIGN-2);

    //Record the Nyx version
    if(success_value)
    {
        Log::record_log("\tNyx initialized", "[✓]", N_ALIGN, N_H_CHAR);
        Log::record_log("\t\tNyx version: " NYX_VERSION, "|", N_ALIGN-2);
    }
    else
    {
        Log::record_log("\tNyx initialized","[x]",N_ALIGN, N_H_CHAR);
    }

    Log::record_log(std::string(80, '='));//Separator to improve readability

    //Call a function to record the exit time upon program termination
    atexit(record_end);
    return success_value;
}
}// Close Nyx namespace
//########################################################################################

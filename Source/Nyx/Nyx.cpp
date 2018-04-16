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

using namespace Log;
using namespace std;

int NYX_TOLERANCE = NYX_TOLERANCE_LOW;
bool NYX_STARTED = false;
// ────────────────────────────────────────────────────────────────────────────────

//
// ────────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: N Y X   I M P L E M E N T A T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────
//
namespace Nyx{

bool init_glfw()
{
    //Initialize GLFW and check for errors
	if (!glfwInit())
	{
        //If errors occurred record log information and print error message
		cerr<< "Failed to initialize GLFW.\nTerminating program." << endl;
        record_log("\tGLFW initialized \t\t[x]");

        if(NYX_TOLERANCE == NYX_TOLERANCE_LOW)
            //Terminate program
		    exit(EXIT_FAILURE);
        
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

void static inline record_end()
{
    Log::record_log_time("Program ended: ");
}

bool NyxInit(int level)
{
    NYX_TOLERANCE = level;
    NYX_STARTED = true;

    Log::set_log_file("log/.log");

    Log::record_log(std::string(80, '='));
    Log::record_log_time("Nyx started: ");
    Log::record_log("Library Linking and initialization checks for Nyx:\n");

    bool success_value = Nyx::init_glfw();

    if(success_value==true)
        record_log("\tNyx initilized \t\t\t [✓]");
    else
        record_log("\tNyx initilized \t\t\t [x]");

    Log::record_log("\t\tNyx version: " + std::string(NYX_VERSION));

    atexit(record_end);
    Log::record_log(std::string(80, '='));
    return success_value;
}

}
// ────────────────────────────────────────────────────────────────────────────────

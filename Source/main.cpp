//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Main file to start execution of the program
 * 
 * @file main.cpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//
// ─── INCLUDES AND MACROS ────────────────────────────────────────────────────────
//
#include "Nyx.hpp"

using namespace std;
// ────────────────────────────────────────────────────────────────────────────────


//
// ──────────────────────────────────────────────── I ──────────
//   :::::: M A I N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────
//

int main()
{
    Nyx::set_log_file("log/.log");
    Nyx::wipe_log();

    Nyx::record_log_time("Program started: ");
    Nyx::record_log("Nyx version: " + string(NYX_VERSION));
    Nyx::record_log("Library Linking and initialization checks:\n");

    Nyx::Nyx_Window::init_glfw();
    Nyx::Nyx_Window w = Nyx::Nyx_Window();

    Nyx::record_log("\nOpenGL Version and driver: " + 
        string((char *)glGetString(GL_VERSION)));

    w.start_loop();

    Nyx::record_log_time("Program ended: ");
}
// ────────────────────────────────────────────────────────────────────────────────

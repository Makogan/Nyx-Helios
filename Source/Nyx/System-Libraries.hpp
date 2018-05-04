//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Header defining all system libraries needed by at least one Nyx file
 * 
 * This header structure facilitates library inclusion through multiple files
 * 
 * @file System-Libraries.hpp
 * @author Camilo Talero
 * @date 2018-04-15
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                   Include Libraries                                  *
 *                                                                                      */
//========================================================================================
#pragma message("Including Syslib.")
#ifndef SYSTEMLIBS_HPP_INCLUDED
#define SYSTEMLIBS_HPP_INCLUDED

//OpenGL Libraries
#ifndef DOXYGEN_OMIT
#define GLEW_DYNAMIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//IO libraries
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <string>

//Time handling libraries
#include <chrono>
#include <ctime>

//External helpers
#include "log.hpp"
//########################################################################################
#else
#pragma message("SYSLIB included again.")
#endif

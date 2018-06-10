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

#pragma once

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






/**
 * @brief Enumerators defining how much nyx tolerates errors
 * 
 * NYX_TOLERANCE_HIGH will allow errors to occur and continue execution
 * NYX_TOLERANCE_LOW  will terminate the program upon encountering an error
 * 
*/
enum NYX_TOLERANCE_LEVEL {NYX_TOLERANCE_HIGH, NYX_TOLERANCE_LOW};

namespace Nyx{
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                     Nyx Functions                                    *
 *                                                                                      */
//========================================================================================
/**
 * @brief Function used to initialize GLEW  
 * 
 * This is called mainly by NyxInit() and by the Nyx Window constructors. It initializes
 * GLEW and checks for errors
 * 
 * @return true If GLEW was successfully initialize
 * @return false If an error occurs
*/
bool init_glew();
}//Nyx namespace closing bracket
//########################################################################################

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Header for the Nyx library. Includes all global values of the library.
 * 
 * @file Nyx.hpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
#include <string>

//Time handling libraries
#include <chrono>
#include <ctime>

//External helpers
#include "log.hpp"

//Nyx headers
#include "Nyx-Window.hpp"
#include "Nyx-Input.hpp"
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                  Library Information                                 *
 *                                                                                      */
//========================================================================================

/**
 * @brief Macro defining the current Nyx version 
 * 
*/
#define NYX_VERSION "0.0.1"
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
/**
 * @brief Initializes the Nyx library. 
 * 
 * Should be once at the beginning of main, before any Nyx Window is created.
 * 
 * @param level The tolerance level for errors. NYX_TOLERANCE_LOW to terminate program 
 *              when errors occur. 
 *              NYX_TOLERANCE_HIGH to continue execution if an error happens
 * @return true If Nyx was successfully initialized
 * @return false If an error occurred
*/
bool NyxInit(int level);
}//close namespace
//########################################################################################


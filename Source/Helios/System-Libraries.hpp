//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Header defining all system libraries needed by at least one Helios file
 *
 * This header structure facilitates Library inclusion through multiple files
 *
 * @file System-Libraries.hpp
 * @author Camilo Talero
 * @date 2018-04-15
 *                                                                                      */
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

//Data structures
#include <vector>

//IO libraries
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>

//Time handling libraries
#include <chrono>
#include <ctime>

//Math Libraries
#include <algorithm>

//External helpers
#include "log.hpp"
//########################################################################################

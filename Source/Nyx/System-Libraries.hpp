/**
 * @brief Header defining all system libraries needed by at least one Nyx file
 * 
 * This header structure facilitates ;ibnrary inclusion through multiple files
 * 
 * @file System-Libraries.hpp
 * @author Camilo Talero
 * @date 2018-04-15
*/

//
// ────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: I N C L U D E   L I B R A R I E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────
//
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
// ────────────────────────────────────────────────────────────────────────────────

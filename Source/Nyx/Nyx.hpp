//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Header for the Nyx library. Includes all global values of the library.
 * 
 * @file Nyx.hpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

//Nyx headers
#include "Nyx-Window.hpp"
// ────────────────────────────────────────────────────────────────────────────────

//
// ────────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: L I B R A R Y   I N F O R M A T I O N : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────
//
#define NYX_VERSION "0.0.1"

enum {NYX_TOLERANCE_HIGH, NYX_TOLERANCE_LOW};

namespace Nyx{
extern int NYX_TOLERANCE;
extern bool NYX_STARTED;

#ifdef NYX_LIB
extern int OpenGL_Major;
extern int OpenGL_Minor;
extern std::string OpenGL_Vendor;
extern std::string OpenGL_Renderer;
#endif
// ────────────────────────────────────────────────────────────────────────────────

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: N Y X   F U N C T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
bool init_glew();
bool NyxInit(int level);
}//close namespace
// ────────────────────────────────────────────────────────────────────────────────


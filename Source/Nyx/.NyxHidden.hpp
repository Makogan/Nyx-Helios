//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief File containing elements to be used only internally by Nyx
 * 
 * What is in this file should not be exposed to foreign programs
 * 
 * @file .NyxHidden.hpp
 * @author Camilo Talero
 * @date 2018-04-17
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                  Macros and Globals                                  *
 *                                                                                      */
//========================================================================================

#pragma once

#include <string>

namespace Nyx{
extern int NYX_TOLERANCE; //The tolerance level of the library 
extern bool NYX_STARTED;  //Whether Nyx has been initialized 

extern int OpenGL_Major;            //OpenGL Major version 
extern int OpenGL_Minor;            //OpenGL minor version 
extern std::string OpenGL_Vendor;   //The vendor providing the OpenGL implementation 
extern std::string OpenGL_Renderer; //The hardware being used to render 

}//CLose Nyx namespace
//########################################################################################
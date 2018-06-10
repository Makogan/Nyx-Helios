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

//External helpers
#include "log.hpp"

//Nyx headers
#include "Nyx-Window.hpp"
#include "Nyx-Peripherals.hpp"
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

namespace Nyx{
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


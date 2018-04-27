//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Header declaration for the Helios Library
 * 
 * @file Helios.hpp
 * @author Camilo Talero
 * @date 2018-04-15
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================

#pragma once

//Helios headers
#include "Helios-Wrappers.hpp"
namespace Helios{
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                 Function Declarations                                *
 *                                                                                      */
//========================================================================================

//──── Initialization ────────────────────────────────────────────────────────────────────

/**
 * @brief Initialize the Helios library, should be called before using any Helios class or
 * function
 *
 * @return true Upon successful initialization
 * @return false Upon encountering an error
*/
bool HeliosInit();

}//Helios namespace closing bracket
//########################################################################################
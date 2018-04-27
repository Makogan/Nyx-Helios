//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Implementation of major functions of the Helios library
 *
 * @file Helios.cpp
 * @author Camilo Talero
 * @date 2018-04-19
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include files                                    *
 *                                                                                      */
//========================================================================================

#include "Helios.hpp"
#include "System-Libraries.hpp"

using namespace std;
namespace Helios {
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                            Helios Functions Implementations                          *
 *                                                                                      */
//========================================================================================

//Initialize helios
bool HeliosInit()
{
    //Enable debugging messages
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback((GLDEBUGPROC)Helios::errorCallback, NULL);
    /*glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
        GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, false);*/

    return true;
}

}//Helios namespace closing bracket
//########################################################################################
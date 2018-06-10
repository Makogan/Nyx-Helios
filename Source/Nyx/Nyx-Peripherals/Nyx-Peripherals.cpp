//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Implementation of the Peripheral wrapping classes
 * 
 * @file Nyx-Peripherals.cpp
 * @author Camilo Talero
 * @date 2018-05-02
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================

#include "Nyx-Peripherals.hpp"
namespace Nyx{
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                  Nyx Keyboard Class                                  *
 *                                                                                      */
//========================================================================================

Nyx_Keyboard::Nyx_Keyboard(Nyx_Window *w)
{
    window = w->getWindowPtr();

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Nyx_Keyboard::updateAllKeys()
{
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
        w_func();
    
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
        s_func();
    
    if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
        a_func();

    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
        d_func();
    
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
        shift_func();

    if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS)
        space_func();
}
}//CLose Nyx namespace
//########################################################################################
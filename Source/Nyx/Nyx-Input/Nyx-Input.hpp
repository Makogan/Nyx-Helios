//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Header declaration of classes to wrap GLFW input calls
 *
 * @file Nyx-Input.hpp
 * @author Camilo Talero
 * @date 2018-05-02
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================
#pragma message("Including Input.")
#ifndef NXYINPUT_H
#define NXYINPUT_H


#include "Nyx-Window.hpp"
namespace Nyx{
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                    Keyboard Class                                    *
 *                                                                                      */
//========================================================================================

class Nyx_Keyboard
{
    private:
        GLFWwindow* window;

      /*  void(*w_func)();
        void(*a_func)();
        void(*s_func)();
        void(*d_func)();
        void(*shift_func)();
        void(*space_func)();*/
        Nyx_Window w;

    public:
        //Nyx_Keyboard(Nyx_Window w);

       /* void inline set_w_func(void(*f)()){w_func = f;}
        void inline set_a_func(void(*f)()){a_func = f;}
        void inline set_s_func(void(*f)()){s_func = f;}
        void inline set_d_func(void(*f)()){d_func = f;}
        void inline set_shift_func(void(*f)()){shift_func = f;}
        void inline set_space_func(void(*f)()){space_func = f;}

        void updateAllKeys();*/

};
};//Close Nyx namespace
//########################################################################################
#else
#pragma message("Input included again.")
#endif

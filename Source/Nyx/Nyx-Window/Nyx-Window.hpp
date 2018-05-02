//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Declaration of wrapper classes and methods to abstract GLFW Nyx_Windows
 * 
 * @file Nyx-Window.hpp
 * @author Camilo Talero
 * @date 2018-04-14
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//========================================================================================
/*                                                                                      *
 * Include Files                                                                        *
 *                                                                                      */
//========================================================================================


#pragma once

#include "Nyx/System-Libraries.hpp"

enum Nyx_Enum{NYX_KEY_CALLBACK, NYX_CURSOR_POS_CALLBACK, NYX_CURSOR_BUT_CALLBACK};
//########################################################################################

//========================================================================================
/*                                                                                      *
 * Nyx Window Class                                                                     *
 *                                                                                      */
//========================================================================================


namespace Nyx{

/**
 * @ingroup Nyx
 * 
 * @brief A class to Wrap GLFW windows and OpenGL context creation
 * 
*/
class Nyx_Window
{       
//──── Class Members ─────────────────────────────────────────────────────────────────────

    private:
        GLFWwindow* window;         //!< Pointer to the GLFW Nyx_Window we are wrapping
        void (*window_function)();  //!< Subroutine to be called during Nyx_Window loop
        std::string window_name;    //!< Name of the window (displayed at the top)

    public:

//──── Constructors and Destructors ──────────────────────────────────────────────────────

        //TODO: impelment a destructor
        /**
         * @brief Get the GLFWwindow pointer of the current window
         *
         * @return GLFWwindow* The pointer to the GLFW window
        */
        GLFWwindow* getWindowPtr(){return window;}
        /**
         * @brief Construct a new Nyx_Window object.
         * 
        */
        Nyx_Window();                              

        /**
         * @brief Construct a new Nyx_Window object
         * 
         * @param name The display name of the Nyx_Window. Shown at the top when running
         * program
         * @param f Function pointer to a method that will be run on every frame on the
         * current window. This is the main render method that should call all relevant 
         * drawing functions
         * @param window A window pointer with which to share context information 
         * @param visible Whether the window should be visible or not (Invisible 
         * windows are useful for multi threading)
        */
        Nyx_Window(std::string name, void(*f)(), GLFWwindow* window, bool visible);

//──── Class methods ─────────────────────────────────────────────────────────────────────

        /**
         * @brief Start the infinite render loop of the current Nyx_Window. This method 
         * implicitly calls the function defined during construction on each frame
         * 
        */
        void start_loop();     

        /**
         * @name Callback Setters
         * @brief Set a glfw callback function identified by signature
         * 
         * Each of these functions will call the appropriate glfw set callback function.
         * The functions are identified by signature according to glfw's documentation:
         * http://www.glfw.org/documentation.html
         * 
         * @param callback_f the function pointer to be associated to a glfw callback
        */
        ///@{
        //* error callback */
        void set_callback(void (*callback_f)(int, const char*)); 
        //* cursor position callback */
        void set_callback(void (*callback_f)(GLFWwindow*, double, double));
        //* cursor button callback */
        void set_callback(void (*callback_f)(GLFWwindow*, int, int, int));
        //* key callback */
        void set_callback(void (*callback_f)(GLFWwindow*, int, int, int, int));
        //* window size callback */
        void set_callback(void (*callback_f)(GLFWwindow*, int, int));
        ///@}

        /**
         * @brief Disable cursors in the window
         * 
        */
        void inline disable_cursor()
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
};
}//Nyx namespace closing bracket
//########################################################################################

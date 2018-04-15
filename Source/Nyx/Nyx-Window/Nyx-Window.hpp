//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Declaration of wrapper classes and methods to abstract GLFW Nyx_Windows
 * 
 * @file Nyx-Window.hpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: I N C L U D E   F I L E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
#pragma once

#include "Nyx.hpp"
#include "log.hpp"
// ────────────────────────────────────────────────────────────────────────────────

//
// ──────────────────────────────────────────────────────────────── I ──────────
//   :::::: W I N D O W   C L A S S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────
//
namespace Nyx{

class Nyx_Window
{
public:
//
// ─── STATIC METHODS ─────────────────────────────────────────────────────────────
//
    /**
     * @brief Initialize the GLFW library
     * 
    */
    void static init_glfw();    
    /**
     * @brief Initialize the GLEW library
     * 
    */
    void static init_glew();    
// ────────────────────────────────────────────────────────────────────────────────

//
// ─── CLASS MEMBERS ──────────────────────────────────────────────────────────────
//
    GLFWwindow* window;         //!< Pointer to the GLFW Nyx_Window we are wrapping
    void (*window_function)();  //!< Subroutine to be called during Nyx_Window loop
// ────────────────────────────────────────────────────────────────────────────────

//
// ─── CONSTRUCTORS AND DESTRUCTORS ───────────────────────────────────────────────
//
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
    //~Nyx_Window();
// ────────────────────────────────────────────────────────────────────────────────

//
// ─── CLASS MEHTODS ──────────────────────────────────────────────────────────────
//
    /**
     * @brief Start the infinte render loop of the current Nyx_Window. This method 
     * implicitly calls the function defined during construction on each frame
     * 
    */
    void start_loop();     

    /**
     * @name Set Callback member functions
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
    ///@}
};
}
// ────────────────────────────────────────────────────────────────────────────────

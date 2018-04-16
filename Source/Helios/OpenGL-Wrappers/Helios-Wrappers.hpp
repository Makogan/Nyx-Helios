//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Header declaration of the OpenGL wrapping classes of the Helios library
 * 
 * @file Helios-wrappers.hpp
 * @author Camilo Talero
 * @date 2018-04-15
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: I N C L U D E   F I L E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
#pragma once

#include "Helios/System-Libraries.hpp"
// ────────────────────────────────────────────────────────────────────────────────

//
// ──────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: C L A S S   D E C L A R A T I O N S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────
//
namespace Helios{

/**
 * @ingroup Helios
 * 
 * @brief Class to wrap GLSL shaders.
 * 
*/
class Shader
{
    private:
        GLuint shaderId;
        GLenum type;

        bool check_file(std::string file_path);
    
    public:

        Shader(std::string file_path);
};

}
// ────────────────────────────────────────────────────────────────────────────────


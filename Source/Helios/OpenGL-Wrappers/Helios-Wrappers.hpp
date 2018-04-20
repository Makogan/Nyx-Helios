//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Header declaration of the OpenGL wrapping classes of the Helios library
 * 
 * @file Helios-wrappers.hpp
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

#include "Helios/System-Libraries.hpp"
#include "Debuging.hpp"
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                  Class Declarations                                  *
 *                                                                                      */
//========================================================================================
namespace Helios{
/**
 * @ingroup Helios
 *
 * @brief Class to wrap GLSL shaders.
 *
*/
class Shader
{
//──── Private Members ───────────────────────────────────────────────────────────────────

    private:
        GLuint shaderID; //!< The OpenGL generated identifier
        GLenum type;    //!< The shader type (e.g GL_VERTEX_SHADER)

        /**
         * @brief Help initialize a shader by first error checking a file
         *
         * @param file_path Path to the shader source file
         * @return true If file was successfully found
         * @return false If file was nto found or did not contain the shader type in
         *         its name
        */
        bool check_file(std::string file_path);

    public:

//──── Constructors and Destructors ──────────────────────────────────────────────────────

        /**
         * @brief Construct a new Shader object
         *
         * The valid shader names are anything that contains on of the following
         * substrings (not case sensitive):
         *
         * - Vertex
         * - Tessc
         * - Tesse
         * - Geometry
         * - Fragment
         * - Compute
         *
         * @param file_path Path to the shader source file (shader source file must
         * contain it's shader type in it's name)
        */
        Shader(std::string file_path);

//──── Getters and Setters ───────────────────────────────────────────────────────────────

        ///@{
        /**
         * @brief Get the associated variable
         *
        */
        GLuint getShaderID();
        GLenum getType();
        ///@}
};

/**
 * @brief Class to wrap OpenGL shading programs
 *
*/
class Shading_Program
{
//──── Private Members ───────────────────────────────────────────────────────────────────

    private:
        GLuint programID;        //!< OpenGL generated identifier
        Shader* vertex = NULL;  //!< Vertex shader
        Shader* tessc = NULL;   //!< Tessellation control shader
        Shader* tesse = NULL;   //!< Tessellation evaluation shader
        Shader* geometry = NULL;//!< Geometry shader
        Shader* fragment = NULL;//!< Fragment shader
        Shader* compute = NULL; //!< Compute shader

        /**
         * @brief Compile and attach the shaders to the current program
         * 
        */
        void compileShaders(std::string, std::string, std::string,
            std::string, std::string, std::string);

    public:

//──── Constructors and Destructors ──────────────────────────────────────────────────────

        /**
         * @brief Construct a new Shading_Program object
         *
         * @param vShader Pointer to the path of the source file of a vertex shader or
         *        NULL
         * @param tcShader Pointer to the path of the source file of a tessellation
         *        control shader or NULL
         * @param teShader Pointer to the path of the source file of a tessellation
         *        evaluation shader or NULL
         * @param gShader Pointer to the path of the source file of a geometry shader or
         *        NULL
         * @param fShader Pointer to the path of the source file of a fragment shader or
         *        NULL
         * @param cShader Pointer to the path of the source file of a compute shader or
         *        NULL
        */
        Shading_Program(std::string vShader, std::string tcShader, std::string teShader,
            std::string gShader, std::string fShader, std::string cShader);
};
}//Close helios namespace
//########################################################################################


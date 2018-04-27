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
#include "Debugging.hpp"
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                  Class Declarations                                  *
 *                                                                                      */
//========================================================================================
namespace Helios{

//TODO: implement the rest of the Mesh class
/**
 * @brief Class to wrap a generic 3D mesh
 * 
*/
class Mesh
{

//──── Private Members ───────────────────────────────────────────────────────────────────

    private:

        GLuint VAO;         //!< Vertex array object
        GLuint buffers[4];  //!< VBO identifiers

        std::vector<glm::vec3> vertices;    //!< Array of vertices of the mesh
        std::vector<glm::vec3> normals;     //!< Array of normals of the mesh
        std::vector<glm::vec2> uvs;         //!< Array of texture coordinates of the mesh
        std::vector<uint> indices;          //!< Array of indices for per element indexing

    public:

//──── Constructors and Destructors ──────────────────────────────────────────────────────

        /**
         * @brief Construct a new Mesh object
         *
        */
        Mesh();
        /**
         * @brief Destroy the Mesh object
         *
        */
        ~Mesh();

//──── GPU related methods ───────────────────────────────────────────────────────────────

        void draw();
};

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

        /**
         * @brief Destroy the Shader object
         *
        */
        ~Shader();

//──── Getters and Setters ───────────────────────────────────────────────────────────────

        ///@{
        /**
         * @brief Get the associated variable
         *
        */
        GLuint inline getShaderID(){return shaderID;}
        GLenum inline getType(){return type;}
        ///@}

//──── Other Functions ───────────────────────────────────────────────────────────────────

        /**
         * @brief Attach the shader to a program
         *
         * @param program The program we are attaching to's ID
        */
        void inline attachTo(GLuint program){glAttachShader(program, shaderID);}
        /**
         * @brief Detach The shader from a program
         *
         * @param program The program we are detaching from's ID
        */
        void inline detachFrom(GLuint program){glDetachShader(program, shaderID);}
};

/**
 * @brief Class to wrap OpenGL shading programs
 *
*/
class Shading_Program
{
//──── Private Members ───────────────────────────────────────────────────────────────────

    private:
        GLuint programID; //!< OpenGL generated identifier

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

        /**
         * @brief Destroy the Shading_Program object
         * 
        */
        ~Shading_Program();

//──── Setters and Getters ───────────────────────────────────────────────────────────────

        GLuint inline getProgramID(){return programID;}

//──── Other Functions ───────────────────────────────────────────────────────────────────

        /**
         * @brief use the current program
         *
        */
        void inline use(){glUseProgram(programID);}
};
}//Close helios namespace
//########################################################################################


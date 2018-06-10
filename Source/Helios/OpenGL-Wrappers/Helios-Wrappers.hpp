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

namespace Helios{
//========================================================================================
/*                                                                                      *
 *                                 Forward Declarations                                 *
 *                                                                                      */
//========================================================================================

class Texture;
class Mesh;
class Shading_Program;
class Shader;

//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                  Class Declarations                                  *
 *                                                                                      */
//========================================================================================
/**
 * @brief Wrapper class for textures
 *
*/
class Texture
{
//──── Private Members ───────────────────────────────────────────────────────────────────

    protected:
        GLuint textureID;   //!< OpenGL name of the texture
        GLuint target;      //!< Target of the texture (e.g GL_TEXTURE_2D)

        int color_format;   //!< The color format of the texture (e.g GL_RGBA)
        int width;          //!< width of the texture
        int height;         //!< height of the texture

    public:

//──── Constructors and Destructors ──────────────────────────────────────────────────────

        Texture(){}
        /**
         * @brief Construct a new Texture object
         *
         * @param file_path Path to the texture file
         * @param target The OpenGL target texture
        */
        Texture(std::string file_path, GLuint target);
        /**
         * @brief Destroy the Texture object
         *
        */
        ~Texture();

//──── Other Methods ─────────────────────────────────────────────────────────────────────

        /**
         * @brief Load this textures information into a uniform in the selected program
         *
         * @param program The program into which the texture will be loaded
         * @param uniform The label of the uniform in the shader
         * @param texture_unit The texture unit to which to bind the texture
        */
        void load_to_program(Shading_Program *program, std::string uniform,
            GLuint texture_unit);
        /**
         * @brief Draw this image as is to the screen
         *
        */
        void inline draw(){glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);}
};

/**
 * @brief Wrapper class for a 3D image
 * 
*/
class Image3D : public Texture
{

//──── Private Members ───────────────────────────────────────────────────────────────────

    protected:
        int depth; //<! Depth of the 3D image (width and heigh inherited from Texture)

//──── Public Members ────────────────────────────────────────────────────────────────────

    public:
        /**
         * @brief Construct a new 3D Image
         *
         * @param width Width of texture
         * @param height Height of texture
         * @param depth Depth of texture
        */
        Image3D(int width, int height, int depth);
        /**
         * @brief Load the image to a named uniform in the shading program
         *
         * @param program program to which to load the image
         * @param uniform label of the uniform to which to attach the image
         * @param texture_unit the texture unit in the context to which to bind the
         *        texture
        */
        void inline load_to_program(Shading_Program *program, std::string uniform,
            GLuint texture_unit)
        {Texture::load_to_program(program, uniform, texture_unit);}
        /**
         * @brief Load the image to the shading program
         *
         * @param program Shading program to which to load the texture
         * @param image_unit Image unit to which to bind the texture
        */
        void load_to_program(Shading_Program *program,
            GLuint image_unit);
        void load_layer_to_program(Shading_Program *program,
            GLuint image_unit, GLuint layer);
        /**
         * @brief Set the OpenGL Label of the image object
         *
         * @param label The name which will identify this texture
        */
        void inline setLabel(std::string label)
        {
            glBindTexture(target, textureID);
            glObjectLabel(GL_TEXTURE, textureID, -1, ("\""+label+"\"").c_str());
        }
};
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
         * @brief Construct a new Mesh object
         *
         * @param string path to a wavefront (.obj) file
        */
        Mesh(std:: string file_path);
        /**
         * @brief Destroy the Mesh object
         *
        */
        ~Mesh();

//──── GPU related methods ───────────────────────────────────────────────────────────────

        /**
         * @brief Draw the mesh
         *
        */
        void draw();

        /**
         * @brief Load mesh information from a wavefront file
         *
         * @param file_path Path to the .obj file
        */
        void load_from_obj(std::string file_path);
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
        GLuint programID;           //!< OpenGL generated identifier

    public:

//──── Constructors and Destructors ──────────────────────────────────────────────────────

        /**
         * @brief Construct a new Shading_Program object
         *
         * The default OpenGL label will be the filename of the vertex shader up until
         * the first '-' character found. So for example a program linked from the
         * shader source files "Basic-vertex.glsl" and "Basic-fragment.glsl" will be
         * labeled "Basic". So it's recommended you name all associated shading source
         * files through the pattern <Descriptive Name>-<shader type>.glsl
         * e.g MyShaders-vertex.glsl.
         *
         * @param vShader Path of the source file of a vertex shader (mandatory)
         *
         * @param tcShader Path of the source file of a tessellation control shader or ""
         *
         * @param teShader Path of the source file of a tessellation evaluation shader or ""
         *
         * @param gShader Path of the source file of a geometry shader or ""
         *
         * @param Path of the source file of a fragment shader (mandatory)
         *
         * @param cShader Path of the source file of a compute shader or ""
         *
        */
        Shading_Program(std::string vShader, std::string tcShader, std::string teShader,
            std::string gShader, std::string fShader, std::string cShader);
        /**
         * @brief Destroy the Shading_Program object
         *
        */
        ~Shading_Program();

//──── Setters and Getters ───────────────────────────────────────────────────────────────
        /**
         * @brief Get the OpenGL ProgramID
         *
         * @return GLuint
        */
        GLuint inline getProgramID(){return programID;}

//──── Other Functions ───────────────────────────────────────────────────────────────────

        /**
         * @brief use the current program
         *
        */
        void inline use(){glUseProgram(programID);}
        /**
         * @brief Set the program's OpenGL label
         *
         * @param name The new label of the program
        */
        void inline set_program_name(std::string name)
        {glObjectLabel(GL_PROGRAM, programID, -1, name.c_str());}
        /**
         * @brief Bind a texture to a uniform of the current program
         *
         * @param texture
         * @param uniform_label
        */
        void bind_texture(Texture texture, std::string uniform_label);

//──── Uniform Functions ─────────────────────────────────────────────────────────────────

        /**
         * @brief Get the location of the uniform labeled <name> in the current program
         *
         * @param name The string representing the uniform to be found
         * @return GLint The location of the uniform in the current shading program
        */
        GLint get_uniform_location(std::string name);
        /**
         * @name Uniform Loading Functions
         *
         * @brief Each of the following functions loads the values described in the first
         * parameter into the uniform labeled "name"
         *
         * @param type the structure containing the info to load
         * @param name string describing the name of the uniform as it appears on the shaders
        */
        ///@{
        void inline load_uniform(glm::mat4 matrix, std::string name)
        {
            GLint loc = get_uniform_location(name);
            glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matrix));
        }

        void inline load_uniform(glm::vec4 vector, std::string name)
        {
            GLint loc = get_uniform_location(name);
            glUniform4fv(loc, 1, (GLfloat*)&(vector));
        }

        void inline load_uniform(glm::vec3 vector, std::string name)
        {
            GLint loc = get_uniform_location(name);
            glUniform3fv(loc, 1, (GLfloat*)&(vector));
        }

        void inline load_uniform(float num, std::string name)
        {
            GLint loc = get_uniform_location(name);
            glUniform1f(loc, num);
        }

        void inline load_uniform(double num, std::string name)
        {
            GLint loc = get_uniform_location(name);
            glUniform1f(loc, num);
        }

        void inline load_uniform(int num, std::string name)
        {
            GLint loc = get_uniform_location(name);
            glUniform1i(loc, num);
        }
        ///@}
};
}//Close helios namespace
//########################################################################################


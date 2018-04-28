//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Header defining some inline methods for loading uniform variables to shaders
 *
 * @file Uniform-Access.hpp
 * @author Camilo Talero
 * @date 2018-04-26
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================

#include "System-Libraries.hpp"

#define UNIFORM_NOT_FOUND -1
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                               Uniform Loading Functions                              *
 *                                                                                      */
//========================================================================================

/**
 * @brief Get the location of the uniform "name" in the current program
 *
 * @param name The string representing the uniform to be found
 * @return GLint The location of the uniform in the current shading program
*/
GLint inline get_uniform_location(std::string name)
{
    GLint programID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &programID);
    GLint loc = glGetUniformLocation(programID, name.c_str());
	if(loc == GL_INVALID_VALUE || loc==GL_INVALID_OPERATION || loc==UNIFORM_NOT_FOUND)
	{
		std::cerr << "Error returned when trying to find uniform " <<
        "\"" + name + "\"" << std::endl;

        if(loc == UNIFORM_NOT_FOUND)
        {
            char label_buffer[50];
            GLsizei buff_size;
            glGetObjectLabel(GL_PROGRAM, programID, 50, &buff_size, label_buffer);

            Log::record_log(
                std::string(80, '!') + "\nFailed to find uniform: " + name + "\n" +
                "No such uniform exists in program: " + std::string(label_buffer) + "\n" +
                std::string(80, '!')
            );
        }
        else
        {
            Log::record_log(
                std::string(80, '!') +
                "Problem when requesting uniform: " + name + "\n" +
                "Check that there is an active program and that it has been correctly"
                "Initialized" +
                std::string(80, '!')
            );
        }
		exit(EXIT_FAILURE);
    }

    return loc;
}

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
//########################################################################################
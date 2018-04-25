//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief A set of functions to generate OpenGL debugging messages
 *
 * @file Debugging.hpp
 * @author Camilo Talero
 * @date 2018-04-19
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================
#pragma once

#include "System-Libraries.hpp"

namespace Helios{
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                 Function Declarations                                *
 *                                                                                      */
//========================================================================================

/**
 * @brief Function to be set with
 * <a href=
 * "https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageCallback.xhtml"
 * >glDebugMessageCallback()</a>
 *
 * This function should be passed as a parameter to glDebugMessageCallback() to print
 * debug information when an error occurs.
 *
 * @param source Enumerator of the origin of the error (e.g GL_DEBUG_SOURCE_API)
 * @param type The error type enumerator (e.g GL_DEBUG_TYPE_ERROR)
 * @param id The error enumerator (e.g GL_INVALID_ENUM)
 * @param severity The severity of the error(e.g GL_DEBUG_SEVERITY_HIGH)
 * @param length The length in bytes of the error message
 * @param message The pointer to the first character in the error emssage
 * @param userParam A user defined pointer paramter (not used by Helios)
*/
void errorCallback( GLenum source, GLenum type, GLuint id, GLenum severity,
                    GLsizei length, const GLchar* message, const void* userParam );

///@{
/**
 * @name Enumerator to string functions
 * @brief Return the string representing an OpenGL enumerator
 *
 * @param e The enumerator
 * @return std::string The representing string
*/
std::string errEnumToString(GLenum e);
std::string errSourceToString(GLenum e);
std::string errTypeToString(GLenum e);
std::string errSeverityToString(GLenum e);
std::string shaderEnumToString(GLenum e);
///@}
}//Closing Helios namespace
//########################################################################################


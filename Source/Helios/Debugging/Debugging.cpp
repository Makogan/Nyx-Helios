//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Implementation of OpenGL debug functions
 * 
 * @file Debug.cpp
 * @author Camilo Talero
 * @date 2018-04-19
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================
#include "Debugging.hpp"

namespace Helios{
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                 Function Definitions                                 *
 *                                                                                      */
//========================================================================================

//Error enumerator
std::string errEnumToString(GLenum err)
{
    switch (err)
    {
        case GL_NO_ERROR:                      return "GL_NO_ERROR";
        case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:                return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:               return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
        case 0x8031: /* not core */            return "GL_TABLE_TOO_LARGE_EXT";
        case 0x8065: /* not core */            return "GL_TEXTURE_TOO_LARGE_EXT";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:
            return "Unkown error code: " + std::to_string(err);
    }
}

//Error source
std::string errSourceToString(GLenum errorS)
{
    switch(errorS)
    {
        case GL_DEBUG_SOURCE_API:               return "GL_DEBUG_SOURCE_API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:   return "GL_DEBUG_SOURCE_SHADER_COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY:       return "GL_DEBUG_SOURCE_THIRD_PARTY";
        case GL_DEBUG_SOURCE_APPLICATION:       return "GL_DEBUG_SOURCE_APPLICATION";
        case GL_DEBUG_SOURCE_OTHER:             return "GL_DEBUG_SOURCE_OTHER";
        default:
            return "Unkown error source enumerator: " + std::to_string(errorS);
    }
}

//Error type
std::string errTypeToString(GLenum errorT)
{
    switch(errorT)
    {
        case GL_DEBUG_TYPE_ERROR:               return "GL_DEBUG_TYPE_ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY:         return "GL_DEBUG_TYPE_PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE:         return "GL_DEBUG_TYPE_PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER:              return "GL_DEBUG_TYPE_MARKER";
        case GL_DEBUG_TYPE_PUSH_GROUP:          return "GL_DEBUG_TYPE_PUSH_GROUP";
        case GL_DEBUG_TYPE_POP_GROUP:           return "GL_DEBUG_TYPE_POP_GROUP";
        case GL_DEBUG_TYPE_OTHER:               return "GL_DEBUG_TYPE_OTHER";
        default:
            return "Unkown error type enumerator: " + std::to_string(errorT);
    }
}

//Error severity
std::string errSeverityToString(GLenum errorS)
{
    switch(errorS)
    {
        case GL_DEBUG_SEVERITY_HIGH:            return "GL_DEBUG_SEVERITY_HIGH";
        case GL_DEBUG_SEVERITY_MEDIUM:          return "GL_DEBUG_SEVERITY_MEDIUM";
        case GL_DEBUG_SEVERITY_LOW:             return "GL_DEBUG_SEVERITY_LOW";
        case GL_DEBUG_SEVERITY_NOTIFICATION:    return "GL_DEBUG_SEVERITY_NOTIFICATION";
        default:
            return "Unkown severity enumerator: " + std::to_string(errorS);
    }
}

//Shader type
std::string shaderEnumToString(GLenum shader_type)
{
    switch(shader_type)
    {
        case GL_VERTEX_SHADER:          return "GL_VERTEX_SHADER";
        case GL_TESS_CONTROL_SHADER:    return "GL_TESS_CONTROL_SHADER";
        case GL_TESS_EVALUATION_SHADER: return "GL_TESS_EVALUATION_SHADER";
        case GL_GEOMETRY_SHADER:        return "GL_GEOMETRY_SHADER";
        case GL_FRAGMENT_SHADER:        return "GL_FRAGMENT_SHADER";
        case GL_COMPUTE_SHADER:         return "GL_COMPUTE_SHADER";
        default:
            return "Not a shader enumerator value: " + std::to_string(shader_type);
    }
}

//Error message generation
void errorCallback(   GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message, const void* userParam )
{
    std::string wMessage = Log::wrap_text(std::string(message), 80);
    std::cerr << "OpenGL Event Notification:\n" + wMessage << std::endl;

    char frame = '!';
    if(severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        frame = '-';

    std::string error_message = std::string(80, frame) + "\n";
    error_message += "OpenGL Event Notification:\n";
    error_message += "Source: " + errSourceToString(source) + "\n";
    error_message += "Type: " + errTypeToString(type) + "\n";
    error_message += "ID: " + errEnumToString(id) + "\n";
    error_message += "Severity: " + errSeverityToString(severity) + "\n";
    error_message += "Message:\n" + wMessage;
    error_message += std::string(80, frame);

    Log::record_log(error_message);
}
}//Helios namespace closing bracket
//########################################################################################
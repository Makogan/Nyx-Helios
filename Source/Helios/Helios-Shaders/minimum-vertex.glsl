//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief The smallest vertex shader to get some kind of output
 * 
 * @file minimum-vertex.glsl
 * @author Camilo Talero
 * @date 2018-04-19
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#version 460

const vec2 vertices[4] = {vec2(-1.0,-1.0),vec2(1.0,-1.0),vec2(-1.0,1.0),vec2(1.0,1.0) };

void main()
{
    gl_Position = vec4(vertices[gl_VertexID], 0.0, 1.0);
}
//########################################################################################
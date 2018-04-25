//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief A simple fragment shader to render 3D objects.
 *
 * @file Basic-Vertex.glsl
 * @author Camilo Talero
 * @date 2018-04-24
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#version 460

layout(location = 0) in vec3 position;  // (x,y,z) coordinates of a vertex
layout(location = 1) in vec3 normal;      // normal to the vertex
layout(location = 2) in vec2 uv;        // texture coordinates

out vec3 v_pos;
out vec3 v_norm;
out vec2 v_uv;

uniform mat4 model_view = mat4(1);  // model view matrix
uniform mat4 proj = mat4(1);        // perspective projection matrix

void main()
{
    vec4 pos = model_view*vec4(position, 1.0);
    gl_Position = proj*pos;

    v_pos = vec3(pos);
    v_norm = vec3(model_view*vec4(normal,1.0));
    v_uv = uv;

}
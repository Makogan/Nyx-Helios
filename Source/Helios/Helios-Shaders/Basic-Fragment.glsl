//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief A simple fragment shader to render 3D objects
 * 
 * @file Basic-Fragment.glsl
 * @author Camilo Talero
 * @date 2018-04-24
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#version 460

in vec3 v_pos;
in vec3 v_norm;
in vec2 v_uv;

out vec4 fragment_color;

void main()
{
    fragment_color = vec4(v_norm,0);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief A simple fragment shader to render 3D objects
 * 
 * @file Basic-Fragment.glsl
 * @author Camilo Talero
 * @date 2018-04-24
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#version 430

in vec3 v_pos;
in vec3 v_norm;
in vec2 v_uv;

out vec4 fragment_color;

vec3 light = vec3(20,20,20);

uniform vec3 camera_position;

uniform sampler2D testing;

vec4 blinn_phong()
{
    vec3 pos = v_pos;

	vec4 color = vec4(0);
	vec3 l = vec3(light-v_pos);
	if(length(l)>0)
		l = normalize(l);
    vec3 c = vec3(texture(testing, v_uv));
	vec3 n = normalize(v_norm);
	vec3 e = camera_position-v_pos;
	e = normalize(e);
	vec3 h = normalize(e+l);

	color = vec4(c*(vec3(0.5)+0.5*max(0,dot(n,l))) +
		vec3(0.1)*max(0,pow(dot(h,n), 100)), 1);

    return color;

}

void main()
{
    fragment_color = blinn_phong();
}
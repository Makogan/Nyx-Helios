//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Implementation of a 3D camera object
 * 
 * @file Camera.cpp
 * @author Camilo Talero
 * @date 2018-04-26
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================

#include "Camera.hpp"

using namespace glm;
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                     Camera Class                                     *
 *                                                                                      */
//========================================================================================
namespace Helios{

Camera::Camera()
{
    side = vec3(-1,0,0);
	forward = vec3(0,0,1);
	up = vec3(0,1,0);
	position = vec3(0,0,0);

	width = 1980;
	height = 1024;

	fov = 45;
	near_plane = 0.01;
	far_plane = 2000;
}

void Camera::rotateH(float angle)
{
    forward = rotate(forward, angle, up);
    side = rotate(side, angle, up);
}

void Camera::rotateV(float angle)
{
    forward = rotate(forward, angle, side);
}

void Camera::load_to_program(Shading_Program *program)
{
    program->load_uniform(getViewMatrix(), "view_m");
    program->load_uniform(getPerspectiveMatrix(), "proj_m");
    program->load_uniform(position, "camera_position");
}
//########################################################################################

}//Helios namespace closing bracket
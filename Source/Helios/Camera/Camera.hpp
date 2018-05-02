//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Header declaration of a 3D camera object for projection based rendering
 * 
 * @file Camera.hpp
 * @author Camilo Talero
 * @date 2018-04-26
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================

#include "Helios/System-Libraries.hpp"
#include "Helios-Wrappers.hpp"

//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                     Camera Class                                     *
 *                                                                                      */
//========================================================================================
namespace Helios {
class Camera
{
    private:
        float fov;
        float far_plane;
        float near_plane;
        float width;
        float height;

        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 side;

    public:
        Camera();

        glm::mat4 inline getViewMatrix(){
            return glm::lookAt(position, position+forward, up);}

        glm::mat4 getPerspectiveMatrix(){
            return glm::perspective(fov, width/height, near_plane, far_plane);}

        glm::vec3 inline getPosition(){return position;}
        glm::vec3 inline getForward(){return forward;}
        glm::vec3 inline getSide(){return side;}

        void inline setPosition(glm::vec3 new_pos){position = new_pos;}
        void inline translate(glm::vec3 offset){position += offset;}
        void inline translateForward(float speed)
        {
            glm::vec3 hForward = forward;
            hForward.y = 0;
            hForward = normalize(hForward);

            position += hForward*speed;
        }

        void inline translateSideways(float speed)
        {
            position += side*speed;
        }
        //TODO: perhaps these should be inline functions
        void rotateH(float angle);
        void rotateV(float angle);
        //TODO: this may need to return an error checking code
        void load_to_program(Shading_Program *program);
};

}//Close Helios namespace
//########################################################################################
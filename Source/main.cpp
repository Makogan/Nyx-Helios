//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Main file to start execution of the program
 * 
 * @file main.cpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//========================================================================================
/*                                                                                      *
 *                                  Includes and Macros                                 *
 *                                                                                      */
//========================================================================================
#include "Nyx.hpp"
#include "Helios.hpp"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;
//########################################################################################


//========================================================================================
/*                                                                                      *
 *                                         Main                                         *
 *                                                                                      */
//========================================================================================

GLuint tvao;
GLuint tvbo1;
GLuint tvbo2;
void render()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}
int main()
{
    Nyx::NyxInit(NYX_TOLERANCE_HIGH);
    Nyx::Nyx_Window w = Nyx::Nyx_Window("Example", render, NULL, true);

    Helios::HeliosInit();
    Helios::Shading_Program v = Helios::Shading_Program(
        "Helios-Shaders/Basic-Vertex.glsl", "",
        "", "", "Helios-Shaders/Basic-Fragment.glsl", "");

    v.use();

    vector<glm::vec3> triangle = {glm::vec3(-1,-1,0), glm::vec3(1,-1,0), glm::vec3(0,1,0)};
    vector<glm::vec3> ns = {glm::vec3(-1,-1,0), glm::vec3(1,-1,0), glm::vec3(0,1,0)};

    glGenVertexArrays(1, &tvao);
    glBindVertexArray(tvao);

    glGenBuffers(1, &tvbo1);
    glBindBuffer(GL_ARRAY_BUFFER, tvbo1);
    glObjectLabel(GL_BUFFER, tvbo1, 21, "\"Mesh Vertex Buffer\"");
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*triangle.size(), triangle.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &tvbo2);
    glBindBuffer(GL_ARRAY_BUFFER, tvbo2);
    glObjectLabel(GL_BUFFER, tvbo2, 22, "\"Mesh Normals Buffer\"");
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*ns.size(), ns.data(), GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0,0);

    glEnableVertexAttribArray(1);
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(1,1); 

    GLuint ptrs[] = {tvbo1, tvbo2};
    GLintptr offsets[] = {0,0};
    int strides[] = {sizeof(vec3),sizeof(vec3)};
    glBindVertexBuffers(0, 2, ptrs, offsets, strides); //comment

    w.start_loop();
}
//########################################################################################

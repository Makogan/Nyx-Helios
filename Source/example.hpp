#pragma once

#include "Nyx.hpp"
#include "Helios.hpp"
#include <glm/glm.hpp>

extern Helios::Camera c;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void update();
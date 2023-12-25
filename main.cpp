#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Renderer.h"

Renderer renderer;

glm::vec3 camRayOrigin = glm::vec3(0.0f, 0.0f, 2.0f);

int screenWidth = 800;
int screenHeight = 800;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
        camRayOrigin.y += 0.01f;
    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
        camRayOrigin.y -= 0.01f;
    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
        camRayOrigin.x -= 0.01f;
    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
        camRayOrigin.x += 0.01f;
}
//function to take pixel colors from renderer.h calcPixel func
void setPixelColor(int sw, int sh)
{
    for (int i = 0; i < sw; i++)
    {
        for (int j = 0; j < sh; j++)
        {
            glm::vec3 color = renderer.CalcPixel(i, j, sw, sh, camRayOrigin);
            glColor3f(color.x, color.y, color.z);
            glVertex2i(i, j);

        }
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(screenWidth, screenHeight, "Raytracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    //Loading OpenGL
    gladLoadGL();

    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0, -1.0, 0.0);
    glScalef(2.0 / float(screenWidth), 2.0 / float(screenHeight), 0.0);


    //main game loop
    while (!glfwWindowShouldClose(window))
    {

        glfwSetTime(0);
        double t1 = glfwGetTime();

        glBegin(GL_POINTS);
        setPixelColor(screenWidth, screenHeight);
        glFinish();
        glfwSwapBuffers(window);

        double t2 = glfwGetTime();
        std::cout << (t2 - t1) * 1000 << " milliseconds" << "\n";

        glfwPollEvents();
    }

    glfwTerminate();
    exit(0);
    return 0;
}


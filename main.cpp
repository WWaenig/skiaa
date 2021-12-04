
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "dconfig.h"

Window A1/(SCREEN_WIDTH, SCREEN_HEIGHT);

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            A1.keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            A1.keys[key] = GL_FALSE;
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "A1", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    A1.init();

    while (!glfwWindowShouldClose(window)) {
        clock_t start = clock();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        A1.processInput();
        A1.update();
        A1.render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
#define FPS 1000/33
        clock_t end = clock();
        int time_ms = (double) (end - start) / CLOCKS_PER_SEC * 1000;
        printf("#Render time: %d\n", time_ms);
        if ((FPS - time_ms) > 0) {
            usleep((FPS - time_ms) * 1000);
        }
    }

    glfwTerminate();

    return 0;
}

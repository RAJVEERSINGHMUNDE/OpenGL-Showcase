#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <STB/stb_image.h>
#include <glm-1.0.1/glm/glm.hpp>
#include <glm-1.0.1/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.1/glm/gtc/type_ptr.hpp>

using namespace std;
const float radius = 10.0f;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void cameraInput(GLFWwindow* window, float* theta, float* phi){
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        *phi =- 10;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        *theta =+ 10;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        *theta =- 10;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        *phi =+ 10;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

std::string readFile(const char* filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::string vertexShaderSource = readFile("src/vertex.glsl");
    std::string fragmentShaderSource = readFile("src/fragment.glsl");
    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    //cout << vertexShader << endl;

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    //cout << fragmentShader << endl;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //cout << shaderProgram << endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

float vertices[] = {
    // FRONT FACE (z = +0.5)
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left

    // BACK FACE (z = -0.5)
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left

    // LEFT FACE (x = -0.5)
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left

    // RIGHT FACE (x = +0.5)
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left

    // BOTTOM FACE (y = -0.5)
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // top-right
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left

    // TOP FACE (y = +0.5)
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f   // bottom-left
};


    GLuint VAO, VBO, EBO, texture;
    /*int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;*/

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glGenTextures(1, &texture);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("src/container.jpg", &width, &height, &nrChannels, 0);
    int format = nrChannels == 4 ? GL_RGBA : GL_RGB;  // if the png has alpha then bt ho jayegi
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::vec3 cameraPos =       glm::vec3(0.0f, 0.0f, 3.0f); //selfExplanatory
    glm::vec3 cameraTarget =    glm::vec3(0.0f, 0.0f, 0.0f);//camera looks at the origin
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);//camera is locked to the origin
    glm::vec3 up =              glm::vec3(0.0f, 0.0f, 1.0f);//universal up(z axis)
    glm::vec3 cameraRight =     glm::normalize(glm::cross(cameraDirection, up));//simple across product
    glm::vec3 cameraUp =        glm::vec3(cross(cameraDirection, cameraRight));//right&direcn always normalised so no need

    glUseProgram(shaderProgram);
    glm::mat4 model = glm::mat4(1.0f); //this aint a valid global initialization hence its here
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    /*glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));*/
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    // note that we’re translating the scene in the reverse direction

    unsigned int modelloc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewloc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionloc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model)); //what are the parameters ??
    glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionloc, 1, GL_FALSE, glm::value_ptr(projection));

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f, 2.0f, -2.5f),
    glm::vec3( 1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    float camX, camZ, frametimer, time;
    int i;

    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        //cameraInput(window, theta_ptr, phi_ptr);

        glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model)); //what are the parameters ??
            glDrawArrays(GL_TRIANGLES, 0, 36);
        };

        time = glfwGetTime();
        camX = sin(time) * radius;
        camZ = cos(time) * radius;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));

        if(glfwGetTime() >= frametimer + 1)
            {
                cout << i << endl;
                frametimer = time;
                i=0;
            }

        i++;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteShader(shaderProgram);

    glfwTerminate();
    return 0;
}

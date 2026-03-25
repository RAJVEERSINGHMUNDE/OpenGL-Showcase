#include <iostream>
#include <glad/glad.h> //this header goes before the GLFW header because GLFW imports
#include <GLFW/glfw3.h>//the same headers as well. Without GLAD the program would link but crash at
#include <string.h>//runtime since function pointers are fetched by glad at runtime.

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){
    const char* VertexShaderSource =        "#version 460 core\n"
    /*location=0 is related to vertex*/     "layout (location = 0) in vec3 pos;\n"
    /*attrib pointer first argument  */     "out vec4 color;\n"
    /*and its what tells opengl what data */"void main(){\n"
    /*to feed the shader from currently*/   "    gl_Position = vec4(pos, 1.0);\n"
    /*bound VBO*/                           "}\n";

    const char* FragmentShaderSource =  "#version 460 core\n"
                                        "in vec4 color;\n"
                                        "out vec 4 FragColor;\n"
                                        "void main(){\n"
                                        "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
                                        "}\n";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 1920, 1080);

    GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &VertexShaderSource, NULL);
    glCompileShader(vertexshader);
    std::cout << vertexshader << std::endl;

    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &FragmentShaderSource, NULL);
    glCompileShader(fragmentshader);
    std::cout << fragmentshader << std::endl;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexshader);
    glAttachShader(shaderProgram, fragmentshader);
    glLinkProgram(shaderProgram);
    glDeleteShader(fragmentshader);
    glDeleteShader(vertexshader);
    std::cout << shaderProgram << std::endl;

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float vertices[] = {0.0,  0.5,  0.0,
                      0.5, -0.5,  0.0,
                     -0.5, -0.5,  0.0};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    //location as first argument for shaders to know and match the data that is
    //being provided to them, second is the number of data points, third is the type
    //fourth is whether we want the data normalised or not, 5th is stride
    //and sixth is offset, zero for the first set of coordinates
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);

    glfwSwapInterval(1); //VSync
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        //glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteShader(shaderProgram);

    glfwTerminate();
    return 0;
}

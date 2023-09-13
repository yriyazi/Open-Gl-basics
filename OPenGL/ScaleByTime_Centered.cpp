#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex shader source code
const char* vertexShaderSource = R"GLSL(
    #version 330 core

    uniform float time;
    uniform vec2 windowSize;

    in vec2 position;

    void main()
    {
        float scale = sin(time) + 1.0;
        vec2 scaledPosition = position * scale;
        vec2 adjustedPosition = (scaledPosition / windowSize) * 2.0 - 1.0;
        gl_Position = vec4(scaledPosition, 0.0, 1.0);
    }
)GLSL";

// Fragment shader source code
const char* fragmentShaderSource = R"GLSL(
    #version 330 core
    uniform float time;
    out vec4 fragColor;

    void main()
    {

        fragColor = vec4(0, sin(time), 0, 0.10);  // Red color
    }
)GLSL";

int vvmain()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create the shader program and attach the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders as they're linked into the program now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create vertex data for the triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f,  // Vertex 1: Bottom Left
        0.5f, -0.5f,   // Vertex 2: Bottom Right
        0.0f, 0.5f     // Vertex 3: Top
    };

    // Create a vertex array object (VAO) and vertex buffer object (VBO)
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Set the vertex data into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Specify the vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Render loop
    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        // Get the window size
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Adjust the viewport to the new window size
        glViewport(0, 0, width, height);

        // Clear the screen
        //glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Pass the time uniform variable to the vertex shader
        float time = static_cast<float>(glfwGetTime());
        GLint timeLocation = glGetUniformLocation(shaderProgram, "time");
        glUniform1f(timeLocation, time+i);

        // Pass the window size uniform variable to the vertex shader
        GLint windowSizeLocation = glGetUniformLocation(shaderProgram, "windowSize");
        glUniform2f(windowSizeLocation, static_cast<float>(width), static_cast<float>(height));

        // Bind the VAO and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
        i += 1;
    }

    // Cleanup
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

# include "all_includes.h"
# include "all_includes.h"

/*
GLm beacuse is a light weight library and onlu contain header we dont need to link it
*/
const GLuint WIDTH = 800 , HEIGHT = 600;


const GLchar* vShader = R"(
    #version 330 core                              
    layout (location = 0) in vec3 position;

    //outputing color
    out vec4 vColor;

    uniform mat4 model;

    void main()
    {

        gl_Position = model * vec4(position, 1.0);

        //
        vColor = vec4(clamp(vec3(gl_Position.x,gl_Position.y,gl_Position.z),0.0f,1.0f),1.0f);
    }
)";

const GLchar* fShader = R"(
    #version 330 core                              
    out vec4 color;

    //inputting the color
    in vec4 vColor;

    void main()
    {
        color = vColor;// vec4(1.0,1.0,0.0, 1.0);
    }
)";



GLuint VAO, VBO, shader;

float   triOffset = 0.0f;
bool    direction = true;

float TriMaxOffset = 0.7f;
float triIncrement = 0.005f; 


void CreateTriangle()
{
    // Define triangle vertices
    GLfloat vertices[] = {
                            -1.f, -1.0f, 0.0f,  // Vertex 1: Position
                            1.0f, -1.0f, 0.0f,   // Vertex 2: Position
                            0.0f, 1.0f, 0.0f,    // Vertex 3: Position
    };
    // Creating a VAO
    // glGenVertexArrays(how many,id Of that)
    glGenVertexArrays(1, & VAO);
    // because the array is on GPu and there is no direct acess we need to pass
    // the id and then conncet that id to that shader
    glBindVertexArray(VAO);
        //we need to make a buffer to it go inside that
        // 
        // create a buffer object inside the VAO and pass the id
            glGenBuffers(1,& VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

                ///////////// GL_STATIC_DRAW dosent allow you to change the values
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);
                // glVertexAttribPointer( 0 , row lenght , data type , do normalize ,stride in array , start from);
                glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 0 , 0);
                glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addShader(GLuint theProgram , const GLchar* shaderCode , GLenum    shaderType)
{
    //creatr empty shader for this type
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLenght[1];
    codeLenght[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLenght);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar elog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(elog), NULL, elog);
        printf("Error in Compiling the %d shader program : '%s \n", shaderType, elog);

        return;
    }

    glAttachShader(theProgram, theShader);

    return;
}

void CompileShader() 
{
    shader = glCreateProgram();

    if (!shader) {
        printf("Error in shader Compiling");

        return ;
    }

    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    // for debuging
    GLint result = 0;
    GLchar elog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, & result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(elog),NULL, elog);
        printf("Error in Linking program : '%s \n",elog);

        return;
    }

    //validate program (if opengl is set up correctly for this shader)
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
        printf("Error in Validating program : '%s \n", elog);

        return;
    }

    // uniform xMOve
    //--------------------------------------------------
    // this id will be use to bind tha variable to value
    //--------------------------------------------------
    GLint uniformModel = glGetUniformLocation(shader, "model");

    
}



int main()
{
    // --------------------------------------
    // -----------IMPORTANT------------------
    // --------------------------------------
    //          Initialize GLFW
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW");
        glfwTerminate();
        return 1;
    }

    // Set GLFW options
    // in next two following line we define the version 3.3 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // GLFW_OPENGL_PROFILE          : define how should code that past to it interpered
    // GLFW_OPENGL_CORE_PROFILE     : not be backward compatible (we dont want use deprecated features , feature thta removed or going to be removed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allow forwaed compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFW window
    // we actually create a pointer to window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
    
    //checking that windows is created successfuly
    if (!window)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    //get buffer size information
    int bufferwidth, bufferheight;
    glfwGetFramebufferSize(window, &bufferwidth,&bufferheight);

    //set contex for GLEW to use
    //we can stitch windows and draw on them
    glfwMakeContextCurrent(window);

    //allow  modern extention features
    glewExperimental = GL_TRUE;


    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }


    // Set viewport size
    glViewport(0, 0, bufferwidth,bufferheight);
    CreateTriangle();
    CompileShader();
    
    GLint uniformModel = glGetUniformLocation(shader, "model");
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Adjust the viewport to the new window size
        glViewport(0, 0, width, height);

        // Poll events (get and handle user input events)
        glfwPollEvents();

        if (direction)
        {
            triOffset += triIncrement;
        }
        else
        {
            triOffset -= triIncrement;
        }

        if (abs(triOffset)>=TriMaxOffset)
        {
            direction = !direction;
        }
        //printf(" % f",triOffset);
        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // assing and unassing shader
        glUseProgram(shader);

        // Set up uniform mat
        
        /*
        glm::mat4 model = glm::mat4(1.0f);  // Identity matrix
        glm::vec3 translation(triOffset, triOffset, 0.0f);
        model = glm::translate(model, translation);  // Apply translation

        glm::mat4 model_scale = glm::mat4(1.0f);  // Identity matrix
        model_scale = glm::scale(model_scale, glm::vec3(triOffset, 0.2, 0.2));

        // Create a rotation matrix using GLM
        glm::mat4 model_rotation = glm::mat4(1.0f); // Identity matrix
        float angle = static_cast<float>(glfwGetTime()) * glm::radians(50.0f)*2;
        model_rotation = glm::rotate(model_rotation, angle, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z-axis

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model* model_scale* model_rotation));
        */
        float angle = static_cast<float>(glfwGetTime()) * glm::radians(50.0f) * 2;

        glm::mat4 model = glm::mat4(1.0f);  // Identity matrix
        glm::vec3 translation(triOffset, triOffset, 0.0f);
        model = glm::scale(model    , glm::vec3(0.5f, 0.5f, 1.0f));

        
        model = glm::translate(model, translation);  // Apply translation
        model = glm::rotate(model   , angle, glm::vec3(0.0f, 1.0f, 1.0f)); // Rotate around Z-axis
        
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glBindVertexArray(0);
        glUseProgram(0);

        // Swap buffers (we have 2 scene 1 one draw and a for show and we change them
        glfwSwapBuffers(window);
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
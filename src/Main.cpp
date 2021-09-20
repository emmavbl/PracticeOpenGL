#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 1200;


int main(void)
{
    glfwInit();

    // Create and init GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PracticeOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shaderProgram = Shader("res/shaders/shader.vs", "res/shaders/shader.fs");

    float vertices[] = {
        // position             //color
         0.5f,  0.5f, 0.0f,     1.0, 1.0, 0.0, // top right
         0.5f, -0.5f, 0.0f,     0.0, 1.0, 1.0, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0, 1.0, 0.0, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0, 0.0, 0.0  // top left 
    };
    unsigned int indices[] = { 
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Generate VBO and VAO 
    unsigned int VBO; 
    unsigned int VAO;
    unsigned int EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);// Bind VAO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);// Bind VBO
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            // Bind EBO and load indices data
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // Configure OpenGl's vertices reading in VBO
                // position Attributes
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
                // color Attributes
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3* sizeof(float)));
            glEnableVertexAttribArray(1);

            // Do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
    glBindVertexArray(0); // Unbind VAO

    // Draw in Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);
        
        // Rendering command
        // Clear
        glClearColor(0.529f, 0.850f, 0.776f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.bind();

        // update shader uniform
        float timeValue = glfwGetTime();
        float value = sin(timeValue) / 2.0f + 0.5f;
        shaderProgram.setFloat("myValue", value);

        glBindVertexArray(VAO);
        // Draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // Check events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean GLFW ressources 
    glfwTerminate();

    return 0;
}

// Called every time the user or OS update window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // orange
"}\n\0";
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n" // yellow
"}\n\0";
const char* fragmentShader3Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n" // red
"}\n\0";
const char* fragmentShader4Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.7f, 0.0f, 0.4f, 1.0f);\n" // purple
"}\n\0";
const char* fragmentShader5Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.9f, 0.0f, 1.0f);\n" // gold
"}\n\0";
const char* fragmentShader6Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.8f, 0.0f, 1.0f);\n" // gold_min
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // the fragment shader that outputs the color
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER); 
    unsigned int fragmentShaderPurple = glCreateShader(GL_FRAGMENT_SHADER); 
    unsigned int fragmentShaderGold = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderGoldMin = glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int shaderProgramOrange = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram(); 
    unsigned int shaderProgramRed = glCreateProgram(); 
    unsigned int shaderProgramPurple = glCreateProgram(); 
    unsigned int shaderProgramGold = glCreateProgram();
    unsigned int shaderProgramGoldMin = glCreateProgram();


    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);
    glShaderSource(fragmentShaderRed, 1, &fragmentShader3Source, NULL);
    glCompileShader(fragmentShaderRed);
    glShaderSource(fragmentShaderPurple, 1, &fragmentShader4Source, NULL);
    glCompileShader(fragmentShaderPurple);
    glShaderSource(fragmentShaderGold, 1, &fragmentShader5Source, NULL);
    glCompileShader(fragmentShaderGold);
    glShaderSource(fragmentShaderGoldMin, 1, &fragmentShader6Source, NULL);
    glCompileShader(fragmentShaderGoldMin);

    // link the first program object
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    // then link the second program object using a different fragment shader (but same vertex shader)
    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glAttachShader(shaderProgramRed, vertexShader);
    glAttachShader(shaderProgramRed, fragmentShaderRed);
    glLinkProgram(shaderProgramRed);

    glAttachShader(shaderProgramPurple, vertexShader);
    glAttachShader(shaderProgramPurple, fragmentShaderPurple);
    glLinkProgram(shaderProgramPurple);

    glAttachShader(shaderProgramGold, vertexShader);
    glAttachShader(shaderProgramGold, fragmentShaderGold);
    glLinkProgram(shaderProgramGold);

    glAttachShader(shaderProgramGoldMin, vertexShader);
    glAttachShader(shaderProgramGoldMin, fragmentShaderGoldMin);
    glLinkProgram(shaderProgramGoldMin);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cabeza[] = {
        -1.0f,  0.4f, 0.0f,  
        -0.6f,  0.8f, 0.0f,  
        -0.6f,  0.4f, 0.0f,  
    };
    float cuello[] = {
        -0.6f,  0.8f, 0.0f,  
        -0.2f,  0.4f, 0.0f,  
        -0.6f,  0.0f, 0.0f  
    };
    float pecho[] = {
         0.2f,  0.8f, 0.0f,
         0.2f,  0.0f, 0.0f,
        -0.6f,  0.0f, 0.0f
    };
    float ala[] = {
         1.0f,  0.8f, 0.0f,
         0.2f,  0.8f, 0.0f,
         0.2f,  0.0f, 0.0f
    };
    float piernas[] = {
        -0.6f,  0.0f, 0.0f,
         0.2f,  0.0f, 0.0f,
         0.2f, -0.8f, 0.0f
    };
    float pies[] = {
         0.2f, -0.4f, 0.0f,
         0.6f, -0.8f, 0.0f,
         0.2f, -0.8f, 0.0f
    };
    float fondo_arriba[] = {
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f
    };
    float fondo_arriba2[] = {
         0.0f,  1.0f, 0.0f,
        -1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };
    float fondo_abajo[] = {
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f
    };
    float fondo_abajo2[] = {
         1.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f
    };
    unsigned int VBOs[10], VAOs[10];
    glGenVertexArrays(10, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(10, VBOs);

    // triangulos fondo 
    glBindVertexArray(VAOs[0]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(fondo_arriba), fondo_arriba, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fondo_abajo), fondo_abajo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[2]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(fondo_arriba2), fondo_arriba2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[3]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(fondo_abajo2), fondo_abajo2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);


    // partes ave
    // --------------------
    glBindVertexArray(VAOs[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cabeza), cabeza, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // ---------------------
    glBindVertexArray(VAOs[5]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(cuello), cuello, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);
    // ---------------------
    glBindVertexArray(VAOs[6]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(pecho), pecho, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);
    // ---------------------
    glBindVertexArray(VAOs[7]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[7]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(ala), ala, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);
    // ---------------------
    glBindVertexArray(VAOs[8]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[8]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(piernas), piernas, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);
    // ---------------------
    glBindVertexArray(VAOs[9]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[9]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(pies), pies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
    glEnableVertexAttribArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramGold);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramGoldMin);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramGoldMin);
        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramGold);
        glBindVertexArray(VAOs[3]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // now when we draw the triangle we first use the vertex and orange fragment shader from the program
        glUseProgram(shaderProgramOrange);
        // draw the triangle using the data from our first VAO
        glBindVertexArray(VAOs[4]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an orange triangle

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[5]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	

        glUseProgram(shaderProgramRed);
        glBindVertexArray(VAOs[6]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	

        glUseProgram(shaderProgramPurple);
        glBindVertexArray(VAOs[7]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAOs[8]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramPurple);
        glBindVertexArray(VAOs[9]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(6, VAOs);
    glDeleteBuffers(6, VBOs);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);
    glDeleteProgram(shaderProgramRed);
    glDeleteProgram(shaderProgramPurple);
    glDeleteProgram(shaderProgramGold);
    glDeleteProgram(shaderProgramGoldMin);


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
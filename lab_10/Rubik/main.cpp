//////////////////////////////////////////////////
/*
*                   CUBO RUBICK                       
* 
    INTEGRANTES DEL GRUPO
  
    * DENNIS PUMARAIME ESPINOZA
    * ANGELA SOLANGE SUCSO CHOQUE

*/
//////////////////////////////////////////////////


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "shader_m.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
#include "mapeos.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// ==================================== CUBO ===========================================
class Cubo
{
public:
    glm::vec3 posicion;
    std::vector<int> colores;
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 getModel();
    Cubo(glm::vec3, int*);

    void transformaciones(glm::vec3, float, glm::vec3);
};

Cubo::Cubo(glm::vec3 posicion, int* ptrColores)
{
    this->posicion = posicion;
    for (int i = 0; i < 6; i++)
        colores.push_back( * (ptrColores + i) );

    // inicia modelo
    //glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(model, posicion);
    model = trans * model;
}

glm::mat4 Cubo::getModel()
{
    return model;
}
void Cubo::transformaciones(glm::vec3 desplazamiento, float angulo, glm::vec3 eje)
{
    //glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, desplazamiento);
    model = trans * model;
    if(angulo != 0.0f)
        model = glm::rotate(model, glm::radians(angulo), eje);
    std::cout << model[3].x << " " << model[3].y << " " << model[3].z << std::endl;
}



// ==================================== RUBIK ==========================================
class Rubik
{
public:
    std::vector<Cubo> cubos;
    Rubik();
    void pintarCubo(int[]);
    void pintarCaraCubo(int, int);
    void accionCubo(GLFWwindow*);
    void movimientoCara_X(int, int);
    void movimientoCara_Y(int, int);
    void movimientoCara_Z(int, int);
};

Rubik::Rubik()
{
    for (int i = 0; i < 27; i++)
    {
        Cubo * unCubo = new Cubo(cubePositions[i], coloresCubos + (i * 6));
        cubos.push_back(*unCubo);
    }
}

void Rubik::pintarCubo(int colores[])
{
    for (int i = 0; i < 6; i++) {
        pintarCaraCubo(i, colores[i]);
    }
};

void Rubik::pintarCaraCubo(int cara, int color)
{
    int indiceCara = ((cara) * 30) + 3;  //indice cara
    int indiceColor = (color) * 12;      //indice color

    vertices[indiceCara] = colores[indiceColor];
    vertices[indiceCara + 1] = colores[indiceColor + 1];
    vertices[indiceCara + 5] = colores[indiceColor + 2];
    vertices[indiceCara + 6] = colores[indiceColor + 3];
    vertices[indiceCara + 10] = colores[indiceColor + 4];
    vertices[indiceCara + 11] = colores[indiceColor + 5];
    vertices[indiceCara + 15] = colores[indiceColor + 6];
    vertices[indiceCara + 16] = colores[indiceColor + 7];
    vertices[indiceCara + 20] = colores[indiceColor + 8];
    vertices[indiceCara + 21] = colores[indiceColor + 9];
    vertices[indiceCara + 25] = colores[indiceColor + 10];
    vertices[indiceCara + 26] = colores[indiceColor + 11];
}


/*
    Caras:
    cara = 0 -> ejeX derecha
    cara = 1 -> ejeX centroX
    cara = 2 -> ejeX izquierda
    cara = 6 -> ejeY arriba
    cara = 7 -> ejeY centroY
    cara = 8 -> ejeY abajo
    cara = 3 -> ejeZ frontal
    cara = 4 -> ejeZ centroZ
    cara = 5 -> ejeZ fondo

    Sentido:
    sentido = 0 -> horario
    sentido = 1 -> antihorario

    Z= cara 0 / sentido 0
*/

void Rubik::movimientoCara_X(int cara, int sentido) 
{ 
    int indice = cara * 9;
    
    if (sentido == 0) {
        //ESPACIO
        // traslacion de medios
        glm::vec3 posicionTmp = cubos[0 + indice].posicion;
        cubos[0 + indice].posicion = cubos[6 + indice].posicion;
        cubos[6 + indice].posicion = cubos[8 + indice].posicion;
        cubos[8 + indice].posicion = cubos[2 + indice].posicion;
        cubos[2 + indice].posicion = posicionTmp;

        Cubo cubito = cubos[0 + indice];
        cubos[0 + indice] = cubos[6 + indice];
        cubos[6 + indice] = cubos[8 + indice];
        cubos[8 + indice] = cubos[2 + indice];
        cubos[2 + indice] = cubito;

        // traslacion de medios
        posicionTmp = cubos[1 + indice].posicion;
        cubos[1 + indice].posicion = cubos[3 + indice].posicion;
        cubos[3 + indice].posicion = cubos[7 + indice].posicion;
        cubos[7 + indice].posicion = cubos[5 + indice].posicion;
        cubos[5 + indice].posicion = posicionTmp;

        cubito = cubos[1 + indice];
        cubos[1 + indice] = cubos[3 + indice];
        cubos[3 + indice] = cubos[7 + indice];
        cubos[7 + indice] = cubos[5 + indice];
        cubos[5 + indice] = cubito;

        for (int i = 0; i < 9; i++) {
            cubos[i + indice].model = glm::rotate(cubos[i + indice].model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        Sleep(500.0);
    }
    else if (sentido == 1) {
        ///ejeY derecha SENTIDO -> HORARIO 0

        //ESPACIO
        // traslacion de medios
        glm::vec3 posicionTmp = cubos[0 + indice].posicion;
        cubos[0 + indice].posicion = cubos[2 + indice].posicion;
        cubos[2 + indice].posicion = cubos[8 + indice].posicion;
        cubos[8 + indice].posicion = cubos[6 + indice].posicion;
        cubos[6 + indice].posicion = posicionTmp;

        Cubo cubito = cubos[0 + indice];
        cubos[0 + indice] = cubos[2 + indice];
        cubos[2 + indice] = cubos[8 + indice];
        cubos[8 + indice] = cubos[6 + indice];
        cubos[6 + indice] = cubito;

        // traslacion de medios
        posicionTmp = cubos[1 + indice].posicion;
        cubos[1 + indice].posicion = cubos[5 + indice].posicion;
        cubos[5 + indice].posicion = cubos[7 + indice].posicion;
        cubos[7 + indice].posicion = cubos[3 + indice].posicion;
        cubos[3 + indice].posicion = posicionTmp;

        cubito = cubos[1 + indice];
        cubos[1 + indice] = cubos[5 + indice];
        cubos[5 + indice] = cubos[7 + indice];
        cubos[7 + indice] = cubos[3 + indice];
        cubos[3 + indice] = cubito;

        for (int i = 0; i < 9; i++) {
            cubos[i + indice].model = glm::rotate(cubos[i + indice].model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        Sleep(500.0);
    }
}

void Rubik::movimientoCara_Y(int cara, int sentido) {

    int indice = cara * 3;
    int secuencia[] = { 0,1,2,9,10,11,18,19,20 };

    if (sentido == 0) {

        //ESPACIO
        // traslacion de medios
        glm::vec3 posicionTmp = cubos[0 + indice].posicion;
        cubos[0 + indice].posicion = cubos[18 + indice].posicion;
        cubos[18 + indice].posicion = cubos[20 + indice].posicion;
        cubos[20 + indice].posicion = cubos[2 + indice].posicion;
        cubos[2 + indice].posicion = posicionTmp;

        Cubo cubito = cubos[0 + indice];
        cubos[0 + indice] = cubos[18 + indice];
        cubos[18 + indice] = cubos[20 + indice];
        cubos[20 + indice] = cubos[2 + indice];
        cubos[2 + indice] = cubito;

        // traslacion de medios
        posicionTmp = cubos[1 + indice].posicion;
        cubos[1 + indice].posicion = cubos[9 + indice].posicion;
        cubos[9 + indice].posicion = cubos[19 + indice].posicion;
        cubos[19 + indice].posicion = cubos[11 + indice].posicion;
        cubos[11 + indice].posicion = posicionTmp;

        cubito = cubos[1 + indice];
        cubos[1 + indice] = cubos[9 + indice];
        cubos[9 + indice] = cubos[19 + indice];
        cubos[19 + indice] = cubos[11 + indice];
        cubos[11 + indice] = cubito;

        for (int i = 0; i < 9; i++) {
            cubos[secuencia[i] + indice].model = glm::rotate(cubos[secuencia[i] + indice].model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        
        Sleep(500.0);
    }
    else if (sentido == 1) {
        ///ejeY derecha SENTIDO -> HORARIO 0

        //ESPACIO
        // traslacion de medios
        glm::vec3 posicionTmp = cubos[0 + indice].posicion;
        cubos[0 + indice].posicion = cubos[2 + indice].posicion;
        cubos[2 + indice].posicion = cubos[20 + indice].posicion;
        cubos[20 + indice].posicion = cubos[18 + indice].posicion;
        cubos[18 + indice].posicion = posicionTmp;

        Cubo cubito = cubos[0 + indice];
        cubos[0 + indice] = cubos[2 + indice];
        cubos[2 + indice] = cubos[20 + indice];
        cubos[20 + indice] = cubos[18 + indice];
        cubos[18 + indice] = cubito;

        // traslacion de medios
        posicionTmp = cubos[1 + indice].posicion;
        cubos[1 + indice].posicion = cubos[11 + indice].posicion;
        cubos[11 + indice].posicion = cubos[19 + indice].posicion;
        cubos[19 + indice].posicion = cubos[9 + indice].posicion;
        cubos[9 + indice].posicion = posicionTmp;

        cubito = cubos[1 + indice];
        cubos[1 + indice] = cubos[11 + indice];
        cubos[11 + indice] = cubos[19 + indice];
        cubos[19 + indice] = cubos[9 + indice];
        cubos[9 + indice] = cubito;

        for (int i = 0; i < 9; i++) {
            cubos[secuencia[i] + indice].model = glm::rotate(cubos[secuencia[i] + indice].model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        Sleep(500.0);
    }
}

void Rubik::movimientoCara_Z(int cara, int sentido) {

    int indice = cara;
    int secuencia[] = { 0,3,6,9,12,15,18,21,24 };

    if (sentido == 0) {

        //ESPACIO
        // traslacion de medios
        glm::vec3 posicionTmp = cubos[0 + indice].posicion;
        cubos[0 + indice].posicion = cubos[18 + indice].posicion;
        cubos[18 + indice].posicion = cubos[24 + indice].posicion;
        cubos[24 + indice].posicion = cubos[6 + indice].posicion;
        cubos[6 + indice].posicion = posicionTmp;

        Cubo cubito = cubos[0 + indice];
        cubos[0 + indice] = cubos[18 + indice];
        cubos[18 + indice] = cubos[24 + indice];
        cubos[24 + indice] = cubos[6 + indice];
        cubos[6 + indice] = cubito;

        // traslacion de medios
        posicionTmp = cubos[3 + indice].posicion;
        cubos[3 + indice].posicion = cubos[9 + indice].posicion;
        cubos[9 + indice].posicion = cubos[21 + indice].posicion;
        cubos[21 + indice].posicion = cubos[15 + indice].posicion;
        cubos[15 + indice].posicion = posicionTmp;

        cubito = cubos[3 + indice];
        cubos[3 + indice] = cubos[9 + indice];
        cubos[9 + indice] = cubos[21 + indice];
        cubos[21 + indice] = cubos[15 + indice];
        cubos[15 + indice] = cubito;

        for (int i = 0; i < 9; i++) {
            cubos[secuencia[i] + indice].model = glm::rotate(cubos[secuencia[i] + indice].model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        }

        Sleep(500.0);
    }
    else if (sentido == 1) {
        ///ejeY derecha SENTIDO -> HORARIO 0

        //ESPACIO
        // traslacion de medios
        glm::vec3 posicionTmp = cubos[0 + indice].posicion;
        cubos[0 + indice].posicion = cubos[6 + indice].posicion;
        cubos[6 + indice].posicion = cubos[24 + indice].posicion;
        cubos[24 + indice].posicion = cubos[18 + indice].posicion;
        cubos[18 + indice].posicion = posicionTmp;

        Cubo cubito = cubos[0 + indice];
        cubos[0 + indice] = cubos[6 + indice];
        cubos[6 + indice] = cubos[24 + indice];
        cubos[24 + indice] = cubos[18 + indice];
        cubos[18 + indice] = cubito;

        // traslacion de medios
        posicionTmp = cubos[3 + indice].posicion;
        cubos[3 + indice].posicion = cubos[15 + indice].posicion;
        cubos[15 + indice].posicion = cubos[21 + indice].posicion;
        cubos[21 + indice].posicion = cubos[9 + indice].posicion;
        cubos[9 + indice].posicion = posicionTmp;

        cubito = cubos[3 + indice];
        cubos[3 + indice] = cubos[15 + indice];
        cubos[15 + indice] = cubos[21 + indice];
        cubos[21 + indice] = cubos[9 + indice];
        cubos[9 + indice] = cubito;

        for (int i = 0; i < 9; i++) {
            cubos[secuencia[i] + indice].model = glm::rotate(cubos[secuencia[i] + indice].model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        }

        Sleep(500.0);
    }
}

void Rubik::accionCubo(GLFWwindow* window)
{
    ///////////////////////////////     CARA X      ///////////////////////////////////
    //derecha
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        std::cout << "Z se esta presionando" << std::endl;
        movimientoCara_X(0, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        std::cout << "X se esta presionando" << std::endl;
        movimientoCara_X(0, 1);
    }
    //medio
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        std::cout << "C se esta presionando" << std::endl;
        movimientoCara_X(1, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        std::cout << "V se esta presionando" << std::endl;
        movimientoCara_X(1, 1);
    }
    //izquierda
    else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        std::cout << "B se esta presionando" << std::endl;
        movimientoCara_X(2, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        std::cout << "N se esta presionando" << std::endl;
        movimientoCara_X(2, 1);
    }
    ////////////////////////////////////////////////////////////////////
    
    /////////////////////////////     CARA  Y      ///////////////////////////////
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        std::cout << "F se esta presionando" << std::endl;
        movimientoCara_Y(0, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        std::cout << "G se esta presionando" << std::endl;
        movimientoCara_Y(0, 1);
    }
    //medio
    else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        std::cout << "H se esta presionando" << std::endl;
        movimientoCara_Y(1, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        std::cout << "J se esta presionando" << std::endl;
        movimientoCara_Y(1, 1);
    }
    //izquierda
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        std::cout << "K se esta presionando" << std::endl;
        movimientoCara_Y(2, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        std::cout << "L se esta presionando" << std::endl;
        movimientoCara_Y(2, 1);
    }
    ////////////////////////////////////////////////////////////////////

/////////////////////////////     CARA  Z      ///////////////////////////////
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        std::cout << "z se esta presionando" << std::endl;
        movimientoCara_Z(0, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        std::cout << "y se esta presionando" << std::endl;
        movimientoCara_Z(0, 1);
    }
    //medio
    else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        std::cout << "y se esta presionando" << std::endl;
        movimientoCara_Z(1, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        std::cout << "y se esta presionando" << std::endl;
        movimientoCara_Z(1, 1);
    }
    //izquierda
    else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        std::cout << "y se esta presionando" << std::endl;
        movimientoCara_Z(2, 0);
    }
    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        std::cout << "y se esta presionando" << std::endl;
        movimientoCara_Z(2, 1);
    }
};

//unsigned int cantCubo = 1;

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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("7.1.camera.vs", "7.1.camera.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int VBO[27], VAO[27];
    glGenVertexArrays(27, VAO);
    glGenBuffers(27, VBO);

    // Se inicializa Rubik
    Rubik rubik;

    //27 cubos 
    for (int i = 0; i < 27; i++) {
        rubik.pintarCubo(coloresCubos + (i*6));
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    
    // load and create a texture 
    // -------------------------
    unsigned int texture1;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("colores.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // aqui se detecta el ingreso de teclas para los movimientos del cubo de rubik
        rubik.accionCubo(window);


        // render boxes
        //glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 27; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = rubik.cubos[i].getModel();

            ourShader.setMat4("model", model);

            ourShader.use();
            glBindVertexArray(VAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(27, VAO);
    glDeleteBuffers(27, VBO);
    //glDeleteProgram(ourShader.ID);

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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
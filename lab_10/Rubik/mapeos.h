#ifndef MAPEOS_H
#define MAPEOS_H

float vertices[] = {

    //fondo
    -0.5f, -0.5f, -0.5f,  0.66f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.99f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.99f, 0.33f,
     0.5f,  0.5f, -0.5f,  0.99f, 0.33f,
    -0.5f,  0.5f, -0.5f,  0.66f, 0.33f,
    -0.5f, -0.5f, -0.5f,  0.66f, 0.0f, // verde 7

    // frente 
    -0.5f, -0.5f,  0.5f,  0.66f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.99f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.99f, 0.33f,
     0.5f,  0.5f,  0.5f,  0.99f, 0.33f,
    -0.5f,  0.5f,  0.5f,  0.66f, 0.33f,
    -0.5f, -0.5f,  0.5f,  0.66f, 0.0f, // naranja 8

    // izquierda
    -0.5f,  0.5f,  0.5f,  0.66f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.99f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.99f, 0.33f,
    -0.5f, -0.5f, -0.5f,  0.99f, 0.33f,
    -0.5f, -0.5f,  0.5f,  0.66f, 0.33f,
    -0.5f,  0.5f,  0.5f,  0.66f, 0.0f, // negro 9

    // derecha
     0.5f,  0.5f,  0.5f,  0.66f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.99f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.99f, 0.33f,
     0.5f, -0.5f, -0.5f,  0.99f, 0.33f,
     0.5f, -0.5f,  0.5f,  0.66f, 0.33f,
     0.5f,  0.5f,  0.5f,  0.66f, 0.0f, // rojo 4

     // abajo
    -0.5f, -0.5f, -0.5f,  0.66f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.99f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.99f, 0.33f,
     0.5f, -0.5f,  0.5f,  0.99f, 0.33f,
    -0.5f, -0.5f,  0.5f,  0.66f, 0.33f,
    -0.5f, -0.5f, -0.5f,  0.66f, 0.0f, // morado 5

    // arriba
    -0.5f,  0.5f, -0.5f,  0.66f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.99f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.99f, 0.33f,
     0.5f,  0.5f,  0.5f,  0.99f, 0.33f,
    -0.5f,  0.5f,  0.5f,  0.66f, 0.33f,
    -0.5f,  0.5f, -0.5f,  0.66f, 0.0f, // celeste 6
};



glm::vec3 cubePositions[] = {

    // cara derecha 
    glm::vec3(1.0f,  1.0f,  1.0f), //derecha, arriba , alfrente
    glm::vec3(1.0f,  1.0f,  0.0f), //derecha, arriba , quiet
    glm::vec3(1.0f,  1.0f, -1.0f), //derecha, arriba , atras
    glm::vec3(1.0f,  0.0f,  1.0f), //derecha, quiet  , alfrente
    glm::vec3(1.0f,  0.0f,  0.0f), //derecha , quiet, quiet
    glm::vec3(1.0f,  0.0f, -1.0f), //derecha, quiet, atras
    glm::vec3(1.0f, -1.0f,  1.0f), //derecha, abajo, alfrente
    glm::vec3(1.0f, -1.0f,  0.0f), //derecha, abajo, quiet
    glm::vec3(1.0f, -1.0f, -1.0f), //derecha, abaajo, atras

    //cara centro vertical
    glm::vec3(0.0f,  1.0f,  1.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
    glm::vec3(0.0f,  1.0f, -1.0f),
    glm::vec3(0.0f,  0.0f,  1.0f),
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(0.0f,  0.0f, -1.0f),
    glm::vec3(0.0f, -1.0f,  1.0f),
    glm::vec3(0.0f, -1.0f,  0.0f),
    glm::vec3(0.0f, -1.0f, -1.0f),

    //cara izquierda
    glm::vec3(-1.0f,  1.0f,  1.0f),
    glm::vec3(-1.0f,  1.0f,  0.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f,  0.0f,  1.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3(-1.0f, -1.0f,  0.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f)
};

float colores[] = {
    0.0f,0.0f,0.33f,0.0f,0.33f,0.33f,0.33f,0.33f,0.0f,0.33f,0.0f,0.0f,          //verde
    0.66f,0.66f,0.99f,0.66f,0.99f,0.99f,0.99f,0.99f,0.66f,0.99f,0.66f,0.66f,    //naranja
    0.66f,0.0f,0.99f,0.0f,0.99f,0.33f,0.99f,0.33f,0.66f,0.33f,0.66f,0.0f,       //negro
    0.0f,0.33f,0.33f,0.33f,0.33f,0.66f,0.33f,0.66f,0.0f,0.66f,0.0f,0.33f,       //rojo
    0.33f,0.33f,0.66f,0.33f,0.66f,0.66f,0.66f,0.66f,0.33f,0.66f,0.33f,0.33f,    //morado
    0.66f,0.33f,0.99f,0.33f,0.99f,0.66f,0.99f,0.66f,0.66f,0.66f,0.66f,0.33f,    //celeste
    0.0f,0.66f,0.33f,0.66f,0.33f,0.99f,0.33f,0.99f,0.0f,0.99f,0.0f,0.66f        //blanco
};

/*
Colores:
    0 verde
    1 naranja
    2 negro
    3 rojo
    4 morado
    5 celeste
    6 blanco */
int coloresCubos[] = {
    2,0,2,3,2,4,
    2,2,2,3,2,4,
    6,2,2,3,2,4,
    2,0,2,3,2,2,
    2,2,2,3,2,2,
    6,2,2,3,2,2,
    2,0,2,3,5,2,
    2,2,2,3,5,2,
    6,2,2,3,5,2,

    2,0,2,2,2,4,
    2,2,2,2,2,4,
    6,2,2,2,2,4,
    2,0,2,2,2,2,
    2,2,2,2,2,2,
    6,2,2,2,2,2,
    2,0,2,2,5,2,
    2,2,2,2,5,2,
    6,2,2,2,5,2,

    2,0,1,2,2,4,
    2,2,1,2,2,4,
    6,2,1,2,2,4,
    2,0,1,2,2,2,
    2,2,1,2,2,2,
    6,2,1,2,2,2,
    2,0,1,2,5,2,
    2,2,1,2,5,2,
    6,2,1,2,5,2
};
#endif
// Inclusion de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicion de los estados de la maquina de estados
typedef enum States{
    LEER_ARCHIVOS,
    LOG_IN,
    MENU_PRINCIPAL,
    VER_PROYECTOS,
    COMMIT,
    REVERT,
    PULL,
    STATUS,
    CREAR_PROYECTO,
    CREAR_USUARIO,
    SALIR,
    STATE_NUM
} States;

// Estructura que contendra etiqueta y funcion
typedef struct StateMachine{
    States State;
    void (*funcion)(States* State);
}StateMachine;

//prototipos de funciones
void Inicio(States *State);
void LogIn(States *State);
void MenuPrincipal(States *State);
void VerProyectos(States *State);
void Commit(States *State);
void Revert(States *State);
void Pull(States *State);
void Status(States *State);
void CrearProyecto(States *State);
void CrearUsuario(States *State);
void Salir(States *State);

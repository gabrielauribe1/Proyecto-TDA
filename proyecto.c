// Inclusipn de bibliotecas
#include "maquina_de_estado.h"
#include<stdio.h>
#include<string.h>
#include<stdilb.h>

//#AlanWasHere
typedef struct def_Usuarios{
  char usuario[20], contra[20];
  struct def_Usuarios *sig;
}tipousuarios;

typedef struct def_UsuProyecto{
  char nproyecto[20], usuario[20];
  struct def_UsuProyecto *sig;
}tipouproyecto;

typedef struct def_MasterBranch{
  char nproyecto[20], ncommit[20];
  struct def_MasterBranch *sig;
}tipomasterb;

typedef struct def_Commit{
  int numcom;
  char ncommit[20], fecha[20], usuario[20], nproyecto[20];
  struct def_Commit *sig;
}tipocommit;

int main(void){
    system("clear");
    States MachineState=LOG_IN;
    //maquina de estados con sus respectivas funciones
    StateMachine Machine[] = {
        {LOG_IN, LogIn},
        {MENU_PRINCIPAL, MenuPrincipal},
        {VER_PROYECTOS, VerProyectos},
        {COMMIT, Commit},
        {REVERT, Revert},
        {PULL, Pull},
        {STATUS, Status},
        {CREAR_PROYECTO, CrearProyecto},
        {CREAR_USUARIO, CrearUsuario},
        {SALIR, Salir}
    };

    //bucle infinito de la maquina de estados
    for(;;){
        if(MachineState > STATE_NUM){
            puts("Ocurrio un error");
            exit(0);
        }else{
                (*Machine[MachineState].funcion)(&MachineState);
        }
    }

    return 0;
}

//Menu
void LogIn(States* State){
    char usuario[50],contrasena[50];
    puts("Introduzca su nombre de usuario: ");
    scanf("%s", usuario);
    puts("Introduzca su contraseña: ");
    scanf("%s", contrasena);
    *State=MENU_PRINCIPAL;
}

void MenuPrincipal(States *State){
  system("clear");
  int Opcion;
  puts("1. Ver proyectos");
  puts("2. Crear proyectos");
  puts("3. Crear usuario");
  puts("4. Salir");
  scanf("%d", &Opcion);

    switch(Opcion){
        case 1:
            *State = VER_PROYECTOS;
            break;
        case 2:
            *State = CREAR_PROYECTO;
            break;
        case 3:
            *State = CREAR_USUARIO;
            break;
        case 4:
            *State = SALIR;
            break;
        default:
            puts("Opcion invalida");
    }
}

void VerProyectos(States *State){
  system("clear");
  int Opcion;
  puts("Los proyectos disponibles son los siguientes, seleccione alguno: ");
  puts("(Se selecciona alguno)");

  puts("1. Commit");
  puts("2. Revert");
  puts("3. Pull");
  puts("4. Status");
  puts("5. Regresar menu anterior");
  scanf("%d", &Opcion);

    switch(Opcion){
        case 1:
            *State = COMMIT;
            break;
        case 2:
            *State = REVERT;
            break;
        case 3:
            *State = PULL;
            break;
        case 4:
            *State = STATUS;
            break;
        case 5:
            *State = MENU_PRINCIPAL;
            break;
        default:
            puts("Opcion invalida");
    }
}

void Commit(States *State){
  *State = MENU_PRINCIPAL;
}

void Revert(States *State){
  *State = MENU_PRINCIPAL;
}

void Pull(States *State){
  *State = MENU_PRINCIPAL;
}

void Status(States *State){
  *State = MENU_PRINCIPAL;
}

void CrearProyecto(States *State){
  *State=MENU_PRINCIPAL;
}

void CrearUsuario(States *State){
  *State=MENU_PRINCIPAL;
}

void Salir(States *State){
  exit(0);
}

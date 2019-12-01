// Inclusipn de bibliotecas
#include "maquinas_de_estado.h"
#include<stdio.h>
#include<string.h>

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
  char nproyecto[20], ncommit[100];
  struct def_MasterBranch *sig;
}tipomasterb;

typedef struct def_Commit{
  int numcom,pull,lineas[100];
  char ncommit[100], fecha[20], usuario[20], nproyecto[20];
  struct def_Commit *sig;
}tipocommit;

tipousuarios *iniciousr=NULL;
tipocommit *iniciocom=NULL;
tipomasterb *iniciomb=NULL;
tipouproyecto *iniciousrpro=NULL;
char usractual [20], proyectoElegido[20][20];


int main(void){
    system("clear");
    States MachineState=LEER_ARCHIVOS;
    //maquina de estados con sus respectivas funciones
    StateMachine Machine[] = {
        {LEER_ARCHIVOS, LeerArch},
        {LOG_IN, LogIn},
        {MENU_PRINCIPAL, MenuPrincipal},
        {VER_PROYECTOS, VerProyectos},
        {COMMIT, Commit},
        {REVERT, Revert},
        {PULL, Pull},
        {STATUS, Status},
        {CREAR_PROYECTO, CrearProyecto},
        {CREAR_USUARIO, CrearUsuario},
	{ESCRIBIR, escribir},
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

void LeerArch(States* State){
  char string[101];
  tipousuarios *temp,*temp2;
  tipouproyecto *temp3, *temp4;
  tipomasterb *temp5, *temp6;
  tipocommit *temp7, *temp8;
  FILE *archivo;

  //Se leen todos los USUARIOS
  archivo=fopen("usuarios.txt","rt");
  if(archivo!=NULL){
    while(fgets(string,19,archivo)!=NULL){
       temp=(tipousuarios*)malloc(sizeof(tipousuarios));
      strcpy(temp->usuario,string);
      temp->usuario[strlen(temp->usuario)-1]='\0';
      fgets(string,19,archivo)!=NULL;
      strcpy(temp->contra,string);
      temp->contra[strlen(temp->contra)-1]='\0';
      if(iniciousr!=NULL){
        temp2= iniciousr;
        while(temp2->sig!=NULL)
          temp2=temp2->sig;
        temp2->sig=temp;
      }
      else
        iniciousr=temp;
    }
     fclose(archivo);
  }


  //Se lee la relacion entre USUARIOS Y PROYECTOS
  archivo = fopen("proyecto.txt", "rt");

  if(archivo!=NULL)
    {
      while(fgets(string,19,archivo)!=NULL){
	temp3=(tipouproyecto*)malloc(sizeof(tipouproyecto));
	strcpy(temp3->usuario,string);
	temp3->usuario[strlen(temp3->usuario)-1]='\0';
	fgets(string,19,archivo)!=NULL;
	strcpy(temp3->nproyecto,string);
	temp3->nproyecto[strlen(temp3->nproyecto)-1]='\0';
	if(iniciousrpro!=NULL){
	  temp4=iniciousrpro;
	  while(temp4->sig!=NULL)
	    temp4=temp4->sig;
	  temp4->sig=temp3;
	}
	else
	  iniciousrpro=temp3;
      }
      fclose(archivo);
    }


   //Se leen los commits de los MASTER B
  archivo = fopen("masterbranch.txt", "rt");
  if(archivo!=NULL)
    {
      while(fgets(string,99,archivo)!=NULL){
	temp5=(tipomasterb*)malloc(sizeof(tipomasterb));
	strcpy(temp5->ncommit,string);
	temp5->ncommit[strlen(temp5->ncommit)-1]='\0';
	fgets(string,19,archivo)!=NULL;
	strcpy(temp5->nproyecto,string);
	temp5->nproyecto[strlen(temp5->nproyecto)-1]='\0';
	if(iniciomb!=NULL){
	  temp6=iniciomb;
	  while(temp6->sig!=NULL)
	    temp6=temp6->sig;
	  temp6->sig=temp5;
	}
	else
	  iniciomb=temp5;
      }
      fclose(archivo);
    }

  //Se leen todos los COMMITS
  archivo = fopen("commit.txt", "rt");
  if(archivo!=NULL)
    {
      while(fgets(string,99,archivo)!=NULL){
	temp7=(tipocommit*)malloc(sizeof(tipocommit));
	strcpy(temp7->ncommit,string);
	temp7->ncommit[strlen(temp7->ncommit)-1]='\0';

	fgets(string,19,archivo);
	strcpy(temp7->nproyecto,string);
	temp7->nproyecto[strlen(temp7->nproyecto)-1]='\0';

	fgets(string,19,archivo);
	strcpy(temp7->fecha,string);
	temp7->fecha[strlen(temp7->fecha)-1]='\0';

	fgets(string,19,archivo);
	strcpy(temp7->usuario,string);
	temp7->usuario[strlen(temp7->usuario)-1]='\0';

	fscanf(archivo, "%i\n", &temp7->numcom);

	if(iniciocom!=NULL){
	  temp8=iniciocom;
	  while(temp8->sig!=NULL)
	    temp8=temp7->sig;
	  temp8->sig=temp7;
	}
	else
	  iniciocom=temp7;
      }
      fclose(archivo);
    }
  *State=LOG_IN;
}

//Menu
void LogIn(States* State){
    char usuario[50],contrasena[50];
    tipousuarios *temp;
    temp=iniciousr;
    puts("Introduzca su nombre de usuario: ");
    scanf("%s", usuario);
    while(temp!=NULL && strcmp(usuario,temp->usuario)!=0)
      temp=temp->sig;
    if(temp!=NULL){
      puts("Introduzca su contraseña: ");
      __fpurge(stdin);
      scanf("%s", contrasena);
      if(strcmp(contrasena,temp->contra)==0){
	strcpy(usractual, usuario);
	*State=MENU_PRINCIPAL;
      }
      else
        *State=LOG_IN;
    }
    else{
      puts("El usuario no existe");
      *State=LOG_IN;
    }
}

void MenuPrincipal(States *State){
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
            *State = ESCRIBIR;
            break;
        default:
            puts("Opcion invalida");
    }
}

void VerProyectos(States *State){
  int Opcion,i=0,c=0;
  tipouproyecto *busca,*busca2;
  busca=iniciousrpro;
  if (busca==NULL) {
    puts("no hay proyectos");
  }
  else{
    puts("Los proyectos disponibles son los siguientes: ");
    while(busca!=NULL){
      i++;
      if(strcmp(busca->usuario,usractual)==0){
        printf("%d. %s\n", i, busca->nproyecto);
        strcpy(proyectoElegido[i],busca->nproyecto);
    }
      else i--;
      busca=busca->sig;
    }
    puts("\n");
  }
  puts("Elija uno de los proyectos desplegados: ");
  scanf("%d", &Opcion);
  printf("%s\n", proyectoElegido[Opcion]);//el printf para ver que si escoge bien el proyecto

  puts("\n¿Que deseas hacer?");
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
  system("clear");
  tipouproyecto *busca,*busca3, *nuevousuario;
  tipousuarios *busca2;
  char nombre[20], nombreusu[20];
  int Nusuarios, i;
  puts("Cual es el nombre del proyecto? (max 19 caracteres)");
  __fpurge(stdin);
  gets(nombre);
  busca=iniciousrpro;
  while(busca!=NULL && strcmp(busca->nproyecto,nombre)!=0)
    busca=busca->sig;
  if(busca!=NULL){
    puts("Ese nombre ya esta en uso");
    *State=CREAR_PROYECTO;
  }
  else{
    puts("Cuantos usuarios van a participar en este proyecto?");
    scanf(" %d", &Nusuarios);
    i=0;
    nuevousuario=(tipouproyecto*)malloc(sizeof(tipouproyecto));
    strcpy(nuevousuario->usuario,usractual);
    strcpy(nuevousuario->nproyecto,nombre);
    nuevousuario->sig=NULL;
    if(iniciousrpro!=NULL)
      {
	busca3=iniciousrpro;
	while(busca3->sig!=NULL)
	  busca3=busca3->sig;
	busca3->sig=nuevousuario;
      }
    else
      iniciousrpro=nuevousuario;
    do
      {
	printf("Inserta el nombre del usuario %d:\n", i+1);
	__fpurge(stdin);
	gets(nombreusu);
	busca2=iniciousr;
	while(busca2!=NULL && strcmp(busca2->usuario,nombreusu)!=0)
	  busca2=busca2->sig;
	if(busca2!=NULL)
	    {
	    i++;
	    nuevousuario=(tipouproyecto*)malloc(sizeof(tipouproyecto));
	    strcpy(nuevousuario->usuario,nombreusu);
	    strcpy(nuevousuario->nproyecto,nombre);
	    nuevousuario->sig=NULL;
	    if(iniciousrpro!=NULL)
	      {
		busca3=iniciousrpro;
		while(busca3->sig!=NULL)
		  busca3=busca3->sig;
		busca3->sig=nuevousuario;
	      }
	    else
	      iniciousrpro=nuevousuario;
	  }
	else
	  {
	  puts("Ese usuario no existe, inserte uno que este dado de alta");
	  }
      }while(i<Nusuarios);

      }
    *State=MENU_PRINCIPAL;

}

void CrearUsuario(States *State){
  tipousuarios *nuevo,*busca;
  char nombre[20],passwrd[20];
  printf("Como se va a llamar el nuevo usuario (19 caracteres max)\n");
  __fpurge(stdin);
  gets(nombre);
  busca=iniciousr;
  while(busca!=NULL && strcmp(busca->usuario,nombre)!=0)
    busca=busca->sig;
  if(busca==NULL){
    printf("Cual va a hacer la contrasena(19 caracteres max)\n");
    __fpurge(stdin);
    gets(passwrd);
    nuevo=(tipousuarios*)malloc(sizeof(tipousuarios));
    strcpy(nuevo->usuario,nombre);
    strcpy(nuevo->contra,passwrd);
    nuevo->sig=NULL;
    if(iniciousr!=NULL){
      busca=iniciousr;
      while(busca->sig!=NULL)
	busca=busca->sig;
      busca->sig=nuevo;
    }
    else
      iniciousr=nuevo;
    *State=MENU_PRINCIPAL;
  }
  else{
    puts("Ese usuario ya existe");
    *State=CREAR_USUARIO;
  }
}

void escribir(States *State){
  FILE* archivo;
  tipousuarios *usuarios;
  tipouproyecto *proyecto;
  tipomasterb *master;
  tipocommit *commit;
  archivo=fopen("usuarios.txt","wt");
  usuarios=iniciousr;
  while(usuarios!=NULL){
    fputs(usuarios->usuario,archivo);
    fputs("\n",archivo);
    fputs(usuarios->contra,archivo);
    fputs("\n",archivo);
    usuarios=usuarios->sig;
  }
  fclose(archivo);

  archivo=fopen("proyecto.txt","wt");
  proyecto=iniciousrpro;
  while(proyecto!=NULL){
    fputs(proyecto->usuario,archivo);
    fputs("\n",archivo);
    fputs(proyecto->nproyecto,archivo);
    fputs("\n",archivo);
    proyecto=proyecto->sig;
  }
  fclose(archivo);

  archivo=fopen("masterbranch.txt","wt");
  master=iniciomb;
  while(master!=NULL){
    fputs(master->ncommit,archivo);
    fputs("\n",archivo);
    fputs(master->nproyecto,archivo);
    fputs("\n",archivo);
    master=master->sig;
  }
  fclose(archivo);

  archivo=fopen("commit.txt","wt");
  commit=iniciocom;
  while(commit!=NULL){
    fputs(commit->ncommit,archivo);
    fputs("\n",archivo);
    fputs(commit->nproyecto,archivo);
    fputs("\n",archivo);
    fputs(commit->fecha,archivo);
    fputs("\n",archivo);
    fputs(commit->usuario,archivo);
    fputs("\n",archivo);
    fprintf(archivo,"%d", commit->numcom);
    fputs("\n",archivo);
    commit=commit->sig;
  }
  fclose(archivo);

  *State=SALIR;
}

void Salir(States *State){
 tipousuarios *borra;
 tipouproyecto *proyecto;
 tipomasterb *master;
 tipocommit *commit;
 borra=iniciousr;
 while(borra!=NULL){
   iniciousr=iniciousr->sig;
   free(borra);
   borra=iniciousr;
 }
 proyecto=iniciousrpro;
 while(proyecto!=NULL){
   iniciousrpro=iniciousrpro->sig;
   free(proyecto);
   proyecto=iniciousrpro;
 }
 master=iniciomb;
 while(master!=NULL){
   iniciomb=iniciomb->sig;
   free(master);
   master=iniciomb;
 }
 commit=iniciocom;
 while(commit!=NULL){
   iniciocom=iniciocom->sig;
   free(commit);
   commit=iniciocom;
 }

 exit(0);
}

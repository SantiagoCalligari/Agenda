#include <stdio.h>
#include <stdlib.h>
#include <string.h>


////////////////////////////////////////////////////
//INTEGRANTES: SANTIAGO CALLIGARI, IGNACIO ZULIANI//
////////////////////////////////////////////////////
#define MAXIMO 256
typedef struct {
char *nombre, *direccion, *telefono, *mail , *aliasTelegram, *usuarioInstagram;
} Contacto;

typedef struct _Snodo{
    Contacto datos;
    struct _Snodo *sig;
} Snodo;


void clear()
{
  //Funcion para limpiar un poco la pantalla.
    int i = 0;
    while(i != 20)
    {
        printf("\n");
        i++;
    }

}


void dato(char *punt)
{
    //Almacena en el puntero del tipo char el dato.
    getchar();
    scanf("%[^\n]",punt);
    getchar();
    
}


void muestraContactos(Snodo*agenda)
{
    clear();
    //uso nodo auxiliar para comenzar a recorrer la agenda
    Snodo* nodo = agenda;
    if(agenda == NULL)
    {
        //si agenda esta vacia imprime esto y corta el codigo.
        printf("Su agenda esta vacia. Para añadir un contacto");
        printf(" ingrese la opcion 1 en el menu siguiente: \n");
    }

    while(nodo != NULL)
    {
            printf("\nNombre: %s\n",nodo->datos.nombre);
            printf("Direccion: %s\n",nodo->datos.direccion);
            printf("Telefono: %s\n",nodo->datos.telefono);
            printf("Mail: %s\n",nodo->datos.mail);
            printf("Telegram: %s\n",nodo->datos.aliasTelegram);
            printf("Instagram: %s\n\n",nodo->datos.usuarioInstagram);
        nodo = nodo -> sig;
    }
}



void pedirDatos(Snodo* NuevoNodo){                             //Funcion para rellenar un nuevo nodo.
  //limpio el buffer.
    getchar();
  //vamos rellenando uno por uno los datos alojandolos con malloc y asignandolos con scanf
    printf("Ingresa el nombre:\n");
    scanf("%[^\n]",NuevoNodo->datos.nombre);
    getchar();
    printf("Ingresa la direccion:\n");
    scanf("%[^\n]",NuevoNodo->datos.direccion);
    getchar();
    printf("Ingresa el telefono:\n");
    scanf("%[^\n]",NuevoNodo->datos.telefono);
    getchar();
    printf("Ingresa el mail:\n");
    scanf("%[^\n]",NuevoNodo->datos.mail);
    getchar();
    printf("Ingresa el AliasTelegram:\n");
    scanf("%[^\n]",NuevoNodo->datos.aliasTelegram);
    getchar();
    printf("Ingresa el nombre de insta pa :\n");
    scanf("%[^\n]",NuevoNodo->datos.usuarioInstagram);
    getchar();
    clear();
}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
 //usamos una lista simple que agrega al inicio porque no veiamos necesidad de utilizar nada más complejo//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Snodo* nuevoContacto(Snodo* agenda, int loadOrNew)                     
{   //pido un lugar para un nodo nuevo                  
    Snodo* nuevoNodo = malloc(sizeof(Snodo));
    nuevoNodo->sig = agenda;
    nuevoNodo->datos.nombre = malloc(sizeof(char)*50);
    nuevoNodo->datos.usuarioInstagram = malloc(sizeof(char)*50);
    nuevoNodo->datos.aliasTelegram = malloc(sizeof(char)*50);
    nuevoNodo->datos.mail = malloc(sizeof(char)*50);
    nuevoNodo->datos.telefono = malloc(sizeof(char)*50);
    nuevoNodo->datos.direccion = malloc(sizeof(char)*50);
    if(loadOrNew == 2)
    {
    pedirDatos(nuevoNodo);
    }
    clear();
    return nuevoNodo;
    //devuelvo el nodo que apunta al anterior inicio de agenda
}

int menu(){
    //Muestra las posibles opciones en el menu y devuelve la elegida.
    int opcion;
    printf("1.Agregar un nuevo Contacto\n");
    printf("2.Mostrar Contactos\n");
    printf("3.Buscar Contacto por Nombre\n");
    printf("4.Buscar Contacto por Telefono\n");
    printf("5.Eliminar Contacto Por nombre\n");
    printf("6.Eliminar todo\n");
    printf("7.Salir\n Que desea hacer?: ");
    scanf("%d",&opcion);
    clear();
    return opcion;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////█▀ ▄▀█ █░█ █▀▀   ▄▀█ █▄░█ █▀▄   █░░ █▀█ ▄▀█ █▀▄////////////////////////////
///////////////////////▄█ █▀█ ▀▄▀ ██▄   █▀█ █░▀█ █▄▀   █▄▄ █▄█ █▀█ █▄▀////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


void save(Snodo *agenda)
{
    FILE* save;
    save = fopen("save.txt", "w");
    Snodo* nodo = agenda;
    while(nodo != NULL)
        {
            fprintf(save, "%s,",nodo->datos.nombre);
            fprintf(save, "%s,",nodo->datos.direccion);
            fprintf(save, "%s,",nodo->datos.telefono);
            fprintf(save, "%s,",nodo->datos.mail);
            fprintf(save, "%s,",nodo->datos.aliasTelegram);
            fprintf(save, "%s\n",nodo->datos.usuarioInstagram);
            nodo = nodo -> sig;
        }
    fclose(save);
}


Snodo* loader(Snodo*agenda, char str[])
{                                           // loadeo todo. cuando termina tengo esta struct apuntando a un NULL
    //agenda->datos.nombre = malloc(sizeof(char)*50);
    //strcpy(strtok(str, ","),agenda->datos.nombre);
    strcpy(agenda->datos.nombre,strtok(str, ","));                               //NO MALLOCQUEAS LAS STR
    strcpy(agenda->datos.direccion,strtok(NULL, ","));                      //Esto me genera dolor.
    strcpy(agenda->datos.telefono,strtok(NULL, ","));
    strcpy(agenda->datos.mail,strtok(NULL, ","));
    strcpy(agenda->datos.aliasTelegram,strtok(NULL, ","));
    strcpy(agenda->datos.usuarioInstagram,strtok(NULL, ","));
    return agenda;
}


Snodo* contador(Snodo *agenda)
{
    FILE* line2mat;
    char temp[300],c;
    line2mat = fopen("save.txt","r");
    if(line2mat==NULL)
        exit(0);                //si save esta vacio no me voy.
    while(fscanf(line2mat, "%[^\n]\n", temp) != EOF)
    {
        
        agenda = nuevoContacto(agenda,1);

        agenda = loader(agenda,temp); 
    }
    fclose(line2mat);
    return agenda;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void mostrarBusqueda(Contacto Muestra)
{
    //Limpia un poco la pantalla y luego imprime los datos encontrados del contacto.
    clear();
    printf("\nNombre: %s\n",Muestra.nombre);
    printf("Direccion: %s\n",Muestra.direccion);
    printf("Telefono: %s\n",Muestra.telefono);
    printf("Mail: %s\n",Muestra.mail);
    printf("Telegram: %s\n",Muestra.aliasTelegram);
    printf("Instagram: %s\n\n",Muestra.usuarioInstagram);
}


void buscaContactosNombre(Snodo*agenda, char *nombre)
{
    //aux se usa para evitar algunos errores de codigo .
   //flag es usada para saber si el contacto existe.
    int aux,flag=0;
    Snodo* nodo = agenda;
    while(nodo != NULL) 
    {
        //gracias a esto puedo recorrer la agenda.
        aux = strcmp(nombre, nodo->datos.nombre);
        if(aux==0)
        {
            mostrarBusqueda(nodo->datos);
            flag = 1;
            //si son iguales recorro la agenda y le digo a flag que hay al menos una coincidencia
        }
        
        nodo = nodo -> sig; //Cambio de nodo al siguiente.
    }

    if(agenda == NULL)
    {
        //si la agenda esta vacia, pido que ingrese algun contacto antes.
        printf("Su agenda esta vacia, le pedimos que no busque un contacto si no tiene ");
        printf("ninguno añadido. Para añadir un contacto ingrese la opcion 1 en el menu siguiente: \n");
    }
    else
    {
        if(flag == 0)
        {
            // si la agenda no esta vacia y flag es 0, entonces no esta el contacto.
            printf("Su pedido no está en nuestra agenda\n");
        }

    }

}



void buscarContactosTelefono(Snodo *agenda,char *numero)
{
    //aux se usa para evitar algunos errores de codigo .
   //flag es usada para saber si el contacto existe.
    int aux, flag = 0;
    Snodo *nodo = agenda;
    while(nodo != NULL)
    {
        //gracias a esto puedo recorrer la agenda.
        aux = strcmp(numero, nodo->datos.telefono);
        if(aux==0)
        {
            mostrarBusqueda(nodo->datos);
            flag = 1;
            //si son iguales recorro la agenda y le digo a flag que hay al menos una coincidencia
        }

        nodo = nodo->sig; //Cambio de nodo al siguiente.
    }

    if(agenda == NULL)
    {
        //si la agenda esta vacia, pido que ingrese algun contacto antes.
        printf("Su agenda esta vacia, le pedimos que no busque un contacto si no tiene ninguno añadido. Para añadir un contacto ingrese la opcion 1 en el menu siguiente: \n");
    }
    else
    {
        if(flag == 0)
        {
            // si la agenda no esta vacia y flag es 0, entonces no esta el contacto.
            printf("Su pedido no está en nuestra agenda\n");
        }

    }

}

void liberarDato(Contacto datos)
{
    //Limpia los datos del nodo que almacena el contactoa eliminar.
        free(datos.nombre);
        free(datos.direccion);
        free(datos.telefono);
        free(datos.mail);
        free(datos.aliasTelegram);
        free(datos.usuarioInstagram);
}


Snodo* eliminarContactoNombre(Snodo* agenda, char *nombre)
{
    int seguir = 1, flag = 0;
    char confirmacion;
    /*  
        antecesor es un nodo que siempre apunta al que apuntó nodo en la iteracion anterior.
        En el caso de una lista que sea -> 1 2 3 NULL cuando nodo este apuntando a 3, antecesor va a apuntar a 2.
        la primer iteracion son los dos iguales al puntero a 1.
        la segunda iteracion antecesor es igual al puntero a 1 y nodo es igual al nodo 1
        asi podemos eliminar un nodo cambiando el sig de antecesor al siguiente de nodo, saltandonos nodo en medio.
    */
    Snodo *nodo,*antecesor;
    nodo = malloc(sizeof(Snodo));
    antecesor = malloc(sizeof(Snodo));
    nodo = agenda;
    antecesor = agenda; 
    while(nodo != NULL && seguir)
    {   
        //por cada iteracion pregunto si nombre es igual al nombre del nodo.
        if(strcmp(nombre, nodo->datos.nombre)==0)
        {
            //caso correcto, flag se vuelve 1 porque existe el contacto.
            flag = 1;
            printf("Confirma que quiere eliminar el contacto: %s [S/n]", nodo->datos.nombre);
            dato(&confirmacion);
            if(confirmacion != 'n')
            {
                printf("Contacto eliminado.");
                liberarDato(nodo->datos); 
                //libero todos los valores de datos.
                if(nodo != agenda)
                {
                    //con esto nos saltamos  un nodo
                    antecesor->sig = nodo->sig;
                    seguir = 0;
                }
                free(nodo->sig);
                free(nodo);
                //libero el puntero del nodo a borrar
                // y libero el nodo en total
            }
            else
            {
                printf("Accion cancelada");
                seguir = 0;
                //cuando no nos confiman la accion, no ejecutamos nada
            }

        }
        //aqui ponemos en practica lo que explique antes acerca del antecesor que va detras del nodo.
        if(nodo != agenda)
        {
            antecesor = antecesor->sig;
        }
        // con esta sentencia nos movemos uno para delante en la lista.
        nodo = nodo->sig;
    }

    if(flag != 1)
    {
        //Notifica que el contacto que se quiere eliminar no existe.
        printf("El contacto que quieres eliminar no existe.\n");
    }
    
    return agenda;
}


Snodo* eliminarTodosContactos(Snodo *agenda)
{
    //recorremos toda la lista y liberamos todo.
    Snodo *temp;
    while(agenda != NULL)
    {   
        //apunto al siguiente elemento en temp
        temp = agenda->sig;
        //libero el actual
        liberarDato(agenda->datos);
        free(agenda);
        //  apunto al siguiente elemento con agenda
        agenda = temp;
    }
    return agenda;
}


int main()
{
    Snodo* agenda = NULL;
    char buffer[MAXIMO];
    char confirmacion;
    int opcion;
    agenda = contador(agenda);
    while(opcion != 7)
    {
        opcion = menu();
        switch(opcion)
        {
            case 1:
                agenda = nuevoContacto(agenda,2);
                break;
            case 2:
                muestraContactos(agenda);
                printf("Desea continuar? [S/n]");
                dato(&confirmacion);
                if(confirmacion == 'n')
                {
                    opcion = 7;
                }
                clear();
                break;
            case 3: 
                printf("Ingrese el nombre del contacto que quiere buscar: ");
                dato(buffer);
                buscaContactosNombre(agenda, buffer);
                printf("\nDesea continuar? [S/n]");
                dato(&confirmacion);
                if(confirmacion == 'n')
                {
                    opcion = 7;
                }
                clear();
                break;
            case 4: 
                printf("Ingrese el numero telefonico del contacto que quiere buscar: ");
                dato(buffer);
                buscarContactosTelefono(agenda, buffer);
                printf("Desea continuar? [S/n]");
                dato(&confirmacion);
                if(confirmacion == 'n')
                {
                    opcion = 7;
                }
                clear();
                break;
            case 5: 
                printf("Ingrese el nombre del contacto que quiere eliminar: ");
                dato(buffer);
                agenda = eliminarContactoNombre(agenda,buffer);
                printf("Desea continuar? [S/n]");
                dato(&confirmacion);
                if(confirmacion == 'n')
                {
                    opcion = 7;
                }
                clear();
                break;
            case 6: 
                agenda = eliminarTodosContactos(agenda);
                printf("Desea continuar? [S/n]");
                dato(&confirmacion);
                if(confirmacion == 'n')
                {
                    opcion = 7;
                }
                free(agenda);
                clear();
                break;
            case 7: 
                /*
                system("pause");*/
                break;
            default:
                opcion = 0;
                printf("\nLa opcion ingresada no es valida, vuelva a ingresar: \n");
                opcion = menu();
                break;
        }
    }
    //save(agenda);
    agenda = eliminarTodosContactos(agenda);
    free(agenda);
    return 0;
}
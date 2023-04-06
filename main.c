#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "list.h"

#define MAXCHAR 31

typedef struct{
    char nombre[MAXCHAR];
    char apellido[MAXCHAR];
    int edad;
    char telefono[MAXCHAR];
    char direccion[MAXCHAR];
    char num_seguridad_social[MAXCHAR];
    List* medicosAsignados;
}Paciente;

typedef struct{
    char nombreMedico[MAXCHAR];
}Medico;

void mostrarMenu()
{
    puts("========================================");
    puts("          Control de Pacientes");
    puts("========================================");
   
    puts("1) Registrar Paciente.");
    puts("2) Mostrar Datos Paciente.");
    puts("3) Eliminar Paciente.");
    puts("4) Mostrar todos los Pacientes.");
    puts("5) Mostrar Pacientes sin medicos.");
    puts("6) Asignar medico.");
    puts("7) Desasignar medico.");
    puts("8) Importar Pacientes desde csv.");
    puts("9) Exportar Pacientes a csv.");
    puts("10) Salir.");
}

char* quitar_tildes(char* cadena)
{
    const char *originales = "áéíóúÁÉÍÓÚ";
    const char *reemplazos = "aeiouAEIOU";
    char* nueva_cadena = (char*) malloc(strlen(cadena) + 1);

    if (nueva_cadena == NULL) {
        return NULL;
    }

    int j = 0;

    for(int i = 0; cadena[i] != '\0'; i++)
    {
        bool conTilde = false;
        bool flag = false;

        for(int k = 0; originales[k] != '\0'; k++)
        {
            if(cadena[i] == originales[k])
            {
                if(!flag)
                {
                    i++;
                }
                else
                {
                    conTilde = true;
                    nueva_cadena[j++] = reemplazos[k/2];
                    break;
                }

                flag = true;
            }
        }

        if(!conTilde)
        {
            nueva_cadena[j++] = cadena[i];
        }
    }

    nueva_cadena[j] = '\0';
    return nueva_cadena;
}

void registrarPaciente(List* listaPacientes, char* nombreAux, char* apellidoAux, int edadAux, char* telefonoAux, char* direccionAux, char* num_seguridad_socialAux, List * medicosIngresados, int opcion)
{
    Paciente* p = (Paciente*) malloc(sizeof(Paciente));
    Paciente* pacienteActual = firstList(listaPacientes);

    if(opcion == 1)
    {
        while(pacienteActual != NULL)
        {
            if(strcmp(pacienteActual->num_seguridad_social, num_seguridad_socialAux) == 0)
            {
                system("cls");

                puts("==============================================");
                puts("      El Paciente ya esta registrado.");
                puts("==============================================");

                sleep(2);
                return;
            }

            pacienteActual = nextList(listaPacientes);
        }
        
        strcpy(p->nombre, nombreAux);
        strcpy(p->apellido, apellidoAux);
        p->edad = edadAux;
        strcpy(p->telefono, telefonoAux);
        strcpy(p->direccion, direccionAux);
        strcpy(p->num_seguridad_social, num_seguridad_socialAux);
        p->medicosAsignados = medicosIngresados;

        pushBack(listaPacientes, p);

        system("cls");

        puts("==============================================");
        puts("   El Paciente se registro exitosamente.");
        puts("==============================================");

        sleep(2);
    }
    else
    {
        while(pacienteActual != NULL)
        {
            if(strcmp(pacienteActual->num_seguridad_social, num_seguridad_socialAux) == 0)
            {
                return;
            }

            pacienteActual = nextList(listaPacientes);
        }

        strcpy(p->nombre, nombreAux);
        strcpy(p->apellido, apellidoAux);
        p->edad = edadAux;
        strcpy(p->telefono, telefonoAux);
        strcpy(p->direccion, direccionAux);
        strcpy(p->num_seguridad_social, num_seguridad_socialAux);
        p->medicosAsignados = medicosIngresados;

        pushBack(listaPacientes, p);
    }
}

void registrarMedicos(List* medicosIngresados)
{
    int medicosAsignados;

    do{
        printf("\nCuantos Medicos desea asignar: ");

        while(scanf("%d", &medicosAsignados) != 1)
        {
            printf("\nEntrada invalida. Ingrese un numero entero: ");
            while(getchar() != '\n');
        }

        if(medicosAsignados <= 0)
        {
            printf("\nCantidad mal ingresada, intente nuevamente.\n");
        }

    }while(medicosAsignados <= 0);

    getchar();

    for(int i = 1; i <= medicosAsignados; i++)
    {   
        bool medicoRepetido = false;
        char medicoAuxiliar[MAXCHAR];
        
        printf("Ingrese medico %d: ", i);
        scanf("%30[^\n]s", &medicoAuxiliar);
        while(getchar() != '\n');

        Medico *medicoActual = firstList(medicosIngresados);
            
        while(medicoActual != NULL)
        {
            if(strcmp(medicoAuxiliar, medicoActual->nombreMedico) == 0)
            {   
                puts("========================================");
                printf("El/La %s ya esta asignado al paciente.\n", medicoAuxiliar);
                puts("========================================\n");
                medicoRepetido = true;
                i--;
                break;
            }
            
            medicoActual = nextList(medicosIngresados);
        }

        if(medicoRepetido == false)
        {
            Medico *med = (Medico *) malloc(sizeof(Medico));
            
            strcpy(med->nombreMedico, medicoAuxiliar);
            
            pushBack(medicosIngresados, med);

            puts("========================================");
            printf("%s agregado exitosamente.\n", medicoAuxiliar);
            puts("========================================");
            puts("");
            
        }
    }

    sleep(2);
    
}

void mostrarDatoPaciente(List* listaPacientes)
{
    char nombreABuscar[MAXCHAR];
    char apellidoABuscar[MAXCHAR];

    Paciente* pacienteActual = firstList(listaPacientes);

    if(pacienteActual == NULL)
    {
        puts("========================================");
        puts("  La Lista de Pacientes esta vacia.");
        puts("========================================\n");
        system("pause");
    }
    else
    {
        puts("========================================");
        puts(" Ingrese Datos de Paciente a Buscar:");
        puts("========================================");

        printf("Ingrese Nombre: ");
        scanf("%30[^\n]s", &nombreABuscar);
        while(getchar() != '\n');
        
        printf("Ingrese Apellido: ");
        scanf("%30[^\n]s", &apellidoABuscar);
        while(getchar() != '\n');

        while(pacienteActual != NULL)
        {
            if(strcmp(pacienteActual->nombre, nombreABuscar) == 0 && strcmp(pacienteActual->apellido, apellidoABuscar) == 0)
            {
                puts("");
                puts("========================================");
                puts("          Paciente Encontrado:");
                puts("========================================");
                puts("");

                printf("Nombre: %s\nApellido: %s\nEdad: %d\nTelefono: %s\nDireccion: %s\nNumero de Seguridad Social: %s\n\n", pacienteActual->nombre, pacienteActual->apellido, pacienteActual->edad, pacienteActual->telefono, pacienteActual->direccion, pacienteActual->num_seguridad_social);
                
                void* medicoActual = firstList(pacienteActual->medicosAsignados);

                if(medicoActual == NULL)
                {
                    printf("El Paciente no tiene Medicos Asignados.\n\n");
                }
                else
                {
                    puts("Medicos Asignados:");

                    while(medicoActual != NULL)
                    {
                        printf("- %s\n", medicoActual);

                        medicoActual = nextList(pacienteActual->medicosAsignados);
                    }
                }

                puts("");
                system("pause");
                return;
            }

            pacienteActual = nextList(listaPacientes);
        }

        puts("");
        puts("========================================");
        puts("          Paciente No Encontrado:");
        puts("========================================");
        puts("");

        system("pause");
    }
}

void eliminarPaciente(List * listaPacientes)
{
    Paciente *pacienteActual = firstList(listaPacientes);

    if(pacienteActual == NULL)
    {
        puts("========================================");
        puts("  La Lista de Pacientes esta vacia.");
        puts("========================================\n");
        system("pause");
        return;
    }

    char nombreABuscar[MAXCHAR];
    char apellidoABuscar[MAXCHAR];
    int cantMedicos;

    puts("===========================================");
    puts("Que paciente desea eliminar:");
    puts("===========================================");
    
    printf("Ingrese Nombre: ");
    scanf("%30[^\n]s", &nombreABuscar);
    while(getchar() != '\n');

    printf("Ingrese Apellido: ");
    scanf("%30[^\n]s", &apellidoABuscar);
    while(getchar() != '\n');

    while(pacienteActual != NULL)
    {
        if(strcmp(pacienteActual->nombre, nombreABuscar) == 0 && strcmp(pacienteActual->apellido, apellidoABuscar) == 0)
        {   
            popCurrent(listaPacientes);
            system("cls");
            puts("==============================================");
            puts("      Paciente eliminado exitosamente.");
            puts("==============================================");

            sleep(2);

            return;
        }
        pacienteActual = nextList(listaPacientes);
    }

    puts("");
    puts("========================================");
    puts("         Paciente No Encontrado:");
    puts("========================================");

    system("pause");

    
    return;
}

void mostrarTodosPacientes(List* listaPacientes)
{
    Paciente* pacienteActual = firstList(listaPacientes);
    int contador = 1;

    if(pacienteActual == NULL)
    {
        puts("========================================");
        puts("  La Lista de Pacientes esta vacia.");
        puts("========================================");
    }
    else
    {
        while(pacienteActual != NULL)
        {
            puts("========================================");
            printf("          Paciente %d:\n", contador);
            puts("========================================");
            printf("Nombre: %s\nApellido: %s\nEdad: %d\nTelefono: %s\nDireccion: %s\nNumero de Seguridad Social: %s\n", pacienteActual->nombre, pacienteActual->apellido, pacienteActual->edad, pacienteActual->telefono, pacienteActual->direccion, pacienteActual->num_seguridad_social);

            void* medicoActual = firstList(pacienteActual->medicosAsignados);

            if(medicoActual == NULL)
            {
                printf("\nEl Paciente no tiene Medicos Asignados.\n\n");
            }
            else
            {
                puts("Medicos Asignados:");

                while(medicoActual != NULL)
                {
                    printf("- %s\n", medicoActual);

                    medicoActual = nextList(pacienteActual->medicosAsignados);
                }
            }

            pacienteActual = nextList(listaPacientes);
            contador++;
        }
    }

    puts("");
    system("pause");
}

void pacientesSinMedicos(List* listaPacientes)
{
    Paciente* pacienteActual = firstList(listaPacientes);
    int contador = 1;
    bool pacientesSinMedicos = false;

    if(pacienteActual == NULL)
    {
        puts("========================================");
        puts("  La Lista de Pacientes esta vacia.");
        puts("========================================");
    }
    else
    {
        puts("========================================");
        printf("       Pacientes sin Medicos:\n");
        puts("========================================\n");

        while(pacienteActual != NULL)
        {
            void* medicoActual = firstList(pacienteActual->medicosAsignados);

            if(medicoActual == NULL)
            {
                puts("========================================");
                printf("          Paciente %d:\n", contador);
                puts("========================================");
                printf("Nombre: %s\nApellido: %s\nEdad: %d\nTelefono: %s\nDireccion: %s\nNumero de Seguridad Social: %s\n", pacienteActual->nombre, pacienteActual->apellido, pacienteActual->edad, pacienteActual->telefono, pacienteActual->direccion, pacienteActual->num_seguridad_social);

                pacientesSinMedicos = true;
            }
            
            pacienteActual = nextList(listaPacientes);
            contador++;
        }
    }

    if(!pacientesSinMedicos && contador > 1)
    {
        puts("===========================================================");
        puts(" Todos los pacientes tienen por lo menos 1 medico asignado.");
        puts("===========================================================");
    }

    puts("");
    system("pause");
}

void asignarMedico(List * listaPacientes)
{   
    Paciente* pacienteActual = firstList(listaPacientes);

    if(pacienteActual == NULL)
    {
        puts("========================================");
        puts("  La Lista de Pacientes esta vacia.");
        puts("========================================\n");
        system("pause");
        return;
    }

    char nombreABuscar[MAXCHAR];
    char apellidoABuscar[MAXCHAR];
    int cantMedicos;

    puts("===========================================");
    puts("A que Paciente le desea asignar un medico:");
    puts("===========================================");
    
    printf("Ingrese Nombre: ");
    scanf("%30[^\n]s", &nombreABuscar);
    while(getchar() != '\n');

    printf("Ingrese Apellido: ");
    scanf("%30[^\n]s", &apellidoABuscar);
    while(getchar() != '\n');

    while(pacienteActual != NULL)
    {
        if(strcmp(pacienteActual->nombre, nombreABuscar) == 0 && strcmp(pacienteActual->apellido, apellidoABuscar) == 0)
        {   
            registrarMedicos(pacienteActual->medicosAsignados);

            system("cls");
            puts("==============================================");
            puts("      Medicos asignados exitosamente.");
            puts("==============================================");

            sleep(2);

            return;
        }

        pacienteActual = nextList(listaPacientes);
    }

    puts("");
    puts("========================================");
    puts("          Paciente No Encontrado:");
    puts("========================================");

    system("pause");
}

void desasignarMedico(List* listaPacientes)
{
    Paciente* pacienteActual = firstList(listaPacientes);

    if(pacienteActual == NULL)
    {
        puts("========================================");
        puts("  La Lista de Pacientes esta vacia.");
        puts("========================================\n");
        system("pause");
        return;
    }

    char nombreABuscar[MAXCHAR];
    char apellidoABuscar[MAXCHAR];

    puts("============================================");
    puts("A que Paciente le desea desasignar un medico:");
    puts("============================================");
    
    printf("Ingrese Nombre: ");
    scanf("%30[^\n]s", &nombreABuscar);
    while(getchar() != '\n');

    printf("Ingrese Apellido: ");
    scanf("%30[^\n]s", &apellidoABuscar);
    while(getchar() != '\n');

    while(pacienteActual != NULL)
    {
        if(strcmp(pacienteActual->nombre, nombreABuscar) == 0 && strcmp(pacienteActual->apellido, apellidoABuscar) == 0)
        {   
            puts("");
            puts("========================================");
            puts("          Paciente Encontrado:");
            puts("========================================");
            puts("");

            void* medicoActual = firstList(pacienteActual->medicosAsignados);

            if(medicoActual == NULL)
            {
                printf("El Paciente no tiene Medicos Asignados.\n\n");
                system("pause");
                return;
            }
            else
            {
                puts("Medicos asignados:");
        
                while(medicoActual != NULL)
                {
                    printf(" - %s\n", medicoActual);

                    medicoActual = nextList(pacienteActual->medicosAsignados);
                }
            }

            char medicoBuscar[MAXCHAR];
            
            puts("\n============================================");
            puts("      Que medico desea desasignar:");
            puts("============================================\n");
            
            
            printf("Ingrese Medico: ");
            scanf("%30[^\n]s", &medicoBuscar);
            while(getchar() != '\n');

            medicoActual = firstList(pacienteActual->medicosAsignados);
            bool existeMedico = false;

            while(medicoActual != NULL)
            {
                if(strcmp(medicoActual, medicoBuscar) == 0)
                {
                    popCurrent(pacienteActual->medicosAsignados);
                    existeMedico = true;
                }

                medicoActual = nextList(pacienteActual->medicosAsignados);
            }

            if(!existeMedico)
            {   
                system("cls");
                puts("==============================================");
                puts("      El Medico ingresado no existe.");
                puts("==============================================");
                sleep(2);
                return;
            }

            system("cls");
            puts("==============================================");
            puts("      Medico desasignado exitosamente.");
            puts("==============================================");
            sleep(2);

            return;
        }

        pacienteActual = nextList(listaPacientes);
    }

    puts("");
    puts("========================================");
    puts("          Paciente No Encontrado:");
    puts("========================================");

    system("pause");
}

void importarCsvPaciente(List* listaPacientes)
{
    FILE* archivoPacientes;
    char nombreArchivo[MAXCHAR];

    while(true)
    {
        printf("Ingrese Nombre Archivo (incluir extension .csv): ");
        scanf("%s", &nombreArchivo);
        getchar();

        archivoPacientes = fopen(nombreArchivo,"r");

        if(archivoPacientes == NULL)
        {
            puts("\n==============================");
            printf("Error al abrir el archivo.\n");
            printf("Intentelo nuevamente.\n");
            puts("==============================\n");
        }
        else
        {
            break;
        }
    }

    char linea[8*MAXCHAR];
    char *campo;
    char *campoMedicos;

    char nombreAux[MAXCHAR];
    char apellidoAux[MAXCHAR];
    int edadAux;
    char telefonoAux[MAXCHAR];
    char direccionAux[MAXCHAR];
    char num_seguridad_socialAux[MAXCHAR];

    fgets(linea, 8*MAXCHAR, archivoPacientes);

    while(fgets(linea, 8*MAXCHAR, archivoPacientes))
	{
        List* medicosIngresados = createList();
        char *existeMasMedicos;

        campo = strtok(linea, ",");
        campo = quitar_tildes(campo);
        strcpy(nombreAux, campo);

        campo = strtok(NULL, ",");
        campo = quitar_tildes(campo);
        strcpy(apellidoAux, campo);

        campo = strtok(NULL, ",");
        edadAux = atoi(campo);

        campo = strtok(NULL, ",");
        strcpy(telefonoAux, campo);

        campo = strtok(NULL, ",");
        strcpy(direccionAux, campo);

        campo = strtok(NULL, ",");
        strcpy(num_seguridad_socialAux, campo);

        campo = strtok(NULL, "\n");
        existeMasMedicos = strchr(campo, ';');

        if(existeMasMedicos == NULL)
        {
            if(strcmp(campo, "Sin medicos asignados") != 0)
            {
                Medico *med = (Medico *) malloc(sizeof(Medico));
                campo = quitar_tildes(campo);
                strcpy(med->nombreMedico, campo);
                pushBack(medicosIngresados, med);
            }
        }
        else
        {
            while(campo != NULL)
            {
                Medico *med = (Medico *) malloc(sizeof(Medico));

                campoMedicos = strtok(campo, ";");
                campoMedicos = quitar_tildes(campoMedicos);

                strcpy(med->nombreMedico, campoMedicos);
                pushBack(medicosIngresados, med);

                campo = strtok(NULL, "\n");
            }
        }

        registrarPaciente(listaPacientes, nombreAux, apellidoAux, edadAux, telefonoAux, direccionAux, num_seguridad_socialAux, medicosIngresados, 2);
	}

    system("cls");

    puts("==============================================");
    puts("        El CSV se importo exitosamente.");
    puts("==============================================");

    sleep(2);

    fclose(archivoPacientes);
}

void exportarCsvPaciente(List* listaPacientes)
{
    Paciente* pacienteActual = firstList(listaPacientes);

    if(pacienteActual == NULL)
    {
        puts("========================================");
        puts("  La Lista de Pacientes esta vacia.");
        puts("========================================\n");
        system("pause");
    }
    else
    {
        FILE* archivoPacientes;
        char nombreArchivo[MAXCHAR];

        while(true)
        {
            printf("Ingrese Nombre Archivo (incluir extension .csv): ");
            scanf("%s", &nombreArchivo);
            getchar();

            archivoPacientes = fopen(nombreArchivo,"w");

            if(archivoPacientes == NULL)
            {
                puts("\n==============================");
                printf("Error al abrir el archivo.\n");
                printf("Intentelo nuevamente.\n");
                puts("==============================\n");
            }
            else
            {
                break;
            }
        }

        fprintf(archivoPacientes, "Nombre,Apellido,Edad,Telefono,Direccion,Num_Seguridad_Social,Medicos\n");

        while(pacienteActual != NULL)
        {
            fprintf(archivoPacientes, "%s,%s,%d,%s,%s,%s,", pacienteActual->nombre, pacienteActual->apellido, pacienteActual->edad, pacienteActual->telefono, pacienteActual->direccion, pacienteActual->num_seguridad_social);

            void* medicoActual = firstList(pacienteActual->medicosAsignados);
            bool tieneMasMedicos = false;

            if(medicoActual != NULL)
            {
                while(medicoActual != NULL)
                {
                    if(!tieneMasMedicos)
                    {
                        fprintf(archivoPacientes, "%s", medicoActual);
                        tieneMasMedicos = true;
                    }
                    else
                    {
                        fprintf(archivoPacientes, ";%s", medicoActual);
                    }

                    medicoActual = nextList(pacienteActual->medicosAsignados);
                }
            }
            else
            {
                fprintf(archivoPacientes, "Sin medicos asignados");
            }

            pacienteActual = nextList(listaPacientes);
            fprintf(archivoPacientes, "\n");
        }

        system("cls");

        puts("==============================================");
        puts("        El CSV se exporto exitosamente.");
        puts("==============================================");

        sleep(2);

        fclose(archivoPacientes);
    }
}

int main( int argc, char *argv[] ){

    int opcion;
    List* listaPacientes = createList();
    
    system("cls");
    puts("========================================");
    puts("               Trabajo 1");
    puts("     Desarrollada por Grupo ERROR 404");
    puts("========================================");
    sleep(2);

    do{
        system("cls");
        mostrarMenu();
        puts("");
        printf("Eliga una opcion: ");
        scanf("%d", &opcion);
        getchar();
        
        switch (opcion)
        {
            case 1:
                system("cls");

                char nombreAux[MAXCHAR];
                char apellidoAux[MAXCHAR];
                int edadAux;
                char telefonoAux[MAXCHAR];
                char direccionAux[MAXCHAR];
                char num_seguridad_socialAux[MAXCHAR];
                List* medicosIngresados = createList();

                puts("========================================");
                puts("          Registrar Paciente:");
                puts("========================================");

                printf("Ingrese Nombre: ");
                scanf("%30[^\n]", &nombreAux);

                while(getchar() != '\n');

                printf("Ingrese Apellido: ");
                scanf("%30[^\n]s", &apellidoAux);

                while(getchar() != '\n');

                do{
                    printf("Ingrese Edad: ");

                    while(scanf("%d", &edadAux) != 1)
                    {
                        printf("\nEntrada invalida. Ingrese un numero entero: ");
                        while(getchar() != '\n');
                    }

                    if(edadAux <= 0)
                    {
                        printf("\nEdad mal ingresada, intente nuevamente.\n");
                    }

                }while(edadAux <= 0);

                while(getchar() != '\n');
                
                printf("Ingrese Telefono: ");
                scanf("%30[^\n]s", &telefonoAux);

                while(getchar() != '\n');

                printf("Ingrese Direccion (sin comas): ");
                scanf("%30[^\n]s", &direccionAux);

                while(getchar() != '\n');

                printf("Ingrese Numero de Seguridad Social: ");
                scanf("%30[^\n]s", &num_seguridad_socialAux);

                while(getchar() != '\n');

                int respuestaMedicos;
    
                do{
                    printf("\nDesea Asignar Medicos al Paciente\n");
                    printf("Si (1)\n");
                    printf("No (0)\n");
                    
                    while(scanf("%d", &respuestaMedicos) != 1 || (respuestaMedicos != 1 && respuestaMedicos != 0))
                    {
                        printf("\nRespuesta invalida, intente nuevamente.\n");
                        printf("Si (1)\n");
                        printf("No (0)\n");
                        while(getchar() != '\n');
                    }

                } while(respuestaMedicos != 1 && respuestaMedicos != 0);
                
                if(respuestaMedicos == 1)
                {
                    registrarMedicos(medicosIngresados);
                }

                registrarPaciente(listaPacientes, nombreAux, apellidoAux, edadAux, telefonoAux, direccionAux, num_seguridad_socialAux, medicosIngresados, 1);
                break;
            case 2:
                system("cls");
                mostrarDatoPaciente(listaPacientes);
                break;
            case 3:
                system("cls");
                eliminarPaciente(listaPacientes);
                break;
            case 4:
                system("cls");
                mostrarTodosPacientes(listaPacientes);
                break;
            case 5:
                system("cls");
                pacientesSinMedicos(listaPacientes);
                break;
            case 6:
                system("cls");
                asignarMedico(listaPacientes);
                break;
            case 7:
                system("cls");
                desasignarMedico(listaPacientes);
                break;
            case 8:
                system("cls");
                importarCsvPaciente(listaPacientes);
                break;
            case 9:
                system("cls");
                exportarCsvPaciente(listaPacientes);
                break;
            case 10:
                system("cls");
                printf("Saliendo...\n");
                sleep(2);
                system("cls");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n\n");
                system("pause");
        }
   } while (opcion != 10);

    return 0;
}
# Tarea1_ControlPacientes
Tarea N°1 de Estructura de Datos, Ingeniería Civil Informática


Control de pacientes implementado con TDA Lista.
======

---
**Antes de Empezar**

*   Utilizamos Visual Studio Code para programar en C y con el uso de la extension Live Share compartimos en el codigo en tiempo real para cada integrante del grupo.
*   Ademas creamos un repositorio en GitHub para que todo el equipo tuviera acceso al codigo en cualquier momento con el siguiente link: https://github.com/Matias-Guerrero/Tarea1_ControlPacientes
*   Para ejecutar el codigo comenzamos compilando nuestros archivos .c a traves de la terminal con el siguiente comando: `gcc -g main.c list.c -o Tarea1`, con este comando se crea un archivo .exe, luego para ejecutar Tarea1.exe utilizamos el siguiente comando: `\Tarea1.exe`.
*   Para ejecutar el codigo se debe descargar solo el archivo `Tarea1.exe`.

---

En esta aplicacion implementamos una **lista enlazada**. Para esto utilizamos la siguiente estructura:

````c
typedef struct Node Node;

struct Node {
    void * data; // Puntero al dato
    Node * next; // Puntero al siguiente nodo
    Node * prev; // Puntero al nodo previo
};

typedef struct {
    Node * head; // Puntero al primer elemento
    Node * tail; // Puntero al ultimo elemento
    Node * current; // Puntero para poder recorrer la lista
} List;
````
---

Se nos pidió crear una aplicación que teoricamente seria utilizada en un/a hospital/clinica,
teniendo como objetivo registrar, almacenar y eliminar datos sobre los pacientes que asistiran al recinto. Utilizamos las siguientes estructuras:

````c
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
````

---

Este programa comienza con el main mostrando el menu de opciones, para esto llamamos a la `funcion menu()`, este menu lo integramos dentro de un bucle do-while ya que cada vez que elijamos una opcion siempre se vuelve al menu despues de completarla o si ingresemos un valor erroneo volverá al menu.

Para ingresar las opciones del menu, se debe ingresar valores enteros entre 1 y 10, dependiendo de lo que uno desee realizar, para esto utilizamos un switch, asi estructuramos adecuadamente todas las funciones que debemos implementar.

Funciones Implementadas:
----

- **Opcion 1:** `registrarPacientes(List* listaPacientes, char* nombreAux, char* apellidoAux, int edadAux, char* telefonoAux, char* direccionAux, char* num_seguridad_socialAux, List * medicosIngresados, int opcion)`:

    Una vez elegida la opción 1, antes de llamar a la función `registrarPacientes()`, se ingresan los datos del paciente y validamos que las variables de `tipo char*` no superen los 30 caracteres y que la edad ingresada sea mayor a 0.
    
    Además, para agregar médicos al paciente utilizamos un ciclo do-while en donde el usuario elige si quiere o no asignar médicos, si el usuario ingresa un dato invalido (p.ej. un carácter o un número entero distinto de 1 o 0) se vuelve a preguntar hasta que se ingrese un dato válido para responder la pregunta.

    Si el usuario decide asignar médicos, se llama a la función `registrarMedicos()` a la cual le ingresamos como parámetro la lista de médicos del paciente en cuestión. Una vez dentro de la función para registrar los médicos al paciente, nuevamente con el uso del bucle do-while, el usuario debe ingresar la cantidad de médicos a asignar (el número a ingresar debe ser mayor a 0), luego con un ciclo for se ingresa el nombre del médico a asignar, para esto se valida que el nombre del médico no sobrepase los 30 caracteres y mediante el uso de las funciones de listas enlazadas buscamos que el médico no exista en la lista de médicos del paciente, una vez que se cumplan las condiciones mencionadas anteriormente, el nombre del médico se guarda en la lista de médicos del paciente con el uso del `pushBack()`.

    Si se da el caso de que el usuario asigna un médico que ya está asignado al paciente, se muestra un mensaje por pantalla indicando que ya está registrado, y se vuelve a pedir un médico no ingresado .

    Y finalmente se llama a la función `registrarPaciente()` con los parámetros ya ingresados, en la función se crea una variable paciente asignando la memoria correspondiente con la `función malloc()`,luego con el uso de `firstList()` y `nextList()` recorremos la lista enlazada de pacientes para comprobar si el paciente ya está registrado, esta comprobación  es a través del número de seguridad social ya que este es único para cada paciente. Finalmente se copian los datos a la variable paciente creada anteriormente, se agrega el paciente a la lista de pacientes con `pushBack()` y se muestra un mensaje por pantalla diciendo que el paciente se registró exitosamente.

    Para esta opción del menú, al momento de llamar a la función `registrarPaciente()` asignamos el último parámetro de esta como un 1, esto ya que esta función se usa tanto para registrar pacientes ingresados por el usuario y para registrar pacientes leídos desde un csv.

    
- **Opcion 2:** `void mostrarDatoPaciente(List* listaPacientes)`:

    Una vez seleccionada la opción 2, se llama a la función `mostrarDatoPaciente()` la cual recibe como argumento la lista de pacientes. En esta función se crean dos variables que nos servirán  para buscar el nombre y apellido del paciente.  Luego en la variable pacienteActual se guarda el primer elemento de la lista de Pacientes, la cual nos servirá para recorrer la lista en búsqueda del paciente que se desea mostrar por pantalla.

    Entra a una condicional (if-else) en la cual se comprueba si el primer dato de la lista es nulo lo que significa que la lista está vacía, y por lo tanto muestra un mensaje por pantalla indicando que la lista se encuentra vacía con lo que termina la función, en el caso contrario el programa indica por pantalla que se debe ingresar el nombre y el apellido del paciente a buscar los cuales no deben superar los 30 caracteres. Una vez ingresados los datos del paciente comienza un ciclo while el cual nos sirve para recorrer la lista de pacientes y para realizar este recorrido utilizamos el `nextList()` para avanzar por la lista enlazada, para realizar la búsqueda del paciente se utiliza un condicional if en donde se va a entrar siempre y cuando se cumpla la condición que el pacienteActual -> nombre sea el mismo que la variable nombreABuscar y también el pacienteActual->apellido sea el mismo que apellidoABuscar, teniendo en cuenta que esta comparación se hace con la `función strcmp` ya que compara dos cadenas de caracteres, una vez encontrado el paciente se muestran todos los datos  y se accede a la lista de médicos para ver si el paciente tiene médicos o no, en el caso que tenga por lo menos un médico se recorre la lista de médicos para mostrar los médicos que tiene asignado el paciente,en caso contrario se muestra un mensaje que señala que el paciente no tiene médicos asignados.Con este se da término a la función llamada y se vuelve al menú principal.

- **Opcion 3:** `void eliminarPaciente(List * listaPacientes)`:

    Esta opción, al seleccionarla, llama `EliminarPacientes()`. En esta función se pasa como parámetro la lista del paciente para posteriormente buscar en caso de que exista y eliminarlo.

    El proceso comienza por indicar el primero de la lista `(first List)` y verifica si la lista está vacía. En el caso de que sea así, retorna un mensaje que indica que la lista está vacía y por lo tanto termina la función  regresando al menú. En caso contrario, sigue con el código y le pide al usuario que ingrese el nombre y apellido del paciente a buscar. Estos datos se almacenan en dos variables individuales.

    Estos datos luego son comparados dentro de un ciclo while, en el cual se recorre toda la lista de pacientes preguntando con un control de flujo if comparando si es que los nombres y apellidos ingresados por el usuario son iguales a los datos de nombre y apellido del current de la lista, se recorrerá toda la lista con la función `nextList()` por cada iteración y en caso de que no se encuentren los datos en la lista, se verificará si el current es nulo y saldrá del ciclo imprimiendo un mensaje que no se encontró el paciente y retornará la función. En caso de que encuentre el paciente, se ejecutará inmediatamente un `popCurrent()` y eliminará al paciente junto a un mensaje que indica que el paciente ha sido eliminado exitosamente.


- **Opcion 4:** `void mostrarTodosPacientes(List* listaPacientes)`:

    Al seleccionar la opción 4 se llama a la `función mostrarTodosPacientes()`, se crea la variable pacienteActual para guardar el primer elemento de la lista de Pacientes, la cual nos servirá para recorrer la lista y así mostrar a todos los pacientes con su información respectiva.

    Se entra a una condicional if-else en donde comienza con la condición que  si el pacienteActual es nulo se debe mostrar por pantalla un mensaje indicando que la lista de pacientes se encuentra vacía, en caso contrario comienza un ciclo while el cual nos sirve para recorrer la lista de pacientes, para realizar este recorrido utilizamos el `nextList()` y así avanzar por la lista enlazada para mostrar por pantalla a cada paciente con todos sus datos y con un contador indicar que es el paciente número contador.

    Para mostrar los médicos asignados a cada paciente, se crea la variable medicoActual para guardar el primer elemento de la lista de Médicos, lo cual nos servirá para recorrer la lista enlazada y así mostrar a todos los médicos que tiene asignados el paciente. Luego entra a un condicional if-else, donde la condición es que si medicoActual es nulo se muestra por pantalla que el paciente no tiene médicos asignados, en caso contrario se van a mostrar los médicos que tiene asignado, recorriendo la lista de médicos con la función `nextList()`.


- **Opcion 5:** `void pacientesSinMedicos(List* listaPacientes)`:

    Una vez seleccionada la opción 5, se llama a la función `pacientesSinMedicos()`, en donde se comienza obteniendo el primer paciente de la lista usando el `firstList()`, también se inicializa un contador para llevar la cuenta de los pacientes sin médicos para que cuando sean mostrados por pantalla esten enumerados y se crea una variable pacientesSinMedicos la que se inicializa en falso, la cual indica si es que encontraron o no pacientes sin médicos asignados.

    Luego se ingresa a una condicional if-else en donde se verifica si el pacienteActual es nulo ya que si se cumple esto se mostrará un mensaje por pantalla indicando que la lista de pacientes se encuentra vacía, en caso contrario,  los pacientes  que no tiene médicos asignados serán mostrados por pantalla con todos sus datos y para realizar esta acción se debe recorrer la lista enlazada con `netxList()` y si encuentra por lo menos un paciente sin médicos asignados la variable pacientesSinMedicos cambia a verdadero.

    Y también está el caso que se recorra toda la lista de pacientes y todos tengan médicos asignados, se mostrará por pantalla el mensaje indicando que todos los pacientes tienen por lo menos un médico asignado. Y con esto se da término a la función llamada y se vuelve al menú principal.


- **Opcion 6:** `void asignarMedico(List * listaPacientes)`:

    Una vez elegida la opción 6, se llama a la función `asignarMedico()`, en la cual se comienza obteniendo el primer paciente de la lista de pacientes usando el `firstList()`, y luego entra a un condicional if en donde se pregunta si la lista de pacientes es nula indicando por pantalla un mensaje que la lista de pacientes está vacía.

    En el caso de de que la lista contenga datos, se va pedir que el usuario ingrese el nombre y apellido del paciente al cual se desea asignar médicos, para así entrar al ciclo while el cual nos sirve para recorrer la lista de pacientes, para realizar este recorrido utilizamos el `nextList()` y asi avanzar por la lista enlazada, luego entra en un condicional if en donde se debe cumplir la condición que el pacienteActual -> nombre sea el mismo que la variable nombreABuscar y también el pacienteActual->apellido sea el mismo que apellidoABuscar, teniendo en cuenta que esta comparación se hace con la `función strcmp` ya que compara dos cadenas de caracteres, luego se llama a la función `registrarMedicos()`, y una vez realizado el registro se muestra por pantalla que el médico fue asignado exitosamente.

    Ademas está el caso en el que se ha recorrido toda la lista enlazada y no se ha encontrado el paciente, se indica por pantalla que el paciente no fue encontrado.


- **Opcion 7:** `void desasignarMedico(List* listaPacientes)`:

    Una vez elegida la opción 7, se llama a la función `desasignarMedico()`, en la cual se comienza obteniendo el primer paciente de la lista de pacientes usando el `firstList()`, luego se entra al condicional if en donde si pacienteActual es nulo se indica por pantalla que la lista de pacientes se encuentra vacía.

    En el caso que la lista contenga datos, se va a pedir ingresar el nombre y apellido del paciente al cual se le va a desasignar médicos, para así entrar al ciclo while el cual nos sirve para recorrer la lista de pacientes y para realizar este recorrido utilizamos el `nextList()` para avanzar por la lista enlazada, luego entra en un condicional if en donde se debe cumplir la condición que el pacienteActual -> nombre sea el mismo que la variable nombreABuscar y también el pacienteActual->apellido sea el mismo que apellidoABuscar, teniendo en cuenta que esta comparación se hace con la `función strcmp` ya que compara dos cadenas de caracteres. Luego se obtiene el primer médico que tiene el paciente de la lista de pacientes usando el `firstList()`, entra al condicional if en donde si medicoActual es nula por pantalla se va mostrar que el paciente no tiene médicos asignados, en caso contrario se va a recorrer la lista de médicos asignados al paciente con la `función nextList()`, para así mostrar los nombres de los médicos.

    Después se pide ingresar el nombre del médico que se desea desasignar, para así con el `firstList()` obtener el primer médico que tiene el paciente y también se crea una variable booleana, la cual se inicializa en falso, luego entra a un ciclo condicional while, siempre y cuando medicoActual no sea nulo, con la función `nextList()` vamos a recorrer la lista enlazada hasta encontrar al médico buscado. Luego a través de un condicional if en donde con la función strcmp se compara medicoActual con medicobuscar, si esto se cumple, con la función de la lista enlazada `popCurrent()` se elimina al médico especificado  y cambia el valor de existeMedico a verdadero, para así indicar por pantalla que el médico se ha desasignado exitosamente.

    En caso contrario si el booleano existeMedico sigue siendo falso se mostrará por pantalla que el médico ingresado no existe. 
 
    Y finalmente en caso de no encontrar al paciente se muestra por pantalla un mesaje en el cual se indica que el paciente no fue encontrado.


- **Opcion 8:** `void importarCsvPaciente(List* listaPacientes)`:

    Luego de elegir la opción 8, se llamará a la función `ImportarCsvPacientes()`, función que tomará los datos escritos en un archivo .CSV, el cual, contiene información de pacientes y sus médicos, para luego almacenar los datos en una lista.

    Primero se le pide al usuario que ingrese el nombre del archivo CSV que desea importar con la terminación `.csv` (Si llegase a NO existir el nombre del archivo, o  este fuese inscrito con un nombre incorrecto, se notificará al usuario que no existe tal archivo, dándole la oportunidad de ingresar un nombre nuevamente). Luego, se abre el archivo en modo `read` ya que lo utilizaremos solo para leer los datos que este contiene y se lee línea por línea, Cada línea se divide en campos separados por comas utilizando la `función strtok()` y se eliminan los tildes con la función `quitar_tildes()`. Se crean variables auxiliares de tipo char correspondientes al nombre, apellido, teléfono, dirección y número de seguridad social del paciente, y una variable tipo int para la edad (que almacenarán los datos hasta que sean ingresados en la lista), así como una lista de los médicos asignados a ese paciente. En el caso de que el paciente NO tuviese médicos asignados. se registra “Sin médicos asignados”. Si el paciente posee más de un médico asignado , se utiliza el carácter ` ; ` para separar los nombres de los médicos en el campo correspondiente. Finalmente se llama a la función `registrarPaciente()` para agregar al paciente a la lista enlazada y se cierra el archivo. Una vez terminado, se muestra un mensaje informando al usuario que el archivo se ha importado de manera exitosa.


- **Opcion 9:** `void exportarCsvPaciente(List* listaPacientes)`:

    Al elegir esta opción se llamará a la función `ExportarCsvPacientes()`, la cual leerá todos los datos de la lista y los escribirá en un archivo .CSV.

    La función inicia con un puntero indicado por `firstlist()` que apunta al paciente del nodo, en caso de que la lista esté vacía, simplemente imprimirá un mensaje diciendo que la lista de pacientes está vacía y luego pedirá al usuario que ingrese una tecla para continuar. En caso omiso, se creará un puntero a FILE para luego exportarlo a un archivo. Después se le solicita al usuario que ingrese el nombre del archivo a crear, el FILE se abre en modo `write`con el nombre indicado y tiene un control de flujo en caso de que el archivo no se haya podido abrir y solicitará intentarlo nuevamente.

    Previamente a registrar el paciente, se colocarán las “columnas” de cada dato para identificar qué representa cada uno. Ahora es cuando se empezará a recorrer la lista con un while, en el cual su condición consiste en que la lista sea distinta de nulo, por tanto, recorrerá toda la lista hasta el último elemento.

    Luego, escribirá cada dato del paciente en el archivo hasta su número de seguridad social con la `funcion fprintf()`. Luego, como los médicos se encuentran separados por puntos y comas y se encuentran en una lista, se accede al `firstlist()` de la lista medicosAsignados del paciente, inicializado junto a un bool tieneMasMedicos en falso que indicará si este paciente tiene más de un médico asignado.

    Previo al procesamiento de médicos, se verifica si la lista de médicos del paciente esté vacía, y en el caso de que esto sea verdad, procederá a saltar el proceso de exportación e imprimirá un mensaje que indique que hay más de un médico. Si esto no se cumplé, se asume que hay por lo menos un médico y entrará en un ciclo que recorrerá toda la lista de estos,  por cada iteración preguntará en un control de flujo si es que el bool tieneMasMedicos es falso, en caso de que esto se cumpla, escribirá el primer médico en el archivo sin una coma y el bool se convertirá en verdadero, luego la lista de médicos va al siguiente elemento, en caso de que este sea nulo, se daría por terminado el registro del paciente en el archivo y saltaría a la siguiente línea para registrar al próximo paciente. Sin embargo, si es que la lista aún tiene médicos, entrará al else de la condición que verifica que el tieneMasMedicos era falso, por tanto ingresará los médicos restantes con una separación de punto y coma.

    Una vez registrados todos los pacientes, se imprime un mensaje que el csv fue creado y exportado exitosamente y procede a cerrar con `fclose()` el archivo FILE creado.


- **Opcion 10:** 

    Si se selecciona la opción 10, esto hará que se muestre un mensaje por pantalla que indica que se está saliendo del programa, lo cual cierre la terminal y dará término a la ejecución del programa de control de pacientes.

---

**Coevaluacion Personal**

| Nombres | Participación | Responsabilidad | Comunicación | Calidad de trabajo | Trabajo en equipo | TOTAL |
|--------|--------------|----------------|--------------|--------------------|------------------|-------|
| Ulysses B. | 20 | 20 | 20 | 15 | 20 | 95 |
| Matías G. | 20 | 20 | 20 | 20 | 20 | 100 |
| Fabiana P. | 15 | 20 | 20 | 20 | 20 | 95 |
| Matías R. | 15 | 20 | 20 | 20 | 20 | 95 |

**Coevaluacion Grupal**

| Evaluación grupal | Participación | Responsabilidad | Comunicación | Calidad de trabajo | Trabajo en equipo | TOTAL |
|------------------|--------------|----------------|--------------|--------------------|------------------|-------|
| ERROR 404 | 20 | 20 | 15 | 15 | 15 | 85 |

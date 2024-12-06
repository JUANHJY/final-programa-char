#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//este programa es
// Estructura del Estudiante
typedef struct {
    char nombre[35];   // Nombre del estudiante (máximo 35 caracteres)
    float promedio;    // Promedio del estudiante
    char carrera[35];  // Carrera del estudiante (máximo 35 caracteres)
} Estudiante;

// Prototipos de funciones
void nuevoArchivo(const char* nombreArchivo);
void abrirArchivo(const char* nombreArchivo);
void guardarArchivo(const char* nombreArchivo, Estudiante estudiantes[], int cantidad);
void buscarEstudiante(const char* nombreArchivo);
void eliminarArchivo(const char* nombreArchivo);
void agregarEstudiante(Estudiante estudiantes[], int* cantidad);
void eliminarEstudiante(Estudiante estudiantes[], int* cantidad, const char* nombreEstudiante);

int main() {
    int opcion = 0;
    char nombreArchivo[35];
    Estudiante estudiantes[50]; // Máximo de 50 estudiantes
    int cantidadEstudiantes = 0;

    do {
      printf("\n  Menu  \n");
      printf("1. Nuevo Archivo\n");
        printf("2. Abrir Archivo\n");
       printf("3. Guardar Archivo\n");
        printf("4. Buscar Estudiante\n");
 printf("5. Agregar Estudiante\n");
        printf("6. Eliminar Estudiante\n");
        printf("7. Eliminar Archivo\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del nuevo archivo: ");
                fgets(nombreArchivo, 35, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';
                nuevoArchivo(nombreArchivo);
                break;
            case 2:
                printf("Ingrese el nombre del archivo a abrir: ");
                fgets(nombreArchivo, 35, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';
                abrirArchivo(nombreArchivo);
                break;
            case 3:
                printf("Ingrese el nombre del archivo para guardar: ");
                fgets(nombreArchivo, 35, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';
                guardarArchivo(nombreArchivo, estudiantes, cantidadEstudiantes);
                break;
            case 4:
                printf("Ingrese el nombre del archivo para buscar: ");
                fgets(nombreArchivo, 35, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';
                buscarEstudiante(nombreArchivo);
                break;
            case 5:
                agregarEstudiante(estudiantes, &cantidadEstudiantes);
                break;
            case 6: {
                char nombreEstudiante[35];
                printf("Ingrese el nombre del estudiante a eliminar: ");
                fgets(nombreEstudiante, 35, stdin);
                nombreEstudiante[strcspn(nombreEstudiante, "\n")] = '\0';
                eliminarEstudiante(estudiantes, &cantidadEstudiantes, nombreEstudiante);
                break;
            }
            case 7:
                printf("Ingrese el nombre del archivo a eliminar: ");
                fgets(nombreArchivo, 35, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';
                eliminarArchivo(nombreArchivo);
                break;
            case 8:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 8);

    return 0;  // es el retorno de prograna
}

// Funciones del programa de estudiate
         void nuevoArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo) {
        printf("Archivo creado con exito.\n");
        fclose(archivo);
    } else {
        printf("Error al crear el archivo.\n");
    }
}

    void abrirArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo) {
        Estudiante estudiante;
        printf("\n--- Contenido del Archivo ---\n");
        while (fread(&estudiante, sizeof(Estudiante), 1, archivo)) {
            printf("Nombre: %s, Promedio: %.2f, Carrera: %s\n", estudiante.nombre, estudiante.promedio, estudiante.carrera);
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

void guardarArchivo(const char* nombreArchivo, Estudiante estudiantes[], int cantidad) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo) {
fwrite(estudiantes, sizeof(Estudiante), cantidad, archivo);
        fclose(archivo);
printf("Archivo guardado con exito.\n");
    } else {
        printf("Error al guardar el archivo.\n");
    }
}

void buscarEstudiante(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo) {
        char nombreBuscado[35];
          printf("Ingrese el nombre del estudiante a buscar: ");
         fgets(nombreBuscado, 35, stdin);
        nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';

        Estudiante estudiante;
        int encontrado = 0;
        while (fread(&estudiante, sizeof(Estudiante), 1, archivo)) {
            if (strcmp(estudiante.nombre, nombreBuscado) == 0) {
                printf("Nombre: %s, Promedio: %.2f, Carrera: %s\n", estudiante.nombre, estudiante.promedio, estudiante.carrera);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("Estudiante no encontrado.\n");
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

void eliminarArchivo(const char* nombreArchivo) {
    if (remove(nombreArchivo) == 0) {
        printf("Archivo eliminado con exito.\n");
    } else {
        printf("Error al eliminar el archivo.\n");
    }
}

void agregarEstudiante(Estudiante estudiantes[], int* cantidad) {
    if (*cantidad < 50) {
        printf("Ingrese el nombre del estudiante: ");
        fgets(estudiantes[*cantidad].nombre, 35, stdin);
        estudiantes[*cantidad].nombre[strcspn(estudiantes[*cantidad].nombre, "\n")] = '\0';

        printf("Ingrese el promedio del estudiante: ");
        scanf("%f", &estudiantes[*cantidad].promedio);
        getchar();
        printf("Ingrese la carrera del estudiante: ");
        fgets(estudiantes[*cantidad].carrera, 35, stdin);
        estudiantes[*cantidad].carrera[strcspn(estudiantes[*cantidad].carrera, "\n")] = '\0';

        (*cantidad)++;
        printf("Estudiante agregado con exito.\n");
    } else {
        printf("No se pueden agregar más estudiantes. Capacidad máxima alcanzada.\n");
    }
}

void eliminarEstudiante(Estudiante estudiantes[], int* cantidad, const char* nombreEstudiante) {
    int encontrado = 0;
    for (int i = 0; i < *cantidad; i++) {
        if (strcmp(estudiantes[i].nombre, nombreEstudiante) == 0) {
            encontrado = 1;
            for (int j = i; j < *cantidad - 1; j++) {
                estudiantes[j] = estudiantes[j + 1];
            }
            (*cantidad)--;
            printf("Estudiante eliminado con exito.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Estudiante no encontrado.\n");
    }
}

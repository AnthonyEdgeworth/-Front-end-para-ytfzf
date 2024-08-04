#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <sys/stat.h>
#include "suscripciones.h"
#include "configuracion.h"
#include "menu.h"
#include "cargarParametros.h"

// Prototipos de funciones
char *obtener_usuario();
void asegurar_directorio_suscripciones();
void construir_archivo_suscripciones(const char *archivo_csv, const char *ruta_suscripciones);
void gestionar_suscripciones(const char *ruta_csv);
// Función para obtener el nombre del usuario actual
char *obtener_usuario() {
    char buffer[128];
    FILE *fp = popen("whoami", "r");
    if (fp == NULL) {
        perror("No se pudo ejecutar el comando whoami");
        return NULL;
    }

    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        pclose(fp);
        return NULL;
    }
    pclose(fp);

    // Elimina el salto de línea del final
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    return strdup(buffer);
}

// Función para asegurar que el directorio de suscripciones exista
void asegurar_directorio_suscripciones() {
    char *usuario = obtener_usuario();
    if (usuario == NULL) {
        fprintf(stderr, "No se pudo obtener el nombre del usuario.\n");
        return;
    }

    char directorio[512];
    snprintf(directorio, sizeof(directorio), "/home/%s/.config/ytfzf/", usuario);
    free(usuario);

    struct stat st = {0};
    if (stat(directorio, &st) == -1) {
        if (mkdir(directorio, 0700) == -1) {
            perror("Error al crear el directorio de suscripciones");
            return;
        }
    }
}

// Función para construir el archivo de suscripciones desde el archivo CSV
void construir_archivo_suscripciones(const char *archivo_csv, const char *ruta_suscripciones) {
    FILE *csv = fopen(archivo_csv, "r");
    if (csv == NULL) {
        perror("Error al abrir el archivo CSV");
        return;
    }

    FILE *suscripciones = fopen(ruta_suscripciones, "w");
    if (suscripciones == NULL) {
        perror("Error al crear el archivo de suscripciones");
        fclose(csv);
        return;
    }

    char linea[512];
    while (fgets(linea, sizeof(linea), csv)) {
        // Omitir la cabecera
        if (strstr(linea, "ID del canal") != NULL) {
            continue;
        }

        // Dividir la línea por comas
        char *token = strtok(linea, ",");
        if (token != NULL) {
            token = strtok(NULL, ",");
            if (token != NULL) {
                // Eliminar el salto de línea al final
                size_t len = strlen(token);
                if (len > 0 && (token[len - 1] == '\n' || token[len - 1] == '\r')) {
                    token[len - 1] = '\0';
                }

                // Agregar "s" después de "http"
                if (strncmp(token, "http://", 7) == 0) {
                    fprintf(suscripciones, "https://%s\n", token + 7);
                } else {
                    fprintf(suscripciones, "%s\n", token);
                }
            }
        }
    }

    fclose(csv);
    fclose(suscripciones);

    printf("Archivo de suscripciones creado correctamente en: %s\n", ruta_suscripciones);
}

void gestionar_suscripciones(const char *ruta_csv) {
    // Asegurar que el directorio de suscripciones exista

  Config tmp_gestionar_suscripciones;

  if (tmp_gestionar_suscripciones.suscripciones == FALSE)
  {
    printf("No se ha cargado previamente el archivo canales.csv");
ejecutar_menu();

  }
  


    asegurar_directorio_suscripciones();


    // Obtener el nombre de usuario y construir la ruta del archivo de suscripciones
    char *usuario = obtener_usuario();
    if (usuario == NULL) {
        fprintf(stderr, "No se pudo obtener el nombre del usuario.\n");
        return;
    }

    char ruta_suscripciones[512];
    snprintf(ruta_suscripciones, sizeof(ruta_suscripciones), "/home/%s/.config/ytfzf/subscriptions", usuario);
    free(usuario);

    // Verificar si el archivo de suscripciones ya existe
    if (access(ruta_suscripciones, F_OK) == -1) {
        // El archivo no existe, construir el archivo de suscripciones a partir del archivo CSV
        construir_archivo_suscripciones(ruta_csv, ruta_suscripciones);
    }

    // Abrir el archivo CSV
    FILE *file = fopen(ruta_csv, "r");
    if (!file) {
        perror("No se pudo abrir el archivo CSV");
        return;
    }

    // Leer el archivo CSV y procesar cada línea
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Omitir la cabecera
        if (strstr(line, "ID del canal") != NULL) {
            continue;
        }

        // Dividir la línea por comas
        char *token = strtok(line, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        char *title = token;

        // Eliminar el salto de línea al final del título
        if (title != NULL) {
            size_t len = strlen(title);
            if (len > 0 && title[len - 1] == '\n') {
                title[len - 1] = '\0';
            }
        }





        // Generar el comando ytfzf
        char *busqueda = salidaTerminal();
        char command[512];
        snprintf(command, sizeof(command), "%s -c youtube-subscriptions", busqueda);
        printf("Ejecutando: %s\n", command);
        system(command);

        free(busqueda);

        // Preguntar al usuario si desea continuar
        char respuesta;
        do {
            printf("¿Quieres seguir viendo la lista de suscripciones? No[N]   Sí[S]: ");
            scanf(" %c", &respuesta);
            respuesta = toupper(respuesta);
            if (respuesta != 'S' && respuesta != 'N') {
                printf("Opción inválida. Ingrese 'S' o 'N'.\n");
            }
        } while (respuesta != 'S' && respuesta != 'N');

        if (respuesta == 'N') {
            fclose(file);
            return;
        }
    }

    fclose(file);
}

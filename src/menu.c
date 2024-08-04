#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>
#include "menu.h"
#include "suscripciones.h"
#include "configuracion.h"
#include "cargarParametros.h"
#include "menuconfiguracion.h" // Incluye el encabezado correcto
#include "cargarParametros.h"
#include "manual_User.h"

void mostrar_menu();
void manejar_opcion(Config *config, const gchar *ruta); // Actualiza la firma
int ejecutar_menu();
void buscar();
int easterEggs = 1;
char *page = "--pages-start=";

void asegurar_directorio(const gchar *ruta);

int ejecutar_menu()
{
    gchar *usuario = obtener_usuario();
    gchar ruta_config[256];
    Config config; // Definimos la estructura Config aquí

    if (!usuario)
    {
        fprintf(stderr, "Error al obtener el usuario actual.\n");
        return 0; // Error
    }

    snprintf(ruta_config, sizeof(ruta_config), "/home/%s/.config/cli-youtube/config.txt", usuario);

    // Asegurar que el directorio exista
    asegurar_directorio(ruta_config);

    // Verificar si el archivo de configuración existe
    if (g_file_test(ruta_config, G_FILE_TEST_EXISTS))
    {
        // Si existe, cargar la configuración
        cargar_configuracion(ruta_config, &config);
    }
    else
    {
        // Si no existe, crear el archivo de configuración con valores por defecto
        crear_archivo_configuracion(ruta_config);
        cargar_configuracion(ruta_config, &config);
    }

    manejar_opcion(&config, ruta_config); // Pasa los parámetros correctos

    free(usuario); // Liberar memoria asignada por obtener_usuario
    return 0;      // Éxito
}

void mostrar_menu()
{
    printf("Menú Principal\n");
    printf("[1]  Buscador\n");
    printf("[2]. Gestionar suscripciones\n");
    printf("[3]. Configuración\n");
    printf("[4]. Manual de usuario\n");
    printf("[5]. Creditos\n");
    printf("[6]. Salir\n");
}

void manejar_opcion(Config *config, const gchar *ruta)
{
    int opcion;
    do
    {
        mostrar_menu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion)
        {
        case 1:
            buscar();
            system("clear");
            break;

        case 2:
            gchar *usuario = obtener_usuario();
            gchar ruta_config[256];
            Config config_ruta; // Definimos la estructura Config aquí

            if (!usuario)
            {
                fprintf(stderr, "Error al obtener el usuario actual.\n");
                return 0; // Error
            }

            snprintf(ruta_config, sizeof(ruta_config), "/home/%s/.config/cli-youtube/canales.csv", usuario);

            system("clear");
            gestionar_suscripciones(ruta_config);
            break;
        case 3:
            system("clear");
            menu_configuraciones(config); // Llama a la función con el parámetro correcto
            break;
        case 4:
        mostrar_menu_manual();
            break;

        case 5:
            printf("\nProgramadores:");
            printf("\n [1]: Antho: https://github.com/AnthonyEdgeworth \n");
            printf("\nPresione enter para continuar.");
            getchar();
            system("clear");
            easterEggs++;
            if (easterEggs >= 24)
            {
                printf("Agradecimientos muy especiales:");
                printf(" Ángela ♡");
                printf("\nPresione enter para continuar.");
                getchar();
                system("clear");
            }
            ejecutar_menu();
            break;
            
                    case 6:
            printf("Saliendo...\n");
            exit(0);
            break;
            

        default:
            system("clear");
            printf("Opción no válida. Inténtalo de nuevo.\n");
            break;
        }
    } while (opcion != 3);
}

void buscar()
{
    char busquedaUsuario[256];
    char *busqueda = salidaTerminal();
    char command[512];

    printf("¿En qué estás pensando?: ");
    fgets(busquedaUsuario, sizeof(busquedaUsuario), stdin);

    // Elimina el salto de línea al final de la entrada
    size_t len = strlen(busquedaUsuario);
    if (len > 0 && busquedaUsuario[len - 1] == '\n')
    {
        busquedaUsuario[len - 1] = '\0';
    }

    gchar *usuario = obtener_usuario();
    gchar ruta_config[256];
    Config config; // Definimos la estructura Config aquí

    if (!usuario)
    {
        fprintf(stderr, "Error al obtener el usuario actual.\n");
        return; // Error
    }

    snprintf(ruta_config, sizeof(ruta_config), "/home/%s/.config/cli-youtube/config.txt", usuario);

    // Inicializa la configuración. Aquí debes cargar la configuración desde el archivo.
    int pagBuscar = obtener_paginas_cargar(ruta_config);

    for (size_t i = 1; i <= pagBuscar; i++)
    {
        snprintf(command, sizeof(command), "%s %s%ld %s", busqueda, page, i, busquedaUsuario);
        printf("Ejecutando: %s\n", command);
        system(command);
    }

    free(usuario); // Liberar memoria asignada por obtener_usuario
}

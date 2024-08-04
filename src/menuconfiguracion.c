#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>
#include <ctype.h>
#include "menu.h"
#include "suscripciones.h"
#include "configuracion.h"
#include "cargarParametros.h"
#include "menuconfiguracion.h"
#include "filtros.h"

// Prototipos de funciones
void mostrar_menu_configuracion();
void menu_configuraciones(Config *config);
void restaurar_valores_por_defecto(Config *config, const gchar *ruta);
void cambiar_configuraciones(Config *config, const gchar *ruta);
void ver_configuraciones(const gchar *ruta);
void manejar_opcion_config_copy(Config *config, const gchar *ruta);
void gestionar_suscripciones_menu_config(Config *config, const gchar *ruta);
void mostrar_mensaje_archivo(const gchar *ruta_archivo);

// Función principal del menú de configuración
void menu_configuraciones(Config *config)
{
    gchar *usuario = obtener_usuario();
    gchar ruta_config[512];
    snprintf(ruta_config, sizeof(ruta_config), "/home/%s/.config/cli-youtube/config.txt", usuario);

    if (!usuario)
    {
        fprintf(stderr, "Error al obtener el usuario actual.\n");
        exit(EXIT_FAILURE);
    }

    int opcion;
    do
    {
        mostrar_menu_configuracion();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion)
        {
        case 1:
            restaurar_valores_por_defecto(config, ruta_config);
            break;
        case 2:
            cambiar_configuraciones(config, ruta_config);
            break;
        case 3:
        {
            manejar_opcion_config_copy(config, ruta_config);
            printf("Presione enter para continuar.");
            getchar();
            system("clear");
            ejecutar_menu();
        }
        break;

        case 4:
            ver_configuraciones(ruta_config);
            ejecutar_menu();
        case 5:
            system("clear");
            printf("Saliendo...\n");
            ejecutar_menu();
        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
            break;
        }
    } while (opcion != 4);

    free(usuario); // Liberar la memoria
}

// Mostrar el menú
void mostrar_menu_configuracion()
{
    printf("Menú de Configuración\n");
    printf("[1]. Restaurar configuraciones por defecto\n");
    printf("[2]. Cambiar configuraciones\n");
    printf("[3]. Cargar canales.csv\n");
    printf("[4]. Ver configuraciones\n");
    printf("[5]. Salir\n");
}

// Restaurar configuraciones por defecto
void restaurar_valores_por_defecto(Config *config, const gchar *ruta)
{
    if (config == NULL)
    {
        fprintf(stderr, "Error: Configuración no válida.\n");
        return;
    }

    config->cargar_miniatura = TRUE;
    config->seleccionar_calidad = TRUE;
    config->paginas_cargar = 2;
    config->visores_de_miniaturas_chafa = TRUE;
    config->visores_de_miniaturas_kitty = FALSE;
    config->suscripciones = FALSE; // Asegúrate de restablecer este valor también
    config->cargarListas = FALSE;
    config->cargarVideos = TRUE;

    guardar_configuracion(ruta, config);
    printf("Configuraciones restauradas a valores por defecto.\nPresione enter para continuar.");
    getchar();
    system("clear");
}

// Cambiar configuraciones
void cambiar_configuraciones(Config *config, const gchar *ruta)
{
    if (config == NULL)
    {
        fprintf(stderr, "Error: Configuración no válida.\n");
        return;
    }

    int opcion;
    int paginas;
    char respuesta;

    system("clear");
    printf("Cambiar configuraciones\n");

    printf("[1]. Cargar Miniatura (actual: %s)\n", config->cargar_miniatura ? "True" : "False");
    printf("[2]. Seleccionar Calidad (actual: %s)\n", config->seleccionar_calidad ? "True" : "False");
    printf("[3]. Páginas a Cargar (actual: %d)\n", config->paginas_cargar);
    printf("[4]. Elegir Visor de miniaturas (actual: %s)\n", config->visores_de_miniaturas_kitty ? "kitty" : "chafa");
    printf("[5]. Elegir filtro\n");
    printf("[6]. Volver\n");

    printf("Seleccione una opción: ");
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer

    switch (opcion)
    {
    case 1:
        while (respuesta != 'S' && respuesta != 'N')
        {
            printf("Activar Cargar Miniatura ([N]: No, [S]: Sí): ");
            scanf(" %c", &respuesta);

            respuesta = toupper(respuesta);
            if (respuesta != 'S' && respuesta != 'N')
            {
                printf("Opción inválida. Ingrese 'S' o 'N'.\n");
            }
        }

        if (respuesta == 'N')
        {
            config->cargar_miniatura = FALSE;
            break;
        }

        config->cargar_miniatura = TRUE;
        break;
    case 2:

        while (respuesta != 'S' && respuesta != 'N')
        {
            printf("Activar Seleccionar Calidad ([N]: No, [S]: Sí): ");
            scanf(" %c", &respuesta);
            respuesta = toupper(respuesta);
            if (respuesta != 'S' && respuesta != 'N')
            {
                printf("Opción inválida. Ingrese 'S' o 'N'.\n");
            }
        }

        if (respuesta == 'N')
        {
            config->seleccionar_calidad = FALSE;
            break;
        }

        config->seleccionar_calidad = TRUE;
        break;
    case 3:
        printf("Número de Páginas a Cargar: ");
        scanf("%d", &paginas);
        config->paginas_cargar = paginas;
        break;
    case 4:

        while (respuesta != 'K' && respuesta != 'C')
        {
            printf("Visualizador de miniaturas (K: Kitty, C: Chafa): ");
            scanf(" %c", &respuesta);
            respuesta = toupper(respuesta);
            if (respuesta != 'K' && respuesta != 'C')
            {
                printf("Opción inválida. Ingrese 'K' o 'C'.\n");
            }
        }

        if (respuesta == 'K')
        {
            config->visores_de_miniaturas_kitty = TRUE;
            config->visores_de_miniaturas_chafa = FALSE;

            break;
        }

        if (respuesta == 'C')
        {
            config->visores_de_miniaturas_kitty = FALSE;
            config->visores_de_miniaturas_chafa = TRUE;

            break;
        }

        break;
    case 5:
        filtros(config, ruta);
    case 6:
        return;
    default:
        printf("Opción no válida. Inténtelo de nuevo.\n");
        return;
    }

    system("clear");
    printf("¿Estás seguro de realizar los siguientes cambios?\n");
    printf("Cargar Miniatura: %s\n", config->cargar_miniatura ? "True" : "False");
    printf("Seleccionar Calidad: %s\n", config->seleccionar_calidad ? "True" : "False");
    printf("Páginas a Cargar: %d\n", config->paginas_cargar);
    printf("Visualizador de miniaturas: %s\n", config->visores_de_miniaturas_kitty ? "kitty" : "chafa");
    printf("filtro: [%s]\n", config->cargarVideos ? "Busqueda por videos" : "Busqueda por listas de videos");

    char respuesta_cambios = ' ';
    while (respuesta_cambios != 'S' && respuesta_cambios != 'N')
    {
        printf("\n¿Aceptar cambios? ([N]: No, [S]: Sí): ");
        scanf(" %c", &respuesta_cambios);
        respuesta_cambios = toupper(respuesta_cambios);
        if (respuesta_cambios != 'S' && respuesta_cambios != 'N')
        {
            printf("Opción inválida. Ingrese 'S' o 'N'.\n");
        }
    }

    if (respuesta_cambios == 'S')
    {
        guardar_configuracion(ruta, config);
        printf("Cambios guardados.\nPresione enter para continuar.");
    }
    else
    {
        printf("Cambios no guardados.\nPresione enter para continuar.");
    }

    getchar();
    system("clear");
}

// Ver configuraciones
void ver_configuraciones(const gchar *ruta)
{
    Config config;
    cargar_configuracion(ruta, &config);

    system("clear");
    printf("Cargar Miniatura: %s\n", config.cargar_miniatura ? "True" : "False");
    printf("Seleccionar Calidad: %s\n", config.seleccionar_calidad ? "True" : "False");
    printf("Páginas a Cargar: %d\n", config.paginas_cargar);
    printf("Visualizador de miniaturas: %s\n", config.visores_de_miniaturas_kitty ? "kitty" : "chafa");
    printf("Suscripciones: %s\n", config.suscripciones ? "Activadas" : "Desactivadas");
    printf("filtro: [%s]\n", config.cargarVideos ? "Busqueda por videos" : "Busqueda por listas de videos");
    printf("Presione enter para continuar.");
    getchar();
    system("clear");
}

void manejar_opcion_config(Config *config, const gchar *ruta)
{
    int opcion;
    do
    {
        printf("\nSeleccione una opción:\n");
        printf("1. Restaurar configuraciones por defecto\n");
        printf("2. Cambiar configuraciones\n");
        printf("3. Ver configuraciones\n");
        printf("4. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion)
        {
        case 1:
            restaurar_valores_por_defecto(config, ruta);
            break;
        case 2:
            cambiar_configuraciones(config, ruta);
            break;
        case 3:
            ver_configuraciones(ruta);
            break;
        case 4:
            ejecutar_menu();
        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
            break;
        }
    } while (opcion != 4);
}

void manejar_opcion_config_copy(Config *config, const gchar *ruta)
{
    gchar *usuario = obtener_usuario();
    gchar ruta_config[512];
    snprintf(ruta_config, sizeof(ruta_config), "/home/%s/.config/cli-youtube/config.txt", usuario);

    if (!usuario)
    {
        fprintf(stderr, "Error al obtener el usuario actual.\n");
        exit(EXIT_FAILURE);
    }

    gchar *ruta_destino = g_strdup_printf("/home/%s/.config/cli-youtube/canales.csv", usuario);

    // Variable para almacenar la ruta proporcionada por el usuario
    char busquedaUsuario[256];

    // Solicitar la ubicación del archivo al usuario
    printf("¿En dónde se encuentra el archivo canales.csv?: ");
    fgets(busquedaUsuario, sizeof(busquedaUsuario), stdin);

    // Eliminar el salto de línea al final de la entrada
    size_t len = strlen(busquedaUsuario);
    if (len > 0 && busquedaUsuario[len - 1] == '\n')
    {
        busquedaUsuario[len - 1] = '\0';
    }

    // Confirmar con el usuario antes de copiar el archivo
    printf("¿Desea continuar con la copia del archivo desde %s a %s? ([N]: No, [S]: Sí): ", busquedaUsuario, ruta_destino);
    char respuesta;
    scanf(" %c", &respuesta);
    respuesta = toupper(respuesta);

    if (respuesta == 'S')
    {
        // Llamar a la función para copiar el archivo
        copiar_archivo_csv(busquedaUsuario, ruta_destino);
        printf("Archivo copiado exitosamente.\n");
        config->suscripciones = TRUE;
        printf("Configuración de suscripciones actualizada a: %s\n", config->suscripciones ? "TRUE" : "FALSE"); // Mensaje de depuración
        guardar_configuracion(ruta_config, config);                                                             // Asegúrate de guardar los cambios
    }
    else
    {
        printf("Operación cancelada.\n");
    }

    // Liberar memoria
    g_free(ruta_destino);
}

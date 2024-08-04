#include "configuracion.h"
#include "menuconfiguracion.h"
#include "cargarParametros.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *salidaTerminal();

char *salidaTerminal()
{
    Config config;
    char *usuario = obtener_usuario(); // Obtener el nombre de usuario actual

    // Construir la ruta de configuración basada en el usuario actual
    gchar ruta_config[MAX_LINE_LENGTH];
    snprintf(ruta_config, sizeof(ruta_config), "/home/%s/.config/cli-youtube/config.txt", usuario);

    // Leer la configuración
    if (access(ruta_config, F_OK) != -1)
    {
        cargar_configuracion(ruta_config, &config);
    }
    else
    {
        printf("No se pudo leer la configuración. Usando valores predeterminados.\n");
        config.cargar_miniatura = TRUE;
        config.paginas_cargar = 2;
        config.seleccionar_calidad = TRUE;
    }

    char command[MAX_LINE_LENGTH] = "ytfzf";

    // Ajustes según la configuración
    if (config.cargarListas == TRUE)
    {
        strcat(command, " --type=playlist");

        if (config.cargar_miniatura)
        {
            strcat(command, " -t");

            if (config.visores_de_miniaturas_kitty == TRUE)
            {
                strcat(command, " -T kitty");
            }
            else
            {
                strcat(command, " -T chafa");
            }
        }
    }
    else if (config.cargarVideos)
    {

        if (config.seleccionar_calidad)
        {
            strcat(command, " -f");
        }

        if (config.cargar_miniatura)
        {
            strcat(command, " -t");

            if (config.visores_de_miniaturas_kitty == TRUE)
            {
                strcat(command, " -T kitty");
            }
            else
            {
                strcat(command, " -T chafa");
            }
        }
    }

    free(usuario);          // Liberar la memoria asignada para el nombre de usuario
    return strdup(command); // Copia el comando a una cadena dinámica
}

#include "configuracion.h"
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cargarParametros.h"

void cargar_configuracion(const gchar *ruta, Config *config);
void guardar_configuracion(const gchar *ruta, const Config *config);
void crear_archivo_configuracion(const gchar *ruta);
int obtener_paginas_cargar(const gchar *ruta);
void asegurar_directorio(const gchar *ruta);
void copiar_archivo_csv(const gchar *ruta_origen, const gchar *ruta_destino);

Config *config = NULL; // Define la variable global

// Asegurar que el directorio exista
void asegurar_directorio(const gchar *ruta) {
    gchar *dir = g_path_get_dirname(ruta);
    if (!g_file_test(dir, G_FILE_TEST_EXISTS)) {
        if (g_mkdir_with_parents(dir, 0700) != 0) {
            g_warning("No se pudo crear el directorio: %s", dir);
        }
    }
    g_free(dir);
}

void cargar_configuracion(const gchar *ruta, Config *config) {
    GKeyFile *key_file = g_key_file_new();
    GError *error = NULL;

    if (!g_key_file_load_from_file(key_file, ruta, G_KEY_FILE_NONE, &error)) {
        g_warning("Error al cargar el archivo de configuración: %s", error->message);
        g_error_free(error);
        g_key_file_free(key_file);
        return;
    }

    config->cargar_miniatura = g_key_file_get_boolean(key_file, "Configuracion", "CargarMiniatura", NULL);
    config->seleccionar_calidad = g_key_file_get_boolean(key_file, "Configuracion", "SeleccionarCalidad", NULL);
    config->paginas_cargar = g_key_file_get_integer(key_file, "Configuracion", "PaginasACargar", NULL);
    config->visores_de_miniaturas_chafa = g_key_file_get_boolean(key_file, "Configuracion", "visores_de_miniaturas_chafa", NULL);
    config->visores_de_miniaturas_kitty = g_key_file_get_boolean(key_file, "Configuracion", "visores_de_miniaturas_kitty", NULL);
    config->cargarVideos = g_key_file_get_boolean(key_file, "Configuracion", "cargarVideos", NULL);
    config->cargarListas = g_key_file_get_boolean(key_file, "Configuracion", "cargarListas", NULL);
    config->suscripciones = g_key_file_get_boolean(key_file, "Configuracion", "suscripciones", NULL);

    g_key_file_free(key_file);
}

void guardar_configuracion(const gchar *ruta, const Config *config) {
    GKeyFile *key_file = g_key_file_new();
    GError *error = NULL;

    g_key_file_set_boolean(key_file, "Configuracion", "CargarMiniatura", config->cargar_miniatura);
    g_key_file_set_boolean(key_file, "Configuracion", "SeleccionarCalidad", config->seleccionar_calidad);
    g_key_file_set_integer(key_file, "Configuracion", "PaginasACargar", config->paginas_cargar);
    g_key_file_set_boolean(key_file, "Configuracion", "visores_de_miniaturas_chafa", config->visores_de_miniaturas_chafa);
    g_key_file_set_boolean(key_file, "Configuracion", "visores_de_miniaturas_kitty", config->visores_de_miniaturas_kitty);
    g_key_file_set_boolean(key_file, "Configuracion", "cargarVideos", config->cargarVideos);
    g_key_file_set_boolean(key_file, "Configuracion", "cargarListas", config->cargarListas);
    g_key_file_set_boolean(key_file, "Configuracion", "suscripciones", config->suscripciones);

    gchar *data = g_key_file_to_data(key_file, NULL, &error);

    if (error) {
        g_warning("Error al convertir los datos del archivo de configuración: %s", error->message);
        g_error_free(error);
    } else {
        g_file_set_contents(ruta, data, -1, &error);
        if (error) {
            g_warning("Error al guardar el archivo de configuración: %s", error->message);
            g_error_free(error);
        }
    }

    g_key_file_free(key_file);
    g_free(data);
}

void crear_archivo_configuracion(const gchar *ruta) {
    Config config = {
        .cargar_miniatura = TRUE,
        .seleccionar_calidad = TRUE,
        .paginas_cargar = 2,
        .visores_de_miniaturas_chafa = TRUE,
        .visores_de_miniaturas_kitty = FALSE,
        .suscripciones = FALSE,
        .cargarVideos = TRUE,
        .cargarListas = FALSE
    };

    guardar_configuracion(ruta, &config);
}

int obtener_paginas_cargar(const gchar *ruta) {
    Config config;
    cargar_configuracion(ruta, &config);
    return config.paginas_cargar;
}


void copiar_archivo_csv(const gchar *ruta_origen, const gchar *ruta_destino) {
    FILE *origen = fopen(ruta_origen, "rb");
    FILE *destino = fopen(ruta_destino, "wb");
    if (origen && destino) {
        char buffer[BUFSIZ];
        size_t n;
        while ((n = fread(buffer, 1, sizeof(buffer), origen)) > 0) {
            fwrite(buffer, 1, n, destino);
        }
    }
    if (origen) fclose(origen);
    if (destino) fclose(destino);

}



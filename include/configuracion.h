#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <glib.h>

typedef struct {
    gboolean cargar_miniatura;
    gboolean seleccionar_calidad;
    gboolean visores_de_miniaturas_kitty;
    gboolean visores_de_miniaturas_chafa;
    gboolean suscripciones;
    gboolean cargarVideos;
    gboolean cargarListas;
    gint paginas_cargar;
} Config;

extern void cargar_configuracion(const gchar *ruta, Config *config);
extern void guardar_configuracion(const gchar *ruta, const Config *config);
extern void crear_archivo_configuracion(const gchar *ruta);
extern int obtener_paginas_cargar(const gchar *ruta); // Declaración de la nueva función
extern void copiar_archivo_csv(const gchar *ruta_origen, const gchar *ruta_destino);


#endif // CONFIGURACION_H

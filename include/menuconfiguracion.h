#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "configuracion.h"
#include <unistd.h>

extern void mostrar_menu_configuracion();
extern void menu_configuraciones(Config *config);
extern void restaurar_valores_por_defecto(Config *config, const gchar *ruta);
extern void cambiar_configuraciones(Config *config, const gchar *ruta);
extern void ver_configuraciones(const gchar *ruta);
extern void  manejar_opcion_config_copy(Config *config, const gchar *ruta);
extern void mostrar_mensaje_archivo(const gchar *ruta_archivo);
extern void gestionar_suscripciones_menu_config(Config *config, const gchar *ruta);





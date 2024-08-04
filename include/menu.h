#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "configuracion.h"
#include <unistd.h>
#include "menuconfiguracion.h"
#include "cargarParametros.h"
#include <ctype.h>

extern short int menuSelecition;
extern short int menuSalirdelPrograma;
extern short int guardarSelection;
extern gchar *paginasBuscar;
extern int easterEggs;


extern char input[MAX_LINE_LENGTH];
extern char command[MAX_LINE_LENGTH];
extern void manejar_opcion(Config *config, const gchar *ruta);
extern int ejecutar_menu();
extern void mostrar_menu();
extern int menu();
extern void buscar();
extern void asegurar_directorio(const gchar *ruta);
extern int easterEggs;
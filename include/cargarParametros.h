#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "configuracion.h"
#include <unistd.h>
#include "menuconfiguracion.h"


#define MAX_LINE_LENGTH 512

extern int eleccion;
extern char conversión;
extern char* salidaTerminal();
extern char* obtener_usuario();


// Función para obtener el nombre del usuario actual

